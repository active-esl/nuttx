/****************************************************************************
 * arch/arm/src/imxrt/hardware/rt118x/imxrt118x_dcdc.h
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

#ifndef __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_DCDC_H
#define __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_DCDC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "hardware/imxrt_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Generated from NXP MIMXRT1186_cm33.xml (SVD). */

/* DCDC Register Offsets (base IMXRT_DCDC_BASE = 0x44520000) */

#define IMXRT_DCDC_REG0_OFFSET 0x0000  /* DCDC Register 0 */
#define IMXRT_DCDC_REG1_OFFSET 0x0004  /* DCDC Register 1 */
#define IMXRT_DCDC_REG2_OFFSET 0x0008  /* DCDC Register 2 */
#define IMXRT_DCDC_REG3_OFFSET 0x000c  /* DCDC Register 3 */
#define IMXRT_DCDC_CTRL0_OFFSET 0x0010  /* DCDC Control Register 0 */
#define IMXRT_DCDC_OK_CNT_OFFSET 0x0014  /* OK CNT */
#define IMXRT_DCDC_CURRENT_TRG_OFFSET 0x0018  /* CURRENT TARGET VALUE for DCDC ANALOG */
#define IMXRT_DCDC_FILTER_CNT_OFFSET 0x001c  /* FILTER CNT */
#define IMXRT_DCDC_TRG_0_AUTHEN_OFFSET 0x0020  /* TRG_0 Authentication Control */
#define IMXRT_DCDC_TRG_SW_0_OFFSET 0x0024  /* Target SW Control for CORE 0 */
#define IMXRT_DCDC_TRG_GPC_0_OFFSET 0x0028  /* Target GPC Control for CORE 0 */
#define IMXRT_DCDC_TRG_1_AUTHEN_OFFSET 0x0030  /* TRG_1 Authentication Control */
#define IMXRT_DCDC_TRG_SW_1_OFFSET 0x0034  /* Target SW Control for CORE 1 */
#define IMXRT_DCDC_TRG_GPC_1_OFFSET 0x0038  /* Target GPC Control for CORE 1 */

/* DCDC Register Addresses */

#define IMXRT_DCDC_REG0 (IMXRT_DCDC_BASE + IMXRT_DCDC_REG0_OFFSET)
#define IMXRT_DCDC_REG1 (IMXRT_DCDC_BASE + IMXRT_DCDC_REG1_OFFSET)
#define IMXRT_DCDC_REG2 (IMXRT_DCDC_BASE + IMXRT_DCDC_REG2_OFFSET)
#define IMXRT_DCDC_REG3 (IMXRT_DCDC_BASE + IMXRT_DCDC_REG3_OFFSET)
#define IMXRT_DCDC_CTRL0 (IMXRT_DCDC_BASE + IMXRT_DCDC_CTRL0_OFFSET)
#define IMXRT_DCDC_OK_CNT (IMXRT_DCDC_BASE + IMXRT_DCDC_OK_CNT_OFFSET)
#define IMXRT_DCDC_CURRENT_TRG (IMXRT_DCDC_BASE + IMXRT_DCDC_CURRENT_TRG_OFFSET)
#define IMXRT_DCDC_FILTER_CNT (IMXRT_DCDC_BASE + IMXRT_DCDC_FILTER_CNT_OFFSET)
#define IMXRT_DCDC_TRG_0_AUTHEN (IMXRT_DCDC_BASE + IMXRT_DCDC_TRG_0_AUTHEN_OFFSET)
#define IMXRT_DCDC_TRG_SW_0 (IMXRT_DCDC_BASE + IMXRT_DCDC_TRG_SW_0_OFFSET)
#define IMXRT_DCDC_TRG_GPC_0 (IMXRT_DCDC_BASE + IMXRT_DCDC_TRG_GPC_0_OFFSET)
#define IMXRT_DCDC_TRG_1_AUTHEN (IMXRT_DCDC_BASE + IMXRT_DCDC_TRG_1_AUTHEN_OFFSET)
#define IMXRT_DCDC_TRG_SW_1 (IMXRT_DCDC_BASE + IMXRT_DCDC_TRG_SW_1_OFFSET)
#define IMXRT_DCDC_TRG_GPC_1 (IMXRT_DCDC_BASE + IMXRT_DCDC_TRG_GPC_1_OFFSET)

/* DCDC Bit Fields */

