/****************************************************************************
 * arch/arm/src/imxrt/hardware/rt118x/imxrt118x_bbnsm.h
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

#ifndef __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_BBNSM_H
#define __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_BBNSM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "hardware/imxrt_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Generated from NXP MIMXRT1186_cm33.xml (SVD). */

/* BBNSM Register Offsets (base IMXRT_BBNSM_BASE = 0x44440000) */

#define IMXRT_BBNSM_BBNSM_VID_OFFSET 0x0000  /* BBNSM Version ID Register */
#define IMXRT_BBNSM_BBNSM_FEATURES_OFFSET 0x0004  /* BBNSM Features Register */
#define IMXRT_BBNSM_BBNSM_CTRL_OFFSET 0x0008  /* BBNSM Control Register */
#define IMXRT_BBNSM_BBNSM_INT_EN_OFFSET 0x0010  /* BBNSM Interrupt Enable Register */
#define IMXRT_BBNSM_BBNSM_EVENTS_OFFSET 0x0014  /* BBNSM Events Register */
#define IMXRT_BBNSM_BBNSM_PAD_CTRL_OFFSET 0x0024  /* BBNSM External Pad Control Register */
#define IMXRT_BBNSM_BBNSM_RTC_LS_OFFSET 0x0040  /* BBNSM Real-Time Counter LS Register */
#define IMXRT_BBNSM_BBNSM_RTC_MS_OFFSET 0x0044  /* BBNSM Real-Time Counter MS Register */
#define IMXRT_BBNSM_BBNSM_TA_OFFSET 0x0050  /* BBNSM Time Alarm Register */
#define IMXRT_BBNSM_GPR_OFFSET(n) (0x0300 + ((unsigned)(n) * 4))  /* General Purpose Register Word word x8 */

/* BBNSM Register Addresses */

#define IMXRT_BBNSM_BBNSM_VID (IMXRT_BBNSM_BASE + IMXRT_BBNSM_BBNSM_VID_OFFSET)
#define IMXRT_BBNSM_BBNSM_FEATURES (IMXRT_BBNSM_BASE + IMXRT_BBNSM_BBNSM_FEATURES_OFFSET)
#define IMXRT_BBNSM_BBNSM_CTRL (IMXRT_BBNSM_BASE + IMXRT_BBNSM_BBNSM_CTRL_OFFSET)
#define IMXRT_BBNSM_BBNSM_INT_EN (IMXRT_BBNSM_BASE + IMXRT_BBNSM_BBNSM_INT_EN_OFFSET)
#define IMXRT_BBNSM_BBNSM_EVENTS (IMXRT_BBNSM_BASE + IMXRT_BBNSM_BBNSM_EVENTS_OFFSET)
#define IMXRT_BBNSM_BBNSM_PAD_CTRL (IMXRT_BBNSM_BASE + IMXRT_BBNSM_BBNSM_PAD_CTRL_OFFSET)
#define IMXRT_BBNSM_BBNSM_RTC_LS (IMXRT_BBNSM_BASE + IMXRT_BBNSM_BBNSM_RTC_LS_OFFSET)
#define IMXRT_BBNSM_BBNSM_RTC_MS (IMXRT_BBNSM_BASE + IMXRT_BBNSM_BBNSM_RTC_MS_OFFSET)
#define IMXRT_BBNSM_BBNSM_TA (IMXRT_BBNSM_BASE + IMXRT_BBNSM_BBNSM_TA_OFFSET)
#define IMXRT_BBNSM_GPR(n) (IMXRT_BBNSM_BASE + IMXRT_BBNSM_GPR_OFFSET(n))

/* BBNSM Bit Fields */

#define BBNSM_BBNSM_VID_BBNSM_IPID_SHIFT  (0)
#define BBNSM_BBNSM_VID_BBNSM_IPID_MASK   (0xffu << 0)
#define BBNSM_BBNSM_VID_BBNSM_REV_SHIFT  (8)
#define BBNSM_BBNSM_VID_BBNSM_REV_MASK   (0xffu << 8)
#define BBNSM_BBNSM_VID_BBNSM_VID_SHIFT  (16)
#define BBNSM_BBNSM_VID_BBNSM_VID_MASK   (0xffu << 16)

