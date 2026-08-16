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
#include <stdint.h>

#include <debug.h>
#include <nuttx/arch.h>

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

#define IOMUXC_PAD_ETHERNET             0x07u

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* FRDM-IMXRT1186 uses the shared external MDIO controller for Motorcomm
 * YT8531 PHYs on NETC switch ports 0 and 2.  Do not configure the RT1180-EVK
 * ETH4 RMII pins here: that direct ENETC0/RTL8201 path is not fitted.
 */

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
  putreg32(7, IMXRT_IOMUXC_GPIO_AD_30_MUX); /* NETC EMDC */
  putreg32(IOMUXC_PAD_ETHERNET, IMXRT_IOMUXC_GPIO_AD_30_PAD);
  putreg32(7, IMXRT_IOMUXC_GPIO_AD_31_MUX); /* NETC EMDIO */
  putreg32(4, IMXRT_IOMUXC_NETC_EMDIO_SELECT_INPUT);
  putreg32(IOMUXC_PAD_ETHERNET, IMXRT_IOMUXC_GPIO_AD_31_PAD);
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

static int imxrt_netc_probe_phy(uint8_t phyaddr, const char *port)
{
  uint16_t phyid1;
  uint16_t phyid2;
  int ret;

  ret = imxrt_netc_mdio_read(phyaddr, NETC_PHY_ID1, &phyid1);
  if (ret == OK)
    {
      ret = imxrt_netc_mdio_read(phyaddr, NETC_PHY_ID2, &phyid2);
    }

  if (ret < 0)
    {
      nerr("NETC: FRDM switch %s PHY address %u probe failed: %d\n",
           port, phyaddr, ret);
      return ret;
    }

  if ((phyid1 == 0 && phyid2 == 0) ||
      (phyid1 == 0xffff && phyid2 == 0xffff))
    {
      nerr("NETC: invalid %s PHY ID %04x:%04x at address %u\n",
           port, phyid1, phyid2, phyaddr);
      return -ENODEV;
    }

  ninfo("NETC: FRDM switch %s PHY ID %04x:%04x at address %u\n",
        port, phyid1, phyid2, phyaddr);
  return OK;
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
  int port0;
  int port2;
  int ret;

  ret = imxrt_netc_emdio_initialize();
  if (ret < 0)
    {
      nerr("NETC: EMDIO initialization failed: %d\n", ret);
      return ret;
    }

  port0 = imxrt_netc_probe_phy(CONFIG_IMXRT_NETC_PORT0_PHY_ADDRESS,
                               "port 0");
  port2 = imxrt_netc_probe_phy(CONFIG_IMXRT_NETC_PORT2_PHY_ADDRESS,
                               "port 2");
  if (port0 < 0 && port2 < 0)
    {
      return -ENODEV;
    }

  ninfo("NETC: FRDM MDIO discovery complete; ENETC1/switch packet path "
        "is not implemented\n");
  return OK;
}