#define DCDC_REG0_PWD_ZCD  (1u << 0)
#define DCDC_REG0_DISABLE_AUTO_CLK_SWITCH  (1u << 1)
#define DCDC_REG0_SEL_CLK  (1u << 2)
#define DCDC_REG0_PWD_OSC_INT  (1u << 3)
#define DCDC_REG0_PWD_OVERCUR_DET  (1u << 8)
#define DCDC_REG0_OVERCUR_TRIG_ADJ_SHIFT  (9)
#define DCDC_REG0_OVERCUR_TRIG_ADJ_MASK   (0x3u << 9)
#define DCDC_REG0_PWD_CMP_DCDC_IN_DET  (1u << 11)
#define DCDC_REG0_PWD_HIGH_VDD1P8_DET  (1u << 16)
#define DCDC_REG0_PWD_HIGH_VDD1P0_DET  (1u << 17)
#define DCDC_REG0_PWD_CMP_OFFSET  (1u << 26)
#define DCDC_REG0_XTALOK_DISABLE  (1u << 27)
#define DCDC_REG0_XTAL_24M_OK  (1u << 29)
#define DCDC_REG0_STS_DC_OK  (1u << 31)

#define DCDC_REG1_RLOAD_REG_EN  (1u << 4)
#define DCDC_REG1_VBG_TRIM_SHIFT  (6)
#define DCDC_REG1_VBG_TRIM_MASK   (0x1fu << 6)
#define DCDC_REG1_NEGLIMIT_IN_SHIFT  (13)
#define DCDC_REG1_NEGLIMIT_IN_MASK   (0x7fu << 13)
#define DCDC_REG1_LOOPCTRL_CM_HST_THRESH  (1u << 27)
#define DCDC_REG1_LOOPCTRL_DF_HST_THRESH  (1u << 28)
#define DCDC_REG1_LOOPCTRL_EN_CM_HYST  (1u << 29)
#define DCDC_REG1_LOOPCTRL_EN_DF_HYST  (1u << 30)

#define DCDC_REG2_LOOPCTRL_DC_C_SHIFT  (0)
#define DCDC_REG2_LOOPCTRL_DC_C_MASK   (0x3u << 0)
#define DCDC_REG2_LOOPCTRL_DC_R_SHIFT  (2)
#define DCDC_REG2_LOOPCTRL_DC_R_MASK   (0xfu << 2)
#define DCDC_REG2_LOOPCTRL_DC_FF_SHIFT  (6)
#define DCDC_REG2_LOOPCTRL_DC_FF_MASK   (0x7u << 6)
#define DCDC_REG2_LOOPCTRL_EN_RCSCALE_SHIFT  (9)
#define DCDC_REG2_LOOPCTRL_EN_RCSCALE_MASK   (0x7u << 9)
#define DCDC_REG2_LOOPCTRL_RCSCALE_THRSH  (1u << 12)
#define DCDC_REG2_LOOPCTRL_HYST_SIGN  (1u << 13)
#define DCDC_REG2_BATTMONITOR_EN_BATADJ  (1u << 15)
#define DCDC_REG2_BATTMONITOR_BATT_VAL_SHIFT  (16)
#define DCDC_REG2_BATTMONITOR_BATT_VAL_MASK   (0x3ffu << 16)
#define DCDC_REG2_LOOPCTRL_TOGGLE_DIF  (1u << 30)

#define DCDC_REG3_IN_BROWNOUT_WARN  (1u << 9)
#define DCDC_REG3_ENABLE_FF  (1u << 18)
#define DCDC_REG3_DISABLE_PULSE_SKIP  (1u << 19)
#define DCDC_REG3_DISABLE_IDLE_SKIP  (1u << 20)
#define DCDC_REG3_DOUBLE_IBIAS_CMP_LP  (1u << 21)
#define DCDC_REG3_REG_FBK_SEL_SHIFT  (22)
#define DCDC_REG3_REG_FBK_SEL_MASK   (0x3u << 22)
#define DCDC_REG3_MINPWR_HALF_FETS  (1u << 26)
#define DCDC_REG3_MISC_DELAY_TIMING  (1u << 27)
#define DCDC_REG3_VDD1P0CTRL_DISABLE_STEP  (1u << 29)

#define DCDC_CTRL0_ENABLE_OK_CNT  (1u << 5)
#define DCDC_CTRL0_TRIM_HOLD  (1u << 6)
#define DCDC_CTRL0_IN_BROWNOUT_WARN_EN  (1u << 9)
#define DCDC_CTRL0_DCDC_1P8_STABILITY  (1u << 22)
#define DCDC_CTRL0_TRG_GPC_EN  (1u << 31)

#define DCDC_OK_CNT_OK_COUNT_SHIFT  (0)
#define DCDC_OK_CNT_OK_COUNT_MASK   (0xffffffffu << 0)

#define DCDC_CURRENT_TRG_VDD1P0CTRL_TRG_SHIFT  (0)
#define DCDC_CURRENT_TRG_VDD1P0CTRL_TRG_MASK   (0x1fu << 0)
#define DCDC_CURRENT_TRG_VDD1P8CTRL_TRG_SHIFT  (8)
#define DCDC_CURRENT_TRG_VDD1P8CTRL_TRG_MASK   (0x1fu << 8)
#define DCDC_CURRENT_TRG_DCDC_UPDATING  (1u << 15)
#define DCDC_CURRENT_TRG_VDD1P0CTRL_LP_TRG_SHIFT  (16)
#define DCDC_CURRENT_TRG_VDD1P0CTRL_LP_TRG_MASK   (0x1fu << 16)
#define DCDC_CURRENT_TRG_LP_EN_1P0  (1u << 31)

