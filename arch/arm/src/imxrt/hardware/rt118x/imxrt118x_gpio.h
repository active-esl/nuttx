/****************************************************************************
 * arch/arm/src/imxrt/hardware/rt118x/imxrt118x_gpio.h
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

#ifndef __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_GPIO_H
#define __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_GPIO_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "hardware/imxrt_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RGPIO register offsets from MIMXRT1186_cm33.xml (RGPIO1..6 share layout). */

#define IMXRT_GPIO_VERID_OFFSET  0x0000
#define IMXRT_GPIO_PARAM_OFFSET  0x0004
#define IMXRT_GPIO_LOCK_OFFSET  0x000c
#define IMXRT_GPIO_PCNS_OFFSET  0x0010
#define IMXRT_GPIO_ICNS_OFFSET  0x0014
#define IMXRT_GPIO_PCNP_OFFSET  0x0018
#define IMXRT_GPIO_ICNP_OFFSET  0x001c
#define IMXRT_GPIO_PDOR_OFFSET  0x0040
#define IMXRT_GPIO_PSOR_OFFSET  0x0044
#define IMXRT_GPIO_PCOR_OFFSET  0x0048
#define IMXRT_GPIO_PTOR_OFFSET  0x004c
#define IMXRT_GPIO_PDIR_OFFSET  0x0050
#define IMXRT_GPIO_PDDR_OFFSET  0x0054
#define IMXRT_GPIO_PIDR_OFFSET  0x0058
#define IMXRT_GPIO_PDR_OFFSET(n)  (0x0060 + ((unsigned)(n) * 1))
#define IMXRT_GPIO_ICR0_OFFSET  0x0080
#define IMXRT_GPIO_ICR1_OFFSET  0x0084
#define IMXRT_GPIO_ICR2_OFFSET  0x0088
#define IMXRT_GPIO_ICR3_OFFSET  0x008c
#define IMXRT_GPIO_ICR4_OFFSET  0x0090
#define IMXRT_GPIO_ICR5_OFFSET  0x0094
#define IMXRT_GPIO_ICR6_OFFSET  0x0098
#define IMXRT_GPIO_ICR7_OFFSET  0x009c
#define IMXRT_GPIO_ICR8_OFFSET  0x00a0
#define IMXRT_GPIO_ICR9_OFFSET  0x00a4
#define IMXRT_GPIO_ICR10_OFFSET  0x00a8
#define IMXRT_GPIO_ICR11_OFFSET  0x00ac
#define IMXRT_GPIO_ICR12_OFFSET  0x00b0
#define IMXRT_GPIO_ICR13_OFFSET  0x00b4
#define IMXRT_GPIO_ICR14_OFFSET  0x00b8
#define IMXRT_GPIO_ICR15_OFFSET  0x00bc
#define IMXRT_GPIO_ICR16_OFFSET  0x00c0
#define IMXRT_GPIO_ICR17_OFFSET  0x00c4
#define IMXRT_GPIO_ICR18_OFFSET  0x00c8
#define IMXRT_GPIO_ICR19_OFFSET  0x00cc
#define IMXRT_GPIO_ICR20_OFFSET  0x00d0
#define IMXRT_GPIO_ICR21_OFFSET  0x00d4
#define IMXRT_GPIO_ICR22_OFFSET  0x00d8
#define IMXRT_GPIO_ICR23_OFFSET  0x00dc
#define IMXRT_GPIO_ICR24_OFFSET  0x00e0
#define IMXRT_GPIO_ICR25_OFFSET  0x00e4
#define IMXRT_GPIO_ICR26_OFFSET  0x00e8
#define IMXRT_GPIO_ICR27_OFFSET  0x00ec
#define IMXRT_GPIO_ICR28_OFFSET  0x00f0
#define IMXRT_GPIO_ICR29_OFFSET  0x00f4
#define IMXRT_GPIO_ICR30_OFFSET  0x00f8
#define IMXRT_GPIO_ICR31_OFFSET  0x00fc
#define IMXRT_GPIO_GICLR_OFFSET  0x0100
#define IMXRT_GPIO_GICHR_OFFSET  0x0104
#define IMXRT_GPIO_ISFR_OFFSET(n)  (0x0120 + ((unsigned)(n) * 4))

/* Compatibility aliases for earlier RT118x bring-up names */

#define IMXRT_GPIO_DR_OFFSET     IMXRT_GPIO_PDOR_OFFSET
#define IMXRT_GPIO_GDIR_OFFSET   IMXRT_GPIO_PDDR_OFFSET
#define IMXRT_GPIO_PSR_OFFSET    IMXRT_GPIO_PDIR_OFFSET
#define IMXRT_GPIO_SET_OFFSET    IMXRT_GPIO_PSOR_OFFSET
#define IMXRT_GPIO_CLEAR_OFFSET  IMXRT_GPIO_PCOR_OFFSET
#define IMXRT_GPIO_TOGGLE_OFFSET IMXRT_GPIO_PTOR_OFFSET

#endif /* __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_GPIO_H */
