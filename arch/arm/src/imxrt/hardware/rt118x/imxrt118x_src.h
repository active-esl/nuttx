/****************************************************************************
 * arch/arm/src/imxrt/hardware/rt118x/imxrt118x_src.h
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

#ifndef __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_SRC_H
#define __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_SRC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "hardware/imxrt_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Generated from NXP MIMXRT1186_cm33.xml (SVD). */

/* SRC_GENERAL_REG Register Offsets (base IMXRT_SRC_GENERAL_REG_BASE = 0x44460000) */

#define IMXRT_SRC_AUTHEN_CTRL_OFFSET 0x0004  /* Authentication Control */
#define IMXRT_SRC_SCR_OFFSET 0x0010  /* SRC Control Register */
#define IMXRT_SRC_SRTMR_OFFSET 0x0014  /* SRC Reset Trigger Mode Register */
#define IMXRT_SRC_SRMASK_OFFSET 0x0018  /* SRC Reset Mask Register */
#define IMXRT_SRC_SBMR1_OFFSET 0x0040  /* SRC Boot Mode Register 1 */
#define IMXRT_SRC_SBMR2_OFFSET 0x0044  /* SRC Boot Mode Register 2 */
#define IMXRT_SRC_SRSR_BBSM_OFFSET 0x004c  /* SRC Reset Status Register backup in BBSM domain */
#define IMXRT_SRC_SRSR_OFFSET 0x0050  /* SRC Reset Status Register */
#define IMXRT_SRC_GPR_OFFSET(n) (0x0054 + ((unsigned)(n) * 4))  /* SRC General Purpose Register x20 */

/* SRC_GENERAL_REG Register Addresses */

#define IMXRT_SRC_AUTHEN_CTRL (IMXRT_SRC_GENERAL_REG_BASE + IMXRT_SRC_AUTHEN_CTRL_OFFSET)
#define IMXRT_SRC_SCR (IMXRT_SRC_GENERAL_REG_BASE + IMXRT_SRC_SCR_OFFSET)
#define IMXRT_SRC_SRTMR (IMXRT_SRC_GENERAL_REG_BASE + IMXRT_SRC_SRTMR_OFFSET)
#define IMXRT_SRC_SRMASK (IMXRT_SRC_GENERAL_REG_BASE + IMXRT_SRC_SRMASK_OFFSET)
#define IMXRT_SRC_SBMR1 (IMXRT_SRC_GENERAL_REG_BASE + IMXRT_SRC_SBMR1_OFFSET)
#define IMXRT_SRC_SBMR2 (IMXRT_SRC_GENERAL_REG_BASE + IMXRT_SRC_SBMR2_OFFSET)
#define IMXRT_SRC_SRSR_BBSM (IMXRT_SRC_GENERAL_REG_BASE + IMXRT_SRC_SRSR_BBSM_OFFSET)
#define IMXRT_SRC_SRSR (IMXRT_SRC_GENERAL_REG_BASE + IMXRT_SRC_SRSR_OFFSET)
#define IMXRT_SRC_GPR(n) (IMXRT_SRC_GENERAL_REG_BASE + IMXRT_SRC_GPR_OFFSET(n))

/* SRC_GENERAL_REG Bit Fields */

#define SRC_AUTHEN_CTRL_LOCK_CFG  (1u << 7)
#define SRC_AUTHEN_CTRL_TZ_USER  (1u << 8)
#define SRC_AUTHEN_CTRL_TZ_NS  (1u << 9)
#define SRC_AUTHEN_CTRL_LOCK_TZ  (1u << 11)
#define SRC_AUTHEN_CTRL_LOCK_LIST  (1u << 15)
#define SRC_AUTHEN_CTRL_WHITE_LIST_SHIFT  (16)
#define SRC_AUTHEN_CTRL_WHITE_LIST_MASK   (0xffffu << 16)

#define SRC_SCR_BT_RELEASE_M7  (1u << 0)

#define SRC_SRTMR_WDOG1_TRIG_MODE  (1u << 0)
#define SRC_SRTMR_WDOG2_TRIG_MODE  (1u << 1)
#define SRC_SRTMR_WDOG3_TRIG_MODE  (1u << 2)
#define SRC_SRTMR_WDOG4_TRIG_MODE  (1u << 3)
#define SRC_SRTMR_WDOG5_TRIG_MODE  (1u << 4)
#define SRC_SRTMR_TEMPSENSE_TRIG_MODE  (1u << 5)
#define SRC_SRTMR_EDGELOCK_TRIG_MODE  (1u << 6)
#define SRC_SRTMR_JTAGSW_TRIG_MODE  (1u << 7)
#define SRC_SRTMR_CM33_RESET_TRIG_MODE  (1u << 8)
#define SRC_SRTMR_CM33_LOCKUP_TRIG_MODE  (1u << 9)
#define SRC_SRTMR_CM7_RESET_TRIG_MODE  (1u << 10)
#define SRC_SRTMR_CM7_LOCKUP_TRIG_MODE  (1u << 11)
#define SRC_SRTMR_DCDC_OVVT_TRIG_MODE  (1u << 12)
#define SRC_SRTMR_ECAT_RSTO_TRIG_MODE  (1u << 13)

