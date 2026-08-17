/****************************************************************************
 * arch/arm/include/imxrt/imxrt118x_irq.h
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

/* This file should never be included directly but, rather,
 * only indirectly through nuttx/irq.h
 */

#ifndef __ARCH_ARM_INCLUDE_IMXRT_IMXRT118X_IRQ_H
#define __ARCH_ARM_INCLUDE_IMXRT_IMXRT118X_IRQ_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* External interrupts (vectors >= 16).
 * Numbers match NXP MIMXRT1186 CMSIS IRQn_Type (device IRQn + 16 = NuttX
 * vector). Generated from MIMXRT1186_cm33_COMMON.h / MIMXRT1186_cm33.xml.
 */

#define IMXRT_IRQ_TMR1                   (IMXRT_IRQ_EXTINT + 0)  /* TMR1 interrupt */
#define IMXRT_IRQ_DAP                    (IMXRT_IRQ_EXTINT + 1)  /* DAP interrupt */
#define IMXRT_IRQ_M7_CTI_TRIGGER_OUTPUT  (IMXRT_IRQ_EXTINT + 2)  /* CTI trigger outputs from CM7 */
#define IMXRT_IRQ_M33_CTI_TRIGGER_OUTPUT (IMXRT_IRQ_EXTINT + 3)  /* CTI trigger outputs from CM33 */
#define IMXRT_IRQ_TMR5                   (IMXRT_IRQ_EXTINT + 4)  /* TMR5 interrupt */
#define IMXRT_IRQ_TMR6                   (IMXRT_IRQ_EXTINT + 5)  /* TMR6 interrupt */
#define IMXRT_IRQ_TMR7                   (IMXRT_IRQ_EXTINT + 6)  /* TMR7 interrupt */
#define IMXRT_IRQ_TMR8                   (IMXRT_IRQ_EXTINT + 7)  /* TMR8 interrupt */
#define IMXRT_IRQ_CAN1                   (IMXRT_IRQ_EXTINT + 8)  /* CAN1 interrupt */
#define IMXRT_IRQ_CAN1_ERROR             (IMXRT_IRQ_EXTINT + 9)  /* CAN1 error interrupt */
#define IMXRT_IRQ_GPIO1_0                (IMXRT_IRQ_EXTINT + 10)  /* GPIO1 interrupt 0 */
#define IMXRT_IRQ_GPIO1_1                (IMXRT_IRQ_EXTINT + 11)  /* GPIO1 interrupt 1 */
#define IMXRT_IRQ_I3C1                   (IMXRT_IRQ_EXTINT + 12)  /* I3C1 interrupt */
#define IMXRT_IRQ_LPI2C1                 (IMXRT_IRQ_EXTINT + 13)  /* LPI2C1 interrupt */
#define IMXRT_IRQ_LPI2C2                 (IMXRT_IRQ_EXTINT + 14)  /* LPI2C2 interrupt */
#define IMXRT_IRQ_LPIT1                  (IMXRT_IRQ_EXTINT + 15)  /* LPIT1 interrupt */
#define IMXRT_IRQ_LPSPI1                 (IMXRT_IRQ_EXTINT + 16)  /* LPSPI1 interrupt */
#define IMXRT_IRQ_LPSPI2                 (IMXRT_IRQ_EXTINT + 17)  /* LPSPI2 interrupt */
#define IMXRT_IRQ_LPTMR1                 (IMXRT_IRQ_EXTINT + 18)  /* LPTMR1 interrupt */
#define IMXRT_IRQ_LPUART1                (IMXRT_IRQ_EXTINT + 19)  /* LPUART1 interrupt */
#define IMXRT_IRQ_LPUART2                (IMXRT_IRQ_EXTINT + 20)  /* LPUART2 interrupt */
#define IMXRT_IRQ_MU1                    (IMXRT_IRQ_EXTINT + 21)  /* MU1 interrupt */
#define IMXRT_IRQ_MU2                    (IMXRT_IRQ_EXTINT + 22)  /* MU2 interrupt */
#define IMXRT_IRQ_PWM1_FAULT             (IMXRT_IRQ_EXTINT + 23)  /* PWM1 fault or reload error interrupt */
#define IMXRT_IRQ_PWM1_0                 (IMXRT_IRQ_EXTINT + 24)  /* PWM1 capture 0, compare 0, or reload 0 interrupt */
#define IMXRT_IRQ_PWM1_1                 (IMXRT_IRQ_EXTINT + 25)  /* PWM1 capture 1, compare 1, or reload 1 interrupt */
#define IMXRT_IRQ_PWM1_2                 (IMXRT_IRQ_EXTINT + 26)  /* PWM1 capture 2, compare 2, or reload 2 interrupt */
#define IMXRT_IRQ_PWM1_3                 (IMXRT_IRQ_EXTINT + 27)  /* PWM1 capture 3, compare 3, or reload 3 interrupt */
#define IMXRT_IRQ_EDGELOCK_TRUST_MUA_RX_FULL (IMXRT_IRQ_EXTINT + 28)  /* Edgelock Trust MUA RX full interrupt */
#define IMXRT_IRQ_EDGELOCK_TRUST_MUA_TX_EMPTY (IMXRT_IRQ_EXTINT + 29)  /* Edgelock Trust MUA TX empty interrupt */
#define IMXRT_IRQ_EDGELOCK_APPS_CORE_MUA_RX_FULL (IMXRT_IRQ_EXTINT + 30)  /* Edgelock Apps Core MUA RX full interrupt */
#define IMXRT_IRQ_EDGELOCK_APPS_CORE_MUA_TX_EMPTY (IMXRT_IRQ_EXTINT + 31)  /* Edgelock Apps Core MUA TX empty interrupt */
#define IMXRT_IRQ_EDGELOCK_REALTIME_CORE_MUA_RX_FULL (IMXRT_IRQ_EXTINT + 32)  /* Edgelock Realtime Core MUA RX full interrupt */
#define IMXRT_IRQ_EDGELOCK_REALTIME_CORE_MUA_TX_EMPTY (IMXRT_IRQ_EXTINT + 33)  /* Edgelock Realtime Core MUA TX empty interrupt */
#define IMXRT_IRQ_EDGELOCK_SECURE        (IMXRT_IRQ_EXTINT + 34)  /* Edgelock secure interrupt */
#define IMXRT_IRQ_EDGELOCK_NONSECURE     (IMXRT_IRQ_EXTINT + 35)  /* Edgelock non-secure interrupt */
#define IMXRT_IRQ_TPM1                   (IMXRT_IRQ_EXTINT + 36)  /* TPM1 interrupt */
#define IMXRT_IRQ_TPM2                   (IMXRT_IRQ_EXTINT + 37)  /* TPM2 interrupt */
#define IMXRT_IRQ_RTWDOG1                (IMXRT_IRQ_EXTINT + 38)  /* RTWDOG1 interrupt */
#define IMXRT_IRQ_RTWDOG2                (IMXRT_IRQ_EXTINT + 39)  /* RTWDOG2 interrupt */
#define IMXRT_IRQ_TRDC_MGR_AON           (IMXRT_IRQ_EXTINT + 40)  /* AONMIX TRDC transfer error interrupt */
#define IMXRT_IRQ_PDM_HWVAD_EVENT        (IMXRT_IRQ_EXTINT + 41)  /* HWVAD event interrupt */
#define IMXRT_IRQ_PDM_HWVAD_ERROR        (IMXRT_IRQ_EXTINT + 42)  /* HWVAD error interrupt */
#define IMXRT_IRQ_PDM_EVENT              (IMXRT_IRQ_EXTINT + 43)  /* PDM event interrupt */
#define IMXRT_IRQ_PDM_ERROR              (IMXRT_IRQ_EXTINT + 44)  /* PDM error interrupt */
#define IMXRT_IRQ_SAI1                   (IMXRT_IRQ_EXTINT + 45)  /* SAI interrupt */
#define IMXRT_IRQ_CM33_PS                (IMXRT_IRQ_EXTINT + 46)  /* M33 PS Tag/Data Parity Error */
#define IMXRT_IRQ_CM33_TCM_ECC           (IMXRT_IRQ_EXTINT + 47)  /* M33 TCM ECC interrupt */
#define IMXRT_IRQ_CM33_TCM_ERROR         (IMXRT_IRQ_EXTINT + 48)  /* M33 TCM Error interrupt */
#define IMXRT_IRQ_CM7_TCM_ECC            (IMXRT_IRQ_EXTINT + 49)  /* M7 TCM ECC interrupt */
#define IMXRT_IRQ_CM7_TCM_ERROR          (IMXRT_IRQ_EXTINT + 50)  /* M7 TCM Error interrupt */
#define IMXRT_IRQ_Reserved67             (IMXRT_IRQ_EXTINT + 51)  /* Reserved interrupt */
#define IMXRT_IRQ_Reserved68             (IMXRT_IRQ_EXTINT + 52)  /* Reserved interrupt */
#define IMXRT_IRQ_FLEXIO1                (IMXRT_IRQ_EXTINT + 53)  /* FLEXIO1 interrupt */
#define IMXRT_IRQ_FLEXIO2                (IMXRT_IRQ_EXTINT + 54)  /* FLEXIO2 interrupt */
#define IMXRT_IRQ_FLEXSPI1               (IMXRT_IRQ_EXTINT + 55)  /* FLEXSPI1 interrupt */
#define IMXRT_IRQ_FLEXSPI2               (IMXRT_IRQ_EXTINT + 56)  /* FLEXSPI2 interrupt */
#define IMXRT_IRQ_GPIO2_0                (IMXRT_IRQ_EXTINT + 57)  /* GPIO2 interrupt 0 */
#define IMXRT_IRQ_GPIO2_1                (IMXRT_IRQ_EXTINT + 58)  /* GPIO2 interrupt 1 */
#define IMXRT_IRQ_GPIO3_0                (IMXRT_IRQ_EXTINT + 59)  /* GPIO3 interrupt 0 */
#define IMXRT_IRQ_GPIO3_1                (IMXRT_IRQ_EXTINT + 60)  /* GPIO3 interrupt 1 */
#define IMXRT_IRQ_I3C2                   (IMXRT_IRQ_EXTINT + 61)  /* I3C2 interrupt */
#define IMXRT_IRQ_LPI2C3                 (IMXRT_IRQ_EXTINT + 62)  /* LPI2C3 interrupt */
#define IMXRT_IRQ_Reserved79             (IMXRT_IRQ_EXTINT + 63)  /* Reserved interrupt */
#define IMXRT_IRQ_LPIT2                  (IMXRT_IRQ_EXTINT + 64)  /* LPIT2 interrupt */
#define IMXRT_IRQ_LPSPI3                 (IMXRT_IRQ_EXTINT + 65)  /* LPSPI3 interrupt */
#define IMXRT_IRQ_LPSPI4                 (IMXRT_IRQ_EXTINT + 66)  /* LPSPI4 interrupt */
#define IMXRT_IRQ_LPTMR2                 (IMXRT_IRQ_EXTINT + 67)  /* LPTMR2 interrupt */
#define IMXRT_IRQ_LPUART3                (IMXRT_IRQ_EXTINT + 68)  /* LPUART3 interrupt */
#define IMXRT_IRQ_LPUART4                (IMXRT_IRQ_EXTINT + 69)  /* LPUART4 interrupt */
#define IMXRT_IRQ_LPUART5                (IMXRT_IRQ_EXTINT + 70)  /* LPUART5 interrupt */
#define IMXRT_IRQ_LPUART6                (IMXRT_IRQ_EXTINT + 71)  /* LPUART6 interrupt */
#define IMXRT_IRQ_Reserved88             (IMXRT_IRQ_EXTINT + 72)  /* Reserved interrupt 88 */
#define IMXRT_IRQ_BBNSM                  (IMXRT_IRQ_EXTINT + 73)  /* BBNSM iterrupt */
#define IMXRT_IRQ_SYS_CTR1               (IMXRT_IRQ_EXTINT + 74)  /* System Counter compare interrupt 0 and 1 */
#define IMXRT_IRQ_TPM3                   (IMXRT_IRQ_EXTINT + 75)  /* TPM3 interrupt */
#define IMXRT_IRQ_TPM4                   (IMXRT_IRQ_EXTINT + 76)  /* TPM4 interrupt */
#define IMXRT_IRQ_Reserved93             (IMXRT_IRQ_EXTINT + 77)  /* Reserved interrupt */
#define IMXRT_IRQ_Reserved94             (IMXRT_IRQ_EXTINT + 78)  /* Reserved interrupt */
#define IMXRT_IRQ_RTWDOG3                (IMXRT_IRQ_EXTINT + 79)  /* RTWDOG3 interrupt */
#define IMXRT_IRQ_RTWDOG4                (IMXRT_IRQ_EXTINT + 80)  /* RTWDOG4 interrupt */
#define IMXRT_IRQ_RTWDOG5                (IMXRT_IRQ_EXTINT + 81)  /* RTWDOG5 interrupt */
#define IMXRT_IRQ_TRDC_MGR_WKUP          (IMXRT_IRQ_EXTINT + 82)  /* WAKEUPMIX TRDC transfer error interrupt */
#define IMXRT_IRQ_TMPSNS_INT             (IMXRT_IRQ_EXTINT + 83)  /* Temperature alarm interrupt */
#define IMXRT_IRQ_BBSM                   (IMXRT_IRQ_EXTINT + 84)  /* BBSM wakeup alarm interrupt */
#define IMXRT_IRQ_LDO_AON_ANA            (IMXRT_IRQ_EXTINT + 85)  /* Brown out interrupt */
#define IMXRT_IRQ_Reserved102            (IMXRT_IRQ_EXTINT + 86)  /* Reserved interrupt */
#define IMXRT_IRQ_USDHC2                 (IMXRT_IRQ_EXTINT + 87)  /* USDHC2 */
#define IMXRT_IRQ_TRDC_MGR_MEGA          (IMXRT_IRQ_EXTINT + 88)  /* MEGAMIX TRDC transfer error interrupt */
#define IMXRT_IRQ_SFA                    (IMXRT_IRQ_EXTINT + 89)  /* Signal Frequency Analyzer interrupt */
#define IMXRT_IRQ_LDO_AON_DIG            (IMXRT_IRQ_EXTINT + 90)  /* Brown out interrupt */
#define IMXRT_IRQ_MECC1                  (IMXRT_IRQ_EXTINT + 91)  /* MECC1 interrupt */
#define IMXRT_IRQ_MECC2                  (IMXRT_IRQ_EXTINT + 92)  /* MECC2 interrupt */
#define IMXRT_IRQ_ADC1                   (IMXRT_IRQ_EXTINT + 93)  /* ADC1 interrupt */
#define IMXRT_IRQ_DMA_ERROR              (IMXRT_IRQ_EXTINT + 94)  /* AON Domain eDMA error interrupt */
#define IMXRT_IRQ_DMA3_CH0               (IMXRT_IRQ_EXTINT + 95)  /* AON Domain eDMA channel 0 interrupt */
#define IMXRT_IRQ_DMA3_CH1               (IMXRT_IRQ_EXTINT + 96)  /* AON Domain eDMA channel 1 interrupt */
#define IMXRT_IRQ_DMA3_CH2               (IMXRT_IRQ_EXTINT + 97)  /* AON Domain eDMA channel 2 interrupt */
#define IMXRT_IRQ_DMA3_CH3               (IMXRT_IRQ_EXTINT + 98)  /* AON Domain eDMA channel 3 interrupt */
#define IMXRT_IRQ_DMA3_CH4               (IMXRT_IRQ_EXTINT + 99)  /* AON Domain eDMA channel 4 interrupt */
#define IMXRT_IRQ_DMA3_CH5               (IMXRT_IRQ_EXTINT + 100)  /* AON Domain eDMA channel 5 interrupt */
#define IMXRT_IRQ_DMA3_CH6               (IMXRT_IRQ_EXTINT + 101)  /* AON Domain eDMA channel 6 interrupt */
#define IMXRT_IRQ_DMA3_CH7               (IMXRT_IRQ_EXTINT + 102)  /* AON Domain eDMA channel 7 interrupt */
#define IMXRT_IRQ_DMA3_CH8               (IMXRT_IRQ_EXTINT + 103)  /* AON Domain eDMA channel 8 interrupt */
#define IMXRT_IRQ_DMA3_CH9               (IMXRT_IRQ_EXTINT + 104)  /* AON Domain eDMA channel 9 interrupt */
#define IMXRT_IRQ_DMA3_CH10              (IMXRT_IRQ_EXTINT + 105)  /* AON Domain eDMA channel 10 interrupt */
#define IMXRT_IRQ_DMA3_CH11              (IMXRT_IRQ_EXTINT + 106)  /* AON Domain eDMA channel 11 interrupt */
#define IMXRT_IRQ_DMA3_CH12              (IMXRT_IRQ_EXTINT + 107)  /* AON Domain eDMA channel 12 interrupt */
#define IMXRT_IRQ_DMA3_CH13              (IMXRT_IRQ_EXTINT + 108)  /* AON Domain eDMA channel 13 interrupt */
#define IMXRT_IRQ_DMA3_CH14              (IMXRT_IRQ_EXTINT + 109)  /* AON Domain eDMA channel 14 interrupt */
#define IMXRT_IRQ_DMA3_CH15              (IMXRT_IRQ_EXTINT + 110)  /* AON Domain eDMA channel 15 interrupt */
#define IMXRT_IRQ_DMA3_CH16              (IMXRT_IRQ_EXTINT + 111)  /* AON Domain eDMA channel 16 interrupt */
#define IMXRT_IRQ_DMA3_CH17              (IMXRT_IRQ_EXTINT + 112)  /* AON Domain eDMA channel 17 interrupt */
#define IMXRT_IRQ_DMA3_CH18              (IMXRT_IRQ_EXTINT + 113)  /* AON Domain eDMA channel 18 interrupt */
#define IMXRT_IRQ_DMA3_CH19              (IMXRT_IRQ_EXTINT + 114)  /* AON Domain eDMA channel 19 interrupt */
#define IMXRT_IRQ_DMA3_CH20              (IMXRT_IRQ_EXTINT + 115)  /* AON Domain eDMA channel 20 interrupt */
#define IMXRT_IRQ_DMA3_CH21              (IMXRT_IRQ_EXTINT + 116)  /* AON Domain eDMA channel 21 interrupt */
#define IMXRT_IRQ_DMA3_CH22              (IMXRT_IRQ_EXTINT + 117)  /* AON Domain eDMA channel 22 interrupt */
#define IMXRT_IRQ_DMA3_CH23              (IMXRT_IRQ_EXTINT + 118)  /* AON Domain eDMA channel 23 interrupt */
#define IMXRT_IRQ_DMA3_CH24              (IMXRT_IRQ_EXTINT + 119)  /* AON Domain eDMA channel 24 interrupt */
#define IMXRT_IRQ_DMA3_CH25              (IMXRT_IRQ_EXTINT + 120)  /* AON Domain eDMA channel 25 interrupt */
#define IMXRT_IRQ_DMA3_CH26              (IMXRT_IRQ_EXTINT + 121)  /* AON Domain eDMA channel 26 interrupt */
#define IMXRT_IRQ_DMA3_CH27              (IMXRT_IRQ_EXTINT + 122)  /* AON Domain eDMA channel 27 interrupt */
#define IMXRT_IRQ_DMA3_CH28              (IMXRT_IRQ_EXTINT + 123)  /* AON Domain eDMA channel 28 interrupt */
#define IMXRT_IRQ_DMA3_CH29              (IMXRT_IRQ_EXTINT + 124)  /* AON Domain eDMA channel 29 interrupt */
#define IMXRT_IRQ_DMA3_CH30              (IMXRT_IRQ_EXTINT + 125)  /* AON Domain eDMA channel 30 interrupt */
#define IMXRT_IRQ_DMA3_CH31              (IMXRT_IRQ_EXTINT + 126)  /* AON Domain eDMA channel 31 interrupt */
#define IMXRT_IRQ_DMA4_ERROR             (IMXRT_IRQ_EXTINT + 127)  /* WAKEUP Domain eDMA error interrupt */
#define IMXRT_IRQ_DMA4_CH0_CH1_CH32_CH33 (IMXRT_IRQ_EXTINT + 128)  /* WAKEUP Domain eDMA channel 0/1/32/33 interrupt */
#define IMXRT_IRQ_DMA4_CH2_CH3_CH34_CH35 (IMXRT_IRQ_EXTINT + 129)  /* WAKEUP Domain eDMA channel 2/3/34/35 interrupt */
#define IMXRT_IRQ_DMA4_CH4_CH5_CH36_CH37 (IMXRT_IRQ_EXTINT + 130)  /* WAKEUP Domain eDMA channel 4/5/36/37 interrupt */
#define IMXRT_IRQ_DMA4_CH6_CH7_CH38_CH39 (IMXRT_IRQ_EXTINT + 131)  /* WAKEUP Domain eDMA channel 6/7/38/39 interrupt */
#define IMXRT_IRQ_DMA4_CH8_CH9_CH40_CH41 (IMXRT_IRQ_EXTINT + 132)  /* WAKEUP Domain eDMA channel 8/9/40/41 interrupt */
#define IMXRT_IRQ_DMA4_CH10_CH11_CH42_CH43 (IMXRT_IRQ_EXTINT + 133)  /* WAKEUP Domain eDMA channel 10/11/42/43 interrupt */
#define IMXRT_IRQ_DMA4_CH12_CH13_CH44_CH45 (IMXRT_IRQ_EXTINT + 134)  /* WAKEUP Domain eDMA channel 12/13/44/45 interrupt */
#define IMXRT_IRQ_DMA4_CH14_CH15_CH46_CH47 (IMXRT_IRQ_EXTINT + 135)  /* WAKEUP Domain eDMA channel 14/15/46/47 interrupt */
#define IMXRT_IRQ_DMA4_CH16_CH17_CH48_CH49 (IMXRT_IRQ_EXTINT + 136)  /* WAKEUP Domain eDMA channel 16/17/48/49 interrupt */
#define IMXRT_IRQ_DMA4_CH18_CH19_CH50_CH51 (IMXRT_IRQ_EXTINT + 137)  /* WAKEUP Domain eDMA channel 18/19/50/51 interrupt */
#define IMXRT_IRQ_DMA4_CH20_CH21_CH52_CH53 (IMXRT_IRQ_EXTINT + 138)  /* WAKEUP Domain eDMA channel 20/21/52/53 interrupt */
#define IMXRT_IRQ_DMA4_CH22_CH23_CH54_CH55 (IMXRT_IRQ_EXTINT + 139)  /* WAKEUP Domain eDMA channel 22/23/54/55 interrupt */
#define IMXRT_IRQ_DMA4_CH24_CH25_CH56_CH57 (IMXRT_IRQ_EXTINT + 140)  /* WAKEUP Domain eDMA channel 24/25/56/57 interrupt */
#define IMXRT_IRQ_DMA4_CH26_CH27_CH58_CH59 (IMXRT_IRQ_EXTINT + 141)  /* WAKEUP Domain eDMA channel 26/27/58/59 interrupt */
#define IMXRT_IRQ_DMA4_CH28_CH29_CH60_CH61 (IMXRT_IRQ_EXTINT + 142)  /* WAKEUP Domain eDMA channel 28/29/60/61 interrupt */
#define IMXRT_IRQ_DMA4_CH30_CH31_CH62_CH63 (IMXRT_IRQ_EXTINT + 143)  /* WAKEUP Domain eDMA channel 30/31/62/63 interrupt */
#define IMXRT_IRQ_XBAR1_CH0_CH1          (IMXRT_IRQ_EXTINT + 144)  /* XBAR1 channel 0/1 interrupt */
#define IMXRT_IRQ_XBAR1_CH2_CH3          (IMXRT_IRQ_EXTINT + 145)  /* XBAR1 channel 2/3 interrupt */
#define IMXRT_IRQ_SINC3_CH0_CH1_CH2_CH3  (IMXRT_IRQ_EXTINT + 146)  /* SINC Filter Glue 3 channel 0/1/2/3 */
#define IMXRT_IRQ_EWM                    (IMXRT_IRQ_EXTINT + 147)  /* EWM reset out interrupt */
#define IMXRT_IRQ_SEMC                   (IMXRT_IRQ_EXTINT + 148)  /* SEMC interrupt */
#define IMXRT_IRQ_LPIT3                  (IMXRT_IRQ_EXTINT + 149)  /* LPIT3 interrupt */
#define IMXRT_IRQ_LPTMR3                 (IMXRT_IRQ_EXTINT + 150)  /* LPTMR3 interrupt */
#define IMXRT_IRQ_TMR4                   (IMXRT_IRQ_EXTINT + 151)  /* TMR4 interrupt */
#define IMXRT_IRQ_Reserved168            (IMXRT_IRQ_EXTINT + 152)  /* Reserved interrupt */
#define IMXRT_IRQ_LPI2C6                 (IMXRT_IRQ_EXTINT + 153)  /* LPI2C6 interrupt */
#define IMXRT_IRQ_SAI4                   (IMXRT_IRQ_EXTINT + 154)  /* SAI4 interrupt */
#define IMXRT_IRQ_SPDIF                  (IMXRT_IRQ_EXTINT + 155)  /* SPDIF interrupt */
#define IMXRT_IRQ_Reserved172            (IMXRT_IRQ_EXTINT + 156)  /* Reserved interrupt */
#define IMXRT_IRQ_Reserved173            (IMXRT_IRQ_EXTINT + 157)  /* Reserved interrupt */
#define IMXRT_IRQ_Reserved174            (IMXRT_IRQ_EXTINT + 158)  /* Reserved interrupt */
#define IMXRT_IRQ_Reserved175            (IMXRT_IRQ_EXTINT + 159)  /* Reserved interrupt */
#define IMXRT_IRQ_INTG_BOOTROM_DEBUG_CTRL (IMXRT_IRQ_EXTINT + 160)  /* CM33, CM7, DAP access IRQ */
#define IMXRT_IRQ_EDGELOCK_REQ1          (IMXRT_IRQ_EXTINT + 161)  /* Edgelock reuqest 1 interrupt */
#define IMXRT_IRQ_EDGELOCK_REQ2          (IMXRT_IRQ_EXTINT + 162)  /* Edgelock reuqest 2 interrupt */
#define IMXRT_IRQ_EDGELOCK_REQ3          (IMXRT_IRQ_EXTINT + 163)  /* Edgelock reuqest 3 interrupt */
#define IMXRT_IRQ_TMR3                   (IMXRT_IRQ_EXTINT + 164)  /* TMR3 interrupt */
#define IMXRT_IRQ_JTAGC                  (IMXRT_IRQ_EXTINT + 165)  /* JTAGC SRC reset source */
#define IMXRT_IRQ_M33_SYSRESET_REQ       (IMXRT_IRQ_EXTINT + 166)  /* CM33 SYSREQRST SRC reset source */
#define IMXRT_IRQ_M33_LOCKUP             (IMXRT_IRQ_EXTINT + 167)  /* CM33 LOCKUP SRC reset source */
#define IMXRT_IRQ_M7_SYSRESET_REQ        (IMXRT_IRQ_EXTINT + 168)  /* CM33 SYSREQRST SRC reset source */
#define IMXRT_IRQ_M7_LOCKUP              (IMXRT_IRQ_EXTINT + 169)  /* CM33 LOCKUP SRC reset source */
#define IMXRT_IRQ_PWM2_FAULT             (IMXRT_IRQ_EXTINT + 170)  /* PWM2 fault or reload error interrupt */
#define IMXRT_IRQ_PWM2_0                 (IMXRT_IRQ_EXTINT + 171)  /* PWM2 capture 0, compare 0, or reload 0 interrupt */
#define IMXRT_IRQ_PWM2_1                 (IMXRT_IRQ_EXTINT + 172)  /* PWM2 capture 1, compare 1, or reload 1 interrupt */
#define IMXRT_IRQ_PWM2_2                 (IMXRT_IRQ_EXTINT + 173)  /* PWM2 capture 2, compare 2, or reload 2 interrupt */
#define IMXRT_IRQ_PWM2_3                 (IMXRT_IRQ_EXTINT + 174)  /* PWM2 capture 3, compare 3, or reload 3 interrupt */
#define IMXRT_IRQ_PWM3_FAULT             (IMXRT_IRQ_EXTINT + 175)  /* PWM3 fault or reload error interrupt */
#define IMXRT_IRQ_PWM3_0                 (IMXRT_IRQ_EXTINT + 176)  /* PWM3 capture 0, compare 0, or reload 0 interrupt */
#define IMXRT_IRQ_PWM3_1                 (IMXRT_IRQ_EXTINT + 177)  /* PWM3 capture 1, compare 1, or reload 1 interrupt */
#define IMXRT_IRQ_PWM3_2                 (IMXRT_IRQ_EXTINT + 178)  /* PWM3 capture 2, compare 2, or reload 2 interrupt */
#define IMXRT_IRQ_PWM3_3                 (IMXRT_IRQ_EXTINT + 179)  /* PWM3 capture 3, compare 3, or reload 3 interrupt */
#define IMXRT_IRQ_PWM4_FAULT             (IMXRT_IRQ_EXTINT + 180)  /* PWM4 fault or reload error interrupt */
#define IMXRT_IRQ_PWM4_0                 (IMXRT_IRQ_EXTINT + 181)  /* PWM4 capture 0, compare 0, or reload 0 interrupt */
#define IMXRT_IRQ_PWM4_1                 (IMXRT_IRQ_EXTINT + 182)  /* PWM4 capture 1, compare 1, or reload 1 interrupt */
#define IMXRT_IRQ_PWM4_2                 (IMXRT_IRQ_EXTINT + 183)  /* PWM4 capture 2, compare 2, or reload 2 interrupt */
#define IMXRT_IRQ_PWM4_3                 (IMXRT_IRQ_EXTINT + 184)  /* PWM4 capture 3, compare 3, or reload 3 interrupt */
#define IMXRT_IRQ_EQDC1                  (IMXRT_IRQ_EXTINT + 185)  /* EQDC1 interrupt */
#define IMXRT_IRQ_EQDC2                  (IMXRT_IRQ_EXTINT + 186)  /* EQDC2 interrupt */
#define IMXRT_IRQ_EQDC3                  (IMXRT_IRQ_EXTINT + 187)  /* EQDC3 interrupt */
#define IMXRT_IRQ_EQDC4                  (IMXRT_IRQ_EXTINT + 188)  /* EQDC4 interrupt */
#define IMXRT_IRQ_ADC2                   (IMXRT_IRQ_EXTINT + 189)  /* ADC2 interrupt */
#define IMXRT_IRQ_DCDC                   (IMXRT_IRQ_EXTINT + 190)  /* DCDC brown out interrupt */
#define IMXRT_IRQ_CAN3                   (IMXRT_IRQ_EXTINT + 191)  /* CAN3 interrupt */
#define IMXRT_IRQ_CAN3_ERROR             (IMXRT_IRQ_EXTINT + 192)  /* CAN3 error interrupt */
#define IMXRT_IRQ_DAC                    (IMXRT_IRQ_EXTINT + 193)  /* DAC interrupt */
#define IMXRT_IRQ_LPSPI5                 (IMXRT_IRQ_EXTINT + 194)  /* LPSPI5 interrupt */
#define IMXRT_IRQ_LPSPI6                 (IMXRT_IRQ_EXTINT + 195)  /* LPSPI6 interrupt */
#define IMXRT_IRQ_LPUART7                (IMXRT_IRQ_EXTINT + 196)  /* LPUART7 interrupt */
#define IMXRT_IRQ_LPUART8                (IMXRT_IRQ_EXTINT + 197)  /* LPUART8 interrupt */
#define IMXRT_IRQ_SAI2                   (IMXRT_IRQ_EXTINT + 198)  /* SAI2 interrupt */
#define IMXRT_IRQ_Reserved215            (IMXRT_IRQ_EXTINT + 199)  /* Reserved interrupt */
#define IMXRT_IRQ_Reserved216            (IMXRT_IRQ_EXTINT + 200)  /* Reserved interrupt */
#define IMXRT_IRQ_Reserved217            (IMXRT_IRQ_EXTINT + 201)  /* Reserved interrupt */
#define IMXRT_IRQ_ACMP3                  (IMXRT_IRQ_EXTINT + 202)  /* CMP3 interrupt */
#define IMXRT_IRQ_Reserved219            (IMXRT_IRQ_EXTINT + 203)  /* Reserved interrupt */
#define IMXRT_IRQ_CM7_PS                 (IMXRT_IRQ_EXTINT + 204)  /* M7 PS Tag/Data Parity Error */
#define IMXRT_IRQ_CM7_MCM                (IMXRT_IRQ_EXTINT + 205)  /* M7 MCM interrupt */
#define IMXRT_IRQ_CM33_MCM               (IMXRT_IRQ_EXTINT + 206)  /* M33 MCM interrupt */
#define IMXRT_IRQ_ECAT_INT               (IMXRT_IRQ_EXTINT + 207)  /* EtherCAT interrupt */
#define IMXRT_IRQ_SAFETY_CLK_MON         (IMXRT_IRQ_EXTINT + 208)  /* Safety clock monitor interrupt */
#define IMXRT_IRQ_GPT1                   (IMXRT_IRQ_EXTINT + 209)  /* GPT1 interrupt */
#define IMXRT_IRQ_GPT2                   (IMXRT_IRQ_EXTINT + 210)  /* GPT2 interrupt */
#define IMXRT_IRQ_KPP                    (IMXRT_IRQ_EXTINT + 211)  /* KPP interrupt */
#define IMXRT_IRQ_USBPHY1                (IMXRT_IRQ_EXTINT + 212)  /* USBPHY1 interrupt */
#define IMXRT_IRQ_Reserved229            (IMXRT_IRQ_EXTINT + 213)  /* Reserved interrupt */
#define IMXRT_IRQ_Reserved230            (IMXRT_IRQ_EXTINT + 214)  /* Reserved interrupt */
#define IMXRT_IRQ_USBOTG1                (IMXRT_IRQ_EXTINT + 215)  /* USBOTG1 interrupt */
#define IMXRT_IRQ_FLEXSPI_SLV            (IMXRT_IRQ_EXTINT + 216)  /* FLEXSPI follower interrupt */
#define IMXRT_IRQ_NETC                   (IMXRT_IRQ_EXTINT + 217)  /* NETC interrupt */
#define IMXRT_IRQ_MSGINTR1               (IMXRT_IRQ_EXTINT + 218)  /* MSGINTR1 interrupt */
#define IMXRT_IRQ_MSGINTR2               (IMXRT_IRQ_EXTINT + 219)  /* MSGINTR2 interrupt */
#define IMXRT_IRQ_MSGINTR3               (IMXRT_IRQ_EXTINT + 220)  /* MSGINTR3 interrupt */
#define IMXRT_IRQ_MSGINTR4               (IMXRT_IRQ_EXTINT + 221)  /* MSGINTR4 interrupt */
#define IMXRT_IRQ_MSGINTR5               (IMXRT_IRQ_EXTINT + 222)  /* MSGINTR5 interrupt */
#define IMXRT_IRQ_MSGINTR6               (IMXRT_IRQ_EXTINT + 223)  /* MSGINTR6 interrupt */
#define IMXRT_IRQ_SINC1_CH0              (IMXRT_IRQ_EXTINT + 224)  /* SINC Filter Glue 1 channel 0 */
#define IMXRT_IRQ_SINC1_CH1              (IMXRT_IRQ_EXTINT + 225)  /* SINC Filter Glue 1 channel 1 */
#define IMXRT_IRQ_SINC1_CH2              (IMXRT_IRQ_EXTINT + 226)  /* SINC Filter Glue 1 channel 2 */
#define IMXRT_IRQ_SINC1_CH3              (IMXRT_IRQ_EXTINT + 227)  /* SINC Filter Glue 1 channel 3 */
#define IMXRT_IRQ_SINC2_CH0              (IMXRT_IRQ_EXTINT + 228)  /* SINC Filter Glue 2 channel 0 */
#define IMXRT_IRQ_SINC2_CH1              (IMXRT_IRQ_EXTINT + 229)  /* SINC Filter Glue 2 channel 1 */
#define IMXRT_IRQ_SINC2_CH2              (IMXRT_IRQ_EXTINT + 230)  /* SINC Filter Glue 2 channel 2 */
#define IMXRT_IRQ_SINC2_CH3              (IMXRT_IRQ_EXTINT + 231)  /* SINC Filter Glue 2 channel 3 */
#define IMXRT_IRQ_GPIO4                  (IMXRT_IRQ_EXTINT + 232)  /* GPIO4 interrupt */
#define IMXRT_IRQ_TMR2                   (IMXRT_IRQ_EXTINT + 233)  /* TMR2 interrupt */
#define IMXRT_IRQ_GPIO5                  (IMXRT_IRQ_EXTINT + 234)  /* GPIO5 interrupt */
#define IMXRT_IRQ_ASRC                   (IMXRT_IRQ_EXTINT + 235)  /* ASRC interrupt */
#define IMXRT_IRQ_GPIO6                  (IMXRT_IRQ_EXTINT + 236)  /* GPIO6 interrupt */
#define IMXRT_IRQ_DBG_TRACE              (IMXRT_IRQ_EXTINT + 237)  /* JTAGSW DAP MDM-AP SRC reset source */
#define IMXRT_IRQ_ECAT_RST_OUT           (IMXRT_IRQ_EXTINT + 238)  /* ECAT reset out interrupt */

#define IMXRT_IRQ_NEXTINT                  (IMXRT_IRQ_EXTINT + 239)
#define NR_IRQS                            IMXRT_IRQ_NEXTINT

#endif /* __ARCH_ARM_INCLUDE_IMXRT_IMXRT118X_IRQ_H */