#define DCDC_FILTER_CNT_FILTER_CNT_CFG_SHIFT  (0)
#define DCDC_FILTER_CNT_FILTER_CNT_CFG_MASK   (0xffffffffu << 0)

#define DCDC_TRG_0_AUTHEN_TZ_USER  (1u << 8)
#define DCDC_TRG_0_AUTHEN_TZ_NS  (1u << 9)
#define DCDC_TRG_0_AUTHEN_LOCK_TZ  (1u << 11)
#define DCDC_TRG_0_AUTHEN_LOCK_LIST  (1u << 15)
#define DCDC_TRG_0_AUTHEN_WHITE_LIST_SHIFT  (16)
#define DCDC_TRG_0_AUTHEN_WHITE_LIST_MASK   (0xffffu << 16)

#define DCDC_TRG_SW_0_VDD1P0CTRL_TRG_SHIFT  (0)
#define DCDC_TRG_SW_0_VDD1P0CTRL_TRG_MASK   (0x1fu << 0)
#define DCDC_TRG_SW_0_VDD1P8CTRL_TRG_SHIFT  (8)
#define DCDC_TRG_SW_0_VDD1P8CTRL_TRG_MASK   (0x1fu << 8)
#define DCDC_TRG_SW_0_VDD1P0CTRL_LP_TRG_SHIFT  (16)
#define DCDC_TRG_SW_0_VDD1P0CTRL_LP_TRG_MASK   (0x1fu << 16)
#define DCDC_TRG_SW_0_LP_EN_1P0  (1u << 31)

#define DCDC_TRG_GPC_0_VDD1P0CTRL_TRG_SHIFT  (0)
#define DCDC_TRG_GPC_0_VDD1P0CTRL_TRG_MASK   (0x1fu << 0)
#define DCDC_TRG_GPC_0_VDD1P8CTRL_TRG_SHIFT  (8)
#define DCDC_TRG_GPC_0_VDD1P8CTRL_TRG_MASK   (0x1fu << 8)
#define DCDC_TRG_GPC_0_VDD1P0CTRL_LP_TRG_SHIFT  (16)
#define DCDC_TRG_GPC_0_VDD1P0CTRL_LP_TRG_MASK   (0x1fu << 16)
#define DCDC_TRG_GPC_0_LP_EN_1P0  (1u << 31)

#define DCDC_TRG_1_AUTHEN_TZ_USER  (1u << 8)
#define DCDC_TRG_1_AUTHEN_TZ_NS  (1u << 9)
#define DCDC_TRG_1_AUTHEN_LOCK_TZ  (1u << 11)
#define DCDC_TRG_1_AUTHEN_LOCK_LIST  (1u << 15)
#define DCDC_TRG_1_AUTHEN_WHITE_LIST_SHIFT  (16)
#define DCDC_TRG_1_AUTHEN_WHITE_LIST_MASK   (0xffffu << 16)

#define DCDC_TRG_SW_1_VDD1P0CTRL_TRG_SHIFT  (0)
#define DCDC_TRG_SW_1_VDD1P0CTRL_TRG_MASK   (0x1fu << 0)
#define DCDC_TRG_SW_1_VDD1P8CTRL_TRG_SHIFT  (8)
#define DCDC_TRG_SW_1_VDD1P8CTRL_TRG_MASK   (0x1fu << 8)
#define DCDC_TRG_SW_1_VDD1P0CTRL_LP_TRG_SHIFT  (16)
#define DCDC_TRG_SW_1_VDD1P0CTRL_LP_TRG_MASK   (0x1fu << 16)
#define DCDC_TRG_SW_1_LP_EN_1P0  (1u << 31)

#define DCDC_TRG_GPC_1_VDD1P0CTRL_TRG_SHIFT  (0)
#define DCDC_TRG_GPC_1_VDD1P0CTRL_TRG_MASK   (0x1fu << 0)
#define DCDC_TRG_GPC_1_VDD1P8CTRL_TRG_SHIFT  (8)
#define DCDC_TRG_GPC_1_VDD1P8CTRL_TRG_MASK   (0x1fu << 8)
#define DCDC_TRG_GPC_1_VDD1P0CTRL_LP_TRG_SHIFT  (16)
#define DCDC_TRG_GPC_1_VDD1P0CTRL_LP_TRG_MASK   (0x1fu << 16)
#define DCDC_TRG_GPC_1_LP_EN_1P0  (1u << 31)

#endif /* __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_DCDC_H */
