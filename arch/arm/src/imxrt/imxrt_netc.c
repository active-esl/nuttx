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

#include <arpa/inet.h>

#include <debug.h>
#include <nuttx/arch.h>
#include <nuttx/cache.h>
#include <nuttx/clock.h>
#include <nuttx/compiler.h>
#include <nuttx/net/ip.h>
#include <nuttx/net/netdev.h>
#include <nuttx/wdog.h>
#include <nuttx/wqueue.h>

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
#define NETC_PHY_BMSR                   1u
#define NETC_PHY_ANAR                   4u
#define NETC_PHY_ANLPAR                 5u

#define NETC_PHY_BMSR_LINK              (1u << 2)
#define NETC_PHY_BMSR_AN_COMPLETE       (1u << 5)
#define NETC_PHY_AN_10_HALF             (1u << 5)
#define NETC_PHY_AN_10_FULL             (1u << 6)
#define NETC_PHY_AN_100_HALF            (1u << 7)
#define NETC_PHY_AN_100_FULL            (1u << 8)

#define NETC_RING_COUNT                 8u
#define NETC_DESCRIPTOR_ALIGNMENT       128u
#define NETC_DMA_ALIGNMENT              32u
#define NETC_DMA_BUFFER_SIZE            1536u
#define NETC_POLL_DELAY                 MSEC2TICK(10)

#define NETC_RX_READY                   (1ull << 62)
#define NETC_RX_FINAL                   (1ull << 63)
#define NETC_RX_ERROR_SHIFT             48
#define NETC_TX_FINAL                   (1ull << 63)

#if !defined(CONFIG_SCHED_WORKQUEUE)
#  error Work queue support is required
#else
#  define ETHWORK LPWORK
#endif

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

struct imxrt_netc_desc_s
{
  uint64_t word0;
  uint64_t word1;
};

