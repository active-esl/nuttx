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

#endif /* __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_NETC_H */