#define SRC_SRMASK_WDOG1_MASK  (1u << 0)
#define SRC_SRMASK_WDOG2_MASK  (1u << 1)
#define SRC_SRMASK_WDOG3_MASK  (1u << 2)
#define SRC_SRMASK_WDOG4_MASK  (1u << 3)
#define SRC_SRMASK_WDOG5_MASK  (1u << 4)
#define SRC_SRMASK_TEMPSENSE_MASK  (1u << 5)
#define SRC_SRMASK_EDGELOCK_MASK  (1u << 6)
#define SRC_SRMASK_JTAGSW_MASK  (1u << 7)
#define SRC_SRMASK_CM33_RESET_MASK  (1u << 8)
#define SRC_SRMASK_CM33_LOCKUP_MASK  (1u << 9)
#define SRC_SRMASK_CM7_RESET_MASK  (1u << 10)
#define SRC_SRMASK_CM7_LOCKUP_MASK  (1u << 11)
#define SRC_SRMASK_DCDC_OVVT_MASK  (1u << 12)
#define SRC_SRMASK_ECAT_RSTO_MASK  (1u << 13)
#define SRC_SRMASK_WDOG1_MASK_LOCKED  (1u << 16)
#define SRC_SRMASK_WDOG2_MASK_LOCKED  (1u << 17)
#define SRC_SRMASK_WDOG3_MASK_LOCKED  (1u << 18)
#define SRC_SRMASK_WDOG4_MASK_LOCKED  (1u << 19)
#define SRC_SRMASK_WDOG5_MASK_LOCKED  (1u << 20)
#define SRC_SRMASK_TEMPSENSE_MASK_LOCKED  (1u << 21)
#define SRC_SRMASK_EDGELOCK_MASK_LOCKED  (1u << 22)
#define SRC_SRMASK_JTAGSW_MASK_LOCKED  (1u << 23)
#define SRC_SRMASK_CM33_RESET_MASK_LOCKED  (1u << 24)
#define SRC_SRMASK_CM33_LOCKUP_MASK_LOCKED  (1u << 25)
#define SRC_SRMASK_CM7_RESET_MASK_LOCKED  (1u << 26)
#define SRC_SRMASK_CM7_LOCKUP_MASK_LOCKED  (1u << 27)
#define SRC_SRMASK_DCDC_OVVT_MASK_LOCKED  (1u << 28)
#define SRC_SRMASK_ECAT_RSTO_MASK_LOCKED  (1u << 29)

#define SRC_SBMR1_BOOT_CFG1_SHIFT  (0)
#define SRC_SBMR1_BOOT_CFG1_MASK   (0xffu << 0)
#define SRC_SBMR1_BOOT_CFG2_SHIFT  (8)
#define SRC_SBMR1_BOOT_CFG2_MASK   (0xffu << 8)
#define SRC_SBMR1_BOOT_CFG3_SHIFT  (16)
#define SRC_SBMR1_BOOT_CFG3_MASK   (0xffu << 16)
#define SRC_SBMR1_BOOT_CFG4_SHIFT  (24)
#define SRC_SBMR1_BOOT_CFG4_MASK   (0xffu << 24)

#define SRC_SBMR2_IPP_BOOT_MODE_SHIFT  (24)
#define SRC_SBMR2_IPP_BOOT_MODE_MASK   (0x3fu << 24)

#define SRC_SRSR_BBSM_POR_RST  (1u << 0)
#define SRC_SRSR_BBSM_WDOG1_RST_B  (1u << 1)
#define SRC_SRSR_BBSM_WDOG2_RST_B  (1u << 2)
#define SRC_SRSR_BBSM_WDOG3_RST_B  (1u << 3)
#define SRC_SRSR_BBSM_WDOG4_RST_B  (1u << 4)
#define SRC_SRSR_BBSM_WDOG5_RST_B  (1u << 5)
#define SRC_SRSR_BBSM_TEMPSENSE_RST_B  (1u << 6)
#define SRC_SRSR_BBSM_EDGELOCK_RESET_B  (1u << 7)
#define SRC_SRSR_BBSM_JTAG_SW_RST  (1u << 8)
#define SRC_SRSR_BBSM_CM33_REQUEST  (1u << 9)
#define SRC_SRSR_BBSM_CM33_LOCKUP  (1u << 10)
#define SRC_SRSR_BBSM_CM7_REQUEST  (1u << 11)
#define SRC_SRSR_BBSM_CM7_LOCKUP  (1u << 12)
#define SRC_SRSR_BBSM_DCDC_OVVT  (1u << 13)
#define SRC_SRSR_BBSM_ECAT_RSTO  (1u << 14)

#define SRC_SRSR_POR_RST  (1u << 0)
#define SRC_SRSR_WDOG1_RST_B  (1u << 1)
#define SRC_SRSR_WDOG2_RST_B  (1u << 2)
#define SRC_SRSR_WDOG3_RST_B  (1u << 3)
#define SRC_SRSR_WDOG4_RST_B  (1u << 4)
#define SRC_SRSR_WDOG5_RST_B  (1u << 5)
#define SRC_SRSR_TEMPSENSE_RST_B  (1u << 6)
#define SRC_SRSR_EDGELOCK_RESET_B  (1u << 7)
#define SRC_SRSR_JTAG_SW_RST  (1u << 8)
#define SRC_SRSR_CM33_REQUEST  (1u << 9)
#define SRC_SRSR_CM33_LOCKUP  (1u << 10)
#define SRC_SRSR_CM7_REQUEST  (1u << 11)
#define SRC_SRSR_CM7_LOCKUP  (1u << 12)
#define SRC_SRSR_DCDC_OVVT  (1u << 13)
#define SRC_SRSR_ECAT_RSTO  (1u << 14)
#define SRC_SRSR_IPP_POR_B  (1u << 16)

#define SRC_GPR_GPR_SHIFT  (0)
#define SRC_GPR_GPR_MASK   (0xffffffffu << 0)

#endif /* __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_SRC_H */