struct imxrt_netc_driver_s
{
  bool registered;
  bool ifup;
  int mdio_status;
  uint16_t phyid1;
  uint16_t phyid2;
  uint16_t txhead;
  uint16_t txclean;
  uint16_t rxtail;
  struct wdog_s polltimer;
  struct work_s pollwork;
  struct net_driver_s dev;
  uint8_t buffer[MAX_NETDEV_PKTSIZE + CONFIG_NET_GUARDSIZE]
    aligned_data(NETC_DMA_ALIGNMENT);
  struct imxrt_netc_desc_s txring[NETC_RING_COUNT]
    aligned_data(NETC_DESCRIPTOR_ALIGNMENT);
  struct imxrt_netc_desc_s rxring[NETC_RING_COUNT]
    aligned_data(NETC_DESCRIPTOR_ALIGNMENT);
  uint8_t txpool[NETC_RING_COUNT][NETC_DMA_BUFFER_SIZE]
    aligned_data(NETC_DMA_ALIGNMENT);
  uint8_t rxpool[NETC_RING_COUNT][NETC_DMA_BUFFER_SIZE]
    aligned_data(NETC_DMA_ALIGNMENT);
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

static void imxrt_netc_poll_expiry(wdparm_t arg);

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

static int imxrt_netc_phy_link(bool *linkup, bool *speed100,
                               bool *full_duplex)
{
  uint16_t advertise;
  uint16_t partner;
  uint16_t status;
  uint16_t common;
  int ret;

  ret = imxrt_netc_mdio_read(CONFIG_IMXRT_NETC_PHY_ADDRESS,
                             NETC_PHY_BMSR, &status);
  if (ret == OK)
    {
      /* BMSR link status is latched low, so use the second read. */

      ret = imxrt_netc_mdio_read(CONFIG_IMXRT_NETC_PHY_ADDRESS,
                                 NETC_PHY_BMSR, &status);
    }

  if (ret < 0)
    {
      return ret;
    }

  *linkup = (status & NETC_PHY_BMSR_LINK) != 0;
  if (!*linkup)
    {
      return OK;
    }

  if ((status & NETC_PHY_BMSR_AN_COMPLETE) == 0)
    {
      return -EAGAIN;
    }

  ret = imxrt_netc_mdio_read(CONFIG_IMXRT_NETC_PHY_ADDRESS,
                             NETC_PHY_ANAR, &advertise);
  if (ret == OK)
    {
      ret = imxrt_netc_mdio_read(CONFIG_IMXRT_NETC_PHY_ADDRESS,
                                 NETC_PHY_ANLPAR, &partner);
    }

  if (ret < 0)
    {
      return ret;
    }

  common = advertise & partner;
  if ((common & NETC_PHY_AN_100_FULL) != 0)
    {
      *speed100 = true;
      *full_duplex = true;
    }
  else if ((common & NETC_PHY_AN_100_HALF) != 0)
    {
      *speed100 = true;
      *full_duplex = false;
    }
  else if ((common & NETC_PHY_AN_10_FULL) != 0)
    {
      *speed100 = false;
      *full_duplex = true;
    }
  else if ((common & NETC_PHY_AN_10_HALF) != 0)
    {
      *speed100 = false;
      *full_duplex = false;
    }
  else
    {
      return -EPROTO;
    }

  return OK;
}

static void imxrt_netc_clean(void *address, size_t size)
{
  up_clean_dcache((uintptr_t)address, (uintptr_t)address + size);
}

static void imxrt_netc_invalidate(void *address, size_t size)
{
  up_invalidate_dcache((uintptr_t)address, (uintptr_t)address + size);
}

static void imxrt_netc_set_mac(struct imxrt_netc_driver_s *priv)
{
  const uint8_t *mac = priv->dev.d_mac.ether.ether_addr_octet;
  uint32_t low;
  uint32_t high;

  low = (uint32_t)mac[0] | ((uint32_t)mac[1] << 8) |
        ((uint32_t)mac[2] << 16) | ((uint32_t)mac[3] << 24);
  high = (uint32_t)mac[4] | ((uint32_t)mac[5] << 8);

  putreg32(low, IMXRT_NETC_ENETC0_PSIPMAR0);
  putreg32(high, IMXRT_NETC_ENETC0_PSIPMAR1);
  putreg32(low, IMXRT_NETC_ENETC0_PORT_PMAR0);
  putreg32(high, IMXRT_NETC_ENETC0_PORT_PMAR1);
}

static int imxrt_netc_rings_initialize(struct imxrt_netc_driver_s *priv,
                                       bool speed100, bool full_duplex)
{
  uintptr_t address;
  uint32_t capability;
  uint32_t mode;
  uint16_t command;
  unsigned int i;
  int ret;

  /* A zero/all-ones capability value means the NETC clock or CM33 access
   * path is not ready.  Do not report a successfully raised interface when
   * ELE/TRDC or the NETC roots still block the peripheral.
   */

  capability = getreg32(IMXRT_NETC_ENETC0_ECAPR2);
  if (capability == 0 || capability == UINT32_MAX)
    {
      nerr("NETC: ENETC0 unavailable (clock or ELE/TRDC access)\n");
      return -EACCES;
    }

  command = getreg16(IMXRT_NETC_F0_DEVICE_CONTROL);
  putreg16(command | NETC_PCI_DEVICE_CONTROL_FLR,
           IMXRT_NETC_F0_DEVICE_CONTROL);
  ret = imxrt_netc_wait_clear(IMXRT_NETC_F0_DEVICE_CONTROL,
                              NETC_PCI_DEVICE_CONTROL_FLR);
  if (ret < 0)
    {
      nerr("NETC: ENETC0 function reset timed out\n");
      return ret;
    }

  command = getreg16(IMXRT_NETC_F0_COMMAND);
  command |= NETC_PCI_COMMAND_MEMORY | NETC_PCI_COMMAND_MASTER;
  putreg16(command, IMXRT_NETC_F0_COMMAND);

  memset(priv->txring, 0, sizeof(priv->txring));
  memset(priv->rxring, 0, sizeof(priv->rxring));
  priv->txhead = 0;
  priv->txclean = 0;
  priv->rxtail = 0;

  for (i = 0; i < NETC_RING_COUNT; i++)
    {
      priv->rxring[i].word0 = (uintptr_t)priv->rxpool[i];
    }

  imxrt_netc_clean(priv->txring, sizeof(priv->txring));
  imxrt_netc_clean(priv->rxring, sizeof(priv->rxring));
  imxrt_netc_invalidate(priv->rxpool, sizeof(priv->rxpool));

  putreg32(NETC_ENETC_PSICFGR0_TXRINGS(1) |
           NETC_ENETC_PSICFGR0_RXRINGS(1),
           IMXRT_NETC_ENETC0_PSICFGR0);
  imxrt_netc_set_mac(priv);

  address = (uintptr_t)priv->txring;
  putreg32((uint32_t)address, IMXRT_NETC_SI_TBBAR0);
  putreg32(0, IMXRT_NETC_SI_TBBAR1);
  putreg32(0, IMXRT_NETC_SI_TBPIR);
  putreg32(0, IMXRT_NETC_SI_TBCIR);
  putreg32(NETC_RING_COUNT, IMXRT_NETC_SI_TBLENR);
  putreg32(0, IMXRT_NETC_SI_TBIER);
  putreg32(NETC_SI_TBMR_ENABLE, IMXRT_NETC_SI_TBMR);

  address = (uintptr_t)priv->rxring;
  putreg32((uint32_t)address, IMXRT_NETC_SI_RBBAR0);
  putreg32(0, IMXRT_NETC_SI_RBBAR1);
  putreg32(NETC_DMA_BUFFER_SIZE, IMXRT_NETC_SI_RBBSR);
  putreg32(0, IMXRT_NETC_SI_RBCIR);
  putreg32(NETC_RING_COUNT, IMXRT_NETC_SI_RBLENR);
  putreg32(0, IMXRT_NETC_SI_RBIER);
  putreg32(NETC_SI_RBMR_ENABLE, IMXRT_NETC_SI_RBMR);

  mode = NETC_ENETC_IFMODE_RMII;
  if (!speed100)
    {
      mode |= NETC_ENETC_IFMODE_10M;
    }

  if (!full_duplex)
    {
      mode |= NETC_ENETC_IFMODE_HALF_DUPLEX;
    }

  modifyreg32(IMXRT_NETC_ENETC0_IF_MODE,
              NETC_ENETC_IFMODE_MASK | NETC_ENETC_IFMODE_10M |
              NETC_ENETC_IFMODE_HALF_DUPLEX, mode);
  modifyreg32(IMXRT_NETC_ENETC0_PMR, 0, NETC_ENETC_PMR_SI0EN);
  modifyreg32(IMXRT_NETC_SI_SIMR, 0, NETC_SI_SIMR_ENABLE);
  modifyreg32(IMXRT_NETC_ENETC0_COMMAND_CONFIG, 0,
              NETC_ENETC_COMMAND_TX_EN | NETC_ENETC_COMMAND_RX_EN);

  if ((getreg32(IMXRT_NETC_SI_SIMR) & NETC_SI_SIMR_ENABLE) == 0 ||
      (getreg32(IMXRT_NETC_SI_RBMR) & NETC_SI_RBMR_ENABLE) == 0)
    {
      nerr("NETC: descriptor enable rejected (BLK_CTRL/IERB/TRDC)\n");
      return -EACCES;
    }

  return OK;
}

static void imxrt_netc_reclaim_tx(struct imxrt_netc_driver_s *priv)
{
  uint16_t consumer = getreg32(IMXRT_NETC_SI_TBCIR) % NETC_RING_COUNT;

  while (priv->txclean != consumer)
    {
      priv->txclean = (priv->txclean + 1) % NETC_RING_COUNT;
    }
}

static int imxrt_netc_transmit(struct imxrt_netc_driver_s *priv)
{
  struct imxrt_netc_desc_s *desc;
  uint16_t next;

  imxrt_netc_reclaim_tx(priv);
  next = (priv->txhead + 1) % NETC_RING_COUNT;
  if (next == priv->txclean)
    {
      return -EBUSY;
    }

  if (priv->dev.d_len < 16 || priv->dev.d_len > NETC_DMA_BUFFER_SIZE)
    {
      NETDEV_TXERRORS(&priv->dev);
      return -EMSGSIZE;
    }

  memcpy(priv->txpool[priv->txhead], priv->dev.d_buf, priv->dev.d_len);
  imxrt_netc_clean(priv->txpool[priv->txhead], priv->dev.d_len);

  desc = &priv->txring[priv->txhead];
  desc->word0 = (uintptr_t)priv->txpool[priv->txhead];
  desc->word1 = (uint64_t)priv->dev.d_len |
                ((uint64_t)priv->dev.d_len << 16) | NETC_TX_FINAL;
  imxrt_netc_clean(desc, sizeof(*desc));

  priv->txhead = next;
  putreg32(priv->txhead, IMXRT_NETC_SI_TBPIR);
  NETDEV_TXPACKETS(&priv->dev);
  priv->dev.d_len = 0;
  return OK;
}

static int imxrt_netc_txpoll(struct net_driver_s *dev)
{
  return imxrt_netc_transmit(dev->d_private);
}

static void imxrt_netc_dispatch(struct imxrt_netc_driver_s *priv)
{
  struct eth_hdr_s *hdr = (struct eth_hdr_s *)priv->dev.d_buf;

  NETDEV_RXPACKETS(&priv->dev);

#ifdef CONFIG_NET_IPv4
  if (hdr->type == HTONS(ETHTYPE_IP))
    {
      NETDEV_RXIPV4(&priv->dev);
      ipv4_input(&priv->dev);
    }
  else
#endif
#ifdef CONFIG_NET_IPv6
  if (hdr->type == HTONS(ETHTYPE_IP6))
    {
      NETDEV_RXIPV6(&priv->dev);
      ipv6_input(&priv->dev);
    }
  else
#endif
#ifdef CONFIG_NET_ARP
  if (hdr->type == HTONS(ETHTYPE_ARP))
    {
      NETDEV_RXARP(&priv->dev);
      arp_input(&priv->dev);
    }
  else
#endif
    {
      NETDEV_RXDROPPED(&priv->dev);
      priv->dev.d_len = 0;
    }

  if (priv->dev.d_len > 0)
    {
      imxrt_netc_transmit(priv);
    }
}

static void imxrt_netc_receive(struct imxrt_netc_driver_s *priv)
{
  struct imxrt_netc_desc_s *desc;
  unsigned int budget = NETC_RING_COUNT;
  uint16_t length;

  while (budget-- > 0)
    {
      desc = &priv->rxring[priv->rxtail];
      imxrt_netc_invalidate(desc, sizeof(*desc));
      if ((desc->word1 & NETC_RX_READY) == 0)
        {
          break;
        }

      length = desc->word1 & 0xffffu;
      if ((desc->word1 & NETC_RX_FINAL) == 0 ||
          ((desc->word1 >> NETC_RX_ERROR_SHIFT) & 0xffu) != 0 ||
          length == 0 || length > NETC_DMA_BUFFER_SIZE ||
          length > sizeof(priv->buffer))
        {
          NETDEV_RXERRORS(&priv->dev);
        }
      else
        {
          imxrt_netc_invalidate(priv->rxpool[priv->rxtail], length);
          memcpy(priv->buffer, priv->rxpool[priv->rxtail], length);
          priv->dev.d_buf = priv->buffer;
          priv->dev.d_len = length;
          imxrt_netc_dispatch(priv);
        }

      desc->word0 = (uintptr_t)priv->rxpool[priv->rxtail];
      desc->word1 = 0;
      imxrt_netc_clean(desc, sizeof(*desc));
      priv->rxtail = (priv->rxtail + 1) % NETC_RING_COUNT;
      putreg32(priv->rxtail, IMXRT_NETC_SI_RBCIR);
    }

  priv->dev.d_buf = priv->buffer;
  priv->dev.d_len = 0;
}

static void imxrt_netc_poll_work(void *arg)
{
  struct imxrt_netc_driver_s *priv = arg;

  net_lock();
  if (priv->ifup)
    {
      imxrt_netc_receive(priv);
      imxrt_netc_reclaim_tx(priv);
      devif_poll(&priv->dev, imxrt_netc_txpoll);
      wd_start(&priv->polltimer, NETC_POLL_DELAY,
               imxrt_netc_poll_expiry, (wdparm_t)priv);
    }

  net_unlock();
}

static void imxrt_netc_poll_expiry(wdparm_t arg)
{
  struct imxrt_netc_driver_s *priv =
    (struct imxrt_netc_driver_s *)arg;

  work_queue(ETHWORK, &priv->pollwork, imxrt_netc_poll_work, priv, 0);
}

static int imxrt_netc_ifup(struct net_driver_s *dev)
{
  struct imxrt_netc_driver_s *priv = dev->d_private;
  bool full_duplex = false;
  bool linkup = false;
  bool speed100 = false;
  int ret;

  priv->mdio_status = imxrt_netc_probe_phy(priv);
  if (priv->mdio_status < 0)
    {
      return priv->mdio_status;
    }

  ret = imxrt_netc_phy_link(&linkup, &speed100, &full_duplex);
  if (ret < 0)
    {
      nerr("NETC: PHY link negotiation not ready: %d\n", ret);
      return ret;
    }

  if (!linkup)
    {
      nerr("NETC: PHY link is down\n");
      return -ENETDOWN;
    }

  ret = imxrt_netc_rings_initialize(priv, speed100, full_duplex);
  if (ret < 0)
    {
      return ret;
    }

  priv->ifup = true;
  netdev_carrier_on(dev);
  wd_start(&priv->polltimer, NETC_POLL_DELAY,
           imxrt_netc_poll_expiry, (wdparm_t)priv);
  ninfo("NETC: eth0 up, %u Mbps %s duplex (polling data path)\n",
        speed100 ? 100 : 10, full_duplex ? "full" : "half");
  return OK;
}

static int imxrt_netc_ifdown(struct net_driver_s *dev)
{
  struct imxrt_netc_driver_s *priv = dev->d_private;

  priv->ifup = false;
  wd_cancel(&priv->polltimer);
  work_cancel(ETHWORK, &priv->pollwork);
  modifyreg32(IMXRT_NETC_ENETC0_COMMAND_CONFIG,
              NETC_ENETC_COMMAND_TX_EN | NETC_ENETC_COMMAND_RX_EN, 0);
  modifyreg32(IMXRT_NETC_SI_SIMR, NETC_SI_SIMR_ENABLE, 0);
  modifyreg32(IMXRT_NETC_ENETC0_PMR, NETC_ENETC_PMR_SI0EN, 0);
  netdev_carrier_off(dev);
  return OK;
}

static int imxrt_netc_txavail(struct net_driver_s *dev)
{
  struct imxrt_netc_driver_s *priv = dev->d_private;

  if (priv->ifup && work_available(&priv->pollwork))
    {
      work_queue(ETHWORK, &priv->pollwork, imxrt_netc_poll_work, priv, 0);
    }

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