#define BBNSM_BBNSM_FEATURES_GPR_SZ_SHIFT  (2)
#define BBNSM_BBNSM_FEATURES_GPR_SZ_MASK   (0x3fu << 2)

#define BBNSM_BBNSM_CTRL_RTC_EN_SHIFT  (0)
#define BBNSM_BBNSM_CTRL_RTC_EN_MASK   (0x3u << 0)
#define BBNSM_BBNSM_CTRL_TA_EN_SHIFT  (2)
#define BBNSM_BBNSM_CTRL_TA_EN_MASK   (0x3u << 2)
#define BBNSM_BBNSM_CTRL_CAL_EN  (1u << 4)
#define BBNSM_BBNSM_CTRL_CAL_VAL_SHIFT  (8)
#define BBNSM_BBNSM_CTRL_CAL_VAL_MASK   (0x1fu << 8)
#define BBNSM_BBNSM_CTRL_BTN_TIMEOUT_SHIFT  (16)
#define BBNSM_BBNSM_CTRL_BTN_TIMEOUT_MASK   (0x3u << 16)
#define BBNSM_BBNSM_CTRL_DEBOUNCE_SHIFT  (18)
#define BBNSM_BBNSM_CTRL_DEBOUNCE_MASK   (0x3u << 18)
#define BBNSM_BBNSM_CTRL_TURN_ON_TIME_SHIFT  (20)
#define BBNSM_BBNSM_CTRL_TURN_ON_TIME_MASK   (0x3u << 20)
#define BBNSM_BBNSM_CTRL_PK_EN  (1u << 22)
#define BBNSM_BBNSM_CTRL_PK_OVR  (1u << 23)
#define BBNSM_BBNSM_CTRL_DP_EN  (1u << 24)
#define BBNSM_BBNSM_CTRL_TOSP  (1u << 25)

#define BBNSM_BBNSM_INT_EN_RTC_INT_EN_SHIFT  (0)
#define BBNSM_BBNSM_INT_EN_RTC_INT_EN_MASK   (0x3u << 0)
#define BBNSM_BBNSM_INT_EN_TA_INT_EN_SHIFT  (2)
#define BBNSM_BBNSM_INT_EN_TA_INT_EN_MASK   (0x3u << 2)

#define BBNSM_BBNSM_EVENTS_RTC_ROLL_SHIFT  (0)
#define BBNSM_BBNSM_EVENTS_RTC_ROLL_MASK   (0x3u << 0)
#define BBNSM_BBNSM_EVENTS_TA_SHIFT  (2)
#define BBNSM_BBNSM_EVENTS_TA_MASK   (0x3u << 2)
#define BBNSM_BBNSM_EVENTS_EMG_OFF  (1u << 4)
#define BBNSM_BBNSM_EVENTS_PWR_OFF  (1u << 5)
#define BBNSM_BBNSM_EVENTS_PWR_ON  (1u << 6)

#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL0  (1u << 0)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL1  (1u << 1)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL2  (1u << 2)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL3  (1u << 3)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL4  (1u << 4)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL5  (1u << 5)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL6  (1u << 6)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL7  (1u << 7)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL8  (1u << 8)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL9  (1u << 9)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL10  (1u << 10)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL11  (1u << 11)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL12  (1u << 12)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL13  (1u << 13)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL14  (1u << 14)
#define BBNSM_BBNSM_PAD_CTRL_PAD_CTRL15  (1u << 15)

#define BBNSM_BBNSM_RTC_LS_RTC_SHIFT  (0)
#define BBNSM_BBNSM_RTC_LS_RTC_MASK   (0xffffffffu << 0)

#define BBNSM_BBNSM_RTC_MS_RTC_SHIFT  (0)
#define BBNSM_BBNSM_RTC_MS_RTC_MASK   (0x7fffu << 0)

#define BBNSM_BBNSM_TA_TA_SHIFT  (0)
#define BBNSM_BBNSM_TA_TA_MASK   (0xffffffffu << 0)

#define BBNSM_GPR_GPR_SHIFT  (0)
#define BBNSM_GPR_GPR_MASK   (0xffffffffu << 0)

#endif /* __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_BBNSM_H */
