/****************************************************************************
 * arch/arm/src/imxrt/imxrt_netc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <debug.h>
#include <nuttx/arch.h>
#include <nuttx/compiler.h>
#include <nuttx/net/netdev.h>

#include "arm_internal.h"
#include "imxrt_netc.h"
#include "hardware/rt118x/imxrt118x_netc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define NETC_MDC_MAX_FREQUENCY          2500000u
#define NETC_MDC_DIVISOR                (2u * NETC_MDC_MAX_FREQUENCY)
#define NETC_MDIO_HOLD_RECOMMENDED      2u

#define NETC_PHY_ID1                    2u
#define NETC_PHY_ID2                    3u

#define IOMUXC_MUX_SION                 (1u << 4)
#define IOMUXC_PAD_ETHERNET             0x07u

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct imxrt_netc_pin_s
{
  uintptr_t mux;
  uintptr_t input;
  uintptr_t pad;
  uint8_t mode;
  uint8_t daisy;
  bool input_enable;
};

struct imxrt_netc_driver_s
{
  bool registered;
  int mdio_status;
  uint16_t phyid1;
  uint16_t phyid2;
  struct net_driver_s dev;
  uint8_t buffer[MAX_NETDEV_PKTSIZE + CONFIG_NET_GUARDSIZE]
    aligned_data(4);
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct imxrt_netc_pin_s g_netc_pins[] =
{
  {0x42a10184u, 0,           0x42a103ccu, 7, 0, false}, /* EMDC */
  {0x42a10188u, 0x42a10798u, 0x42a103d0u, 7, 4, false}, /* EMDIO */
  {0x42a100ecu, 0,           0x42a10334u, 1, 0, false}, /* TXD0 */
  {0x42a100f0u, 0,           0x42a10338u, 1, 0, false}, /* TXD1 */
  {0x42a100f4u, 0,           0x42a1033cu, 1, 0, false}, /* TX_EN */
  {0x42a100f8u, 0x42a10854u, 0x42a10340u, 1, 1, true},  /* REF_CLK */
  {0x42a100fcu, 0x42a10844u, 0x42a10344u, 1, 1, false}, /* RXD0 */
  {0x42a10100u, 0x42a10848u, 0x42a10348u, 1, 1, false}, /* RXD1 */
  {0x42a10104u, 0x42a1083cu, 0x42a1034cu, 1, 1, false}, /* RX_DV */
  {0x42a10108u, 0x42a10840u, 0x42a10350u, 1, 1, false}, /* RX_ER */
};

static struct imxrt_netc_driver_s g_netc;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int imxrt_netc_wait_clear(uintptr_t address, uint32_t mask)
{
  unsigned int timeout;

  for (timeout = 0; timeout < CONFIG_IMXRT_NETC_MDIO_TIMEOUT_US; timeout++)
    {
      if ((getreg32(address) & mask) == 0)
        {
          return OK;
        }

      up_udelay(1);
    }

  return -ETIMEDOUT;
}

static void imxrt_netc_configure_pins(void)
{
  unsigned int i;

  for (i = 0; i < sizeof(g_netc_pins) / sizeof(g_netc_pins[0]); i++)
    {
      uint32_t mux = g_netc_pins[i].mode;

      if (g_netc_pins[i].input_enable)
        {
          mux |= IOMUXC_MUX_SION;
        }

      putreg32(mux, g_netc_pins[i].mux);
      if (g_netc_pins[i].input != 0)
        {
          putreg32(g_netc_pins[i].daisy, g_netc_pins[i].input);
        }

      putreg32(IOMUXC_PAD_ETHERNET, g_netc_pins[i].pad);
    }
}

static int imxrt_netc_emdio_initialize(void)
{
  uint32_t divisor;
  uint16_t regval;
  int ret;

  imxrt_netc_configure_pins();

  /* Reset the independent EMDIO PCI function, then permit its register
   * accesses.  MSI-X is deliberately not configured in this MDIO-only slice.
   */

  regval = getreg16(IMXRT_NETC_F1_DEVICE_CONTROL);
  putreg16(regval | NETC_PCI_DEVICE_CONTROL_FLR,
           IMXRT_NETC_F1_DEVICE_CONTROL);

  ret = imxrt_netc_wait_clear(IMXRT_NETC_F1_DEVICE_CONTROL,
                              NETC_PCI_DEVICE_CONTROL_FLR);
  if (ret < 0)
    {
      nerr("NETC: EMDIO function reset timed out\n");
      return ret;
    }

  regval = getreg16(IMXRT_NETC_F1_COMMAND);
  regval |= NETC_PCI_COMMAND_MEMORY | NETC_PCI_COMMAND_MASTER;
  putreg16(regval, IMXRT_NETC_F1_COMMAND);

  divisor = (CONFIG_IMXRT_NETC_CLOCK_FREQUENCY +
             NETC_MDC_DIVISOR - 1) / NETC_MDC_DIVISOR;
  if (divisor == 0 || divisor > 0x1ffu)
    {
      return -ERANGE;
    }

  putreg32((divisor << NETC_EMDIO_CFG_DIV_SHIFT) |
           (NETC_MDIO_HOLD_RECOMMENDED << NETC_EMDIO_CFG_HOLD_SHIFT),
           IMXRT_NETC_EMDIO_CFG);
  return OK;
}

