/****************************************************************************
 * arch/arm/src/imxrt/hardware/rt118x/imxrt118x_netc.h
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

#ifndef __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_NETC_H
#define __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_NETC_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* NETC function 1 is the independent external MDIO controller. */

#define IMXRT_NETC_F0_BASE                0x60000000u
#define IMXRT_NETC_F0_COMMAND             (IMXRT_NETC_F0_BASE + 0x0004u)
#define IMXRT_NETC_F0_DEVICE_CONTROL      (IMXRT_NETC_F0_BASE + 0x0048u)

#define IMXRT_NETC_F1_BASE                0x60001000u
#define IMXRT_NETC_F1_COMMAND             (IMXRT_NETC_F1_BASE + 0x0004u)
#define IMXRT_NETC_F1_DEVICE_CONTROL      (IMXRT_NETC_F1_BASE + 0x0048u)

#define NETC_PCI_COMMAND_MEMORY            (1u << 1)
#define NETC_PCI_COMMAND_MASTER            (1u << 2)
#define NETC_PCI_DEVICE_CONTROL_FLR        (1u << 15)

/* External MDIO register block. */

#define IMXRT_NETC_EMDIO_BASE             0x60ba0000u
#define IMXRT_NETC_EMDIO_CFG              (IMXRT_NETC_EMDIO_BASE + 0x1c00u)
#define IMXRT_NETC_EMDIO_CONTROL          (IMXRT_NETC_EMDIO_BASE + 0x1c04u)
#define IMXRT_NETC_EMDIO_DATA             (IMXRT_NETC_EMDIO_BASE + 0x1c08u)

#define NETC_EMDIO_CFG_READ_ERROR         (1u << 1)
#define NETC_EMDIO_CFG_HOLD_SHIFT         2
#define NETC_EMDIO_CFG_CLAUSE45           (1u << 6)
#define NETC_EMDIO_CFG_DIV_SHIFT          7
#define NETC_EMDIO_CFG_DIV_MASK           (0x1ffu << NETC_EMDIO_CFG_DIV_SHIFT)
#define NETC_EMDIO_CFG_ADDRESS_ERROR      (1u << 28)
#define NETC_EMDIO_CFG_BUSY               (1u << 31)

#define NETC_EMDIO_CONTROL_REG_SHIFT      0
#define NETC_EMDIO_CONTROL_PHY_SHIFT      5
#define NETC_EMDIO_CONTROL_READ           (1u << 15)

/* ENETC0 PSI0 and port register blocks. */

#define IMXRT_NETC_ENETC0_BASE            0x60b10000u
#define IMXRT_NETC_ENETC0_ECAPR2          (IMXRT_NETC_ENETC0_BASE + 0x0008u)
#define IMXRT_NETC_ENETC0_PMR             (IMXRT_NETC_ENETC0_BASE + 0x0010u)
#define IMXRT_NETC_ENETC0_PSIPMAR0        (IMXRT_NETC_ENETC0_BASE + 0x2000u)
#define IMXRT_NETC_ENETC0_PSIPMAR1        (IMXRT_NETC_ENETC0_BASE + 0x2004u)
#define IMXRT_NETC_ENETC0_PSICFGR0        (IMXRT_NETC_ENETC0_BASE + 0x2010u)

#define NETC_ENETC_PMR_SI0EN              (1u << 16)
#define NETC_ENETC_PSICFGR0_TXRINGS(n)    ((uint32_t)(n) & 0x7fu)
#define NETC_ENETC_PSICFGR0_RXRINGS(n)    (((uint32_t)(n) & 0x7fu) << 16)

#define IMXRT_NETC_ENETC0_PORT_BASE       0x60b14000u
#define IMXRT_NETC_ENETC0_PORT_PMAR0      (IMXRT_NETC_ENETC0_PORT_BASE + 0x20u)
#define IMXRT_NETC_ENETC0_PORT_PMAR1      (IMXRT_NETC_ENETC0_PORT_BASE + 0x24u)

#define IMXRT_NETC_ENETC0_LINK_BASE       0x60b15000u
#define IMXRT_NETC_ENETC0_COMMAND_CONFIG  (IMXRT_NETC_ENETC0_LINK_BASE + 0x08u)
#define IMXRT_NETC_ENETC0_IF_MODE         (IMXRT_NETC_ENETC0_LINK_BASE + 0x300u)

#define NETC_ENETC_COMMAND_TX_EN          (1u << 0)
#define NETC_ENETC_COMMAND_RX_EN          (1u << 1)
#define NETC_ENETC_IFMODE_MASK            0x7u
#define NETC_ENETC_IFMODE_RMII            0x3u
#define NETC_ENETC_IFMODE_10M             (1u << 4)
#define NETC_ENETC_IFMODE_HALF_DUPLEX     (1u << 6)

#define IMXRT_NETC_ENETC0_SI_BASE         0x60b00000u
#define IMXRT_NETC_SI_SIMR                (IMXRT_NETC_ENETC0_SI_BASE + 0x0000u)
#define IMXRT_NETC_SI_SIPCAPR0            (IMXRT_NETC_ENETC0_SI_BASE + 0x0020u)
#define IMXRT_NETC_SI_SIRBGCR             (IMXRT_NETC_ENETC0_SI_BASE + 0x0038u)
#define IMXRT_NETC_SI_BDR_BASE            (IMXRT_NETC_ENETC0_SI_BASE + 0x8000u)
#define IMXRT_NETC_SI_TBMR                (IMXRT_NETC_SI_BDR_BASE + 0x000u)
#define IMXRT_NETC_SI_TBBAR0              (IMXRT_NETC_SI_BDR_BASE + 0x010u)
#define IMXRT_NETC_SI_TBBAR1              (IMXRT_NETC_SI_BDR_BASE + 0x014u)
#define IMXRT_NETC_SI_TBPIR               (IMXRT_NETC_SI_BDR_BASE + 0x018u)
#define IMXRT_NETC_SI_TBCIR               (IMXRT_NETC_SI_BDR_BASE + 0x01cu)
#define IMXRT_NETC_SI_TBLENR              (IMXRT_NETC_SI_BDR_BASE + 0x020u)
#define IMXRT_NETC_SI_TBIER               (IMXRT_NETC_SI_BDR_BASE + 0x0a0u)
#define IMXRT_NETC_SI_RBMR                (IMXRT_NETC_SI_BDR_BASE + 0x100u)
#define IMXRT_NETC_SI_RBBSR               (IMXRT_NETC_SI_BDR_BASE + 0x108u)
#define IMXRT_NETC_SI_RBCIR               (IMXRT_NETC_SI_BDR_BASE + 0x10cu)
#define IMXRT_NETC_SI_RBBAR0              (IMXRT_NETC_SI_BDR_BASE + 0x110u)
#define IMXRT_NETC_SI_RBBAR1              (IMXRT_NETC_SI_BDR_BASE + 0x114u)
#define IMXRT_NETC_SI_RBPIR               (IMXRT_NETC_SI_BDR_BASE + 0x118u)
#define IMXRT_NETC_SI_RBLENR              (IMXRT_NETC_SI_BDR_BASE + 0x120u)
#define IMXRT_NETC_SI_RBIER               (IMXRT_NETC_SI_BDR_BASE + 0x1a0u)

#define NETC_SI_SIMR_ENABLE               (1u << 31)
#define NETC_SI_TBMR_ENABLE               (1u << 31)
#define NETC_SI_RBMR_ENABLE               (1u << 31)

#endif /* __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_NETC_H */