static int imxrt_netc_probe_phy(struct imxrt_netc_driver_s *priv)
{
  int ret;

  ret = imxrt_netc_mdio_read(CONFIG_IMXRT_NETC_PHY_ADDRESS, NETC_PHY_ID1,
                             &priv->phyid1);
  if (ret == OK)
    {
      ret = imxrt_netc_mdio_read(CONFIG_IMXRT_NETC_PHY_ADDRESS, NETC_PHY_ID2,
                                 &priv->phyid2);
    }

  if (ret < 0)
    {
      nerr("NETC: PHY address %u MDIO probe failed: %d\n",
           CONFIG_IMXRT_NETC_PHY_ADDRESS, ret);
      return ret;
    }

  if ((priv->phyid1 == 0 && priv->phyid2 == 0) ||
      (priv->phyid1 == 0xffff && priv->phyid2 == 0xffff))
    {
      nerr("NETC: invalid PHY ID %04x:%04x at address %u\n",
           priv->phyid1, priv->phyid2, CONFIG_IMXRT_NETC_PHY_ADDRESS);
      return -ENODEV;
    }

  ninfo("NETC: PHY ID %04x:%04x at address %u\n",
        priv->phyid1, priv->phyid2, CONFIG_IMXRT_NETC_PHY_ADDRESS);
  return OK;
}

static int imxrt_netc_ifup(struct net_driver_s *dev)
{
  struct imxrt_netc_driver_s *priv = dev->d_private;

  priv->mdio_status = imxrt_netc_probe_phy(priv);
  if (priv->mdio_status < 0)
    {
      return priv->mdio_status;
    }

  /* The descriptor rings and MSI-X receive/transmit path are intentionally
   * not represented as complete.  Leave eth0 down after proving MDIO.
   */

  nerr("NETC: PHY found; packet data path is not implemented\n");
  return -ENOSYS;
}

static int imxrt_netc_ifdown(struct net_driver_s *dev)
{
  return OK;
}

static int imxrt_netc_txavail(struct net_driver_s *dev)
{
  return -ENOSYS;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int imxrt_netc_mdio_read(uint8_t phyaddr, uint8_t regaddr,
                         uint16_t *value)
{
  uint32_t config;
  int ret;

  if (value == NULL || phyaddr > 31 || regaddr > 31)
    {
      return -EINVAL;
    }

  config = getreg32(IMXRT_NETC_EMDIO_CFG);
  config &= ~NETC_EMDIO_CFG_CLAUSE45;
  putreg32(config, IMXRT_NETC_EMDIO_CFG);
  putreg32(NETC_EMDIO_CONTROL_READ |
           ((uint32_t)phyaddr << NETC_EMDIO_CONTROL_PHY_SHIFT) |
           ((uint32_t)regaddr << NETC_EMDIO_CONTROL_REG_SHIFT),
           IMXRT_NETC_EMDIO_CONTROL);

  ret = imxrt_netc_wait_clear(IMXRT_NETC_EMDIO_CFG,
                              NETC_EMDIO_CFG_BUSY);
  if (ret < 0)
    {
      return ret;
    }

  config = getreg32(IMXRT_NETC_EMDIO_CFG);
  if ((config & (NETC_EMDIO_CFG_READ_ERROR |
                 NETC_EMDIO_CFG_ADDRESS_ERROR)) != 0)
    {
      return -EIO;
    }

  *value = getreg32(IMXRT_NETC_EMDIO_DATA) & 0xffffu;
  return OK;
}

int imxrt_netc_initialize(void)
{
  struct imxrt_netc_driver_s *priv = &g_netc;
  uint8_t *mac;
  int ret;

  if (priv->registered)
    {
      return -EALREADY;
    }

  memset(priv, 0, sizeof(*priv));
  ret = imxrt_netc_emdio_initialize();
  if (ret < 0)
    {
      nerr("NETC: EMDIO initialization failed: %d\n", ret);
      return ret;
    }

  priv->mdio_status = imxrt_netc_probe_phy(priv);

  priv->dev.d_buf       = priv->buffer;
  priv->dev.d_ifup      = imxrt_netc_ifup;
  priv->dev.d_ifdown    = imxrt_netc_ifdown;
  priv->dev.d_txavail   = imxrt_netc_txavail;
  priv->dev.d_private   = priv;

  /* Fork-local bench MAC.  Keep the locally administered bit set until a
   * board-unique address source is deliberately wired.
   */

  mac = priv->dev.d_mac.ether.ether_addr_octet;
  mac[0] = 0x02;
  mac[1] = 0x00;
  mac[2] = 0x00;
  mac[3] = 0x01;
  mac[4] = 0x02;
  mac[5] = 0x00;

  ret = netdev_register(&priv->dev, NET_LL_ETHERNET);
  if (ret == OK)
    {
      priv->registered = true;
    }

  return ret;
}
