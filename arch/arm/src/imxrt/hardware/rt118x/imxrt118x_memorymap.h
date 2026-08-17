/****************************************************************************
 * arch/arm/src/imxrt/hardware/rt118x/imxrt118x_memorymap.h
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

#ifndef __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_MEMORYMAP_H
#define __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_MEMORYMAP_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* System Memory Map (Cortex-M33 non-secure view).
 * Peripheral register bases generated from NXP MIMXRT1186_cm33.xml.
 * AHB/FlexSPI windows and TCM sizes from the RT118x reference manual /
 * CMSIS device header.
 */

/* TCM / OCRAM / FlexSPI AHB ************************************************/

#define IMXRT_ITCM_BASE              0x1ffe0000u  /* 128 KB, CM33 Code TCM */
#define IMXRT_ITCM_SIZE              (128u * 1024u)
#define IMXRT_DTCM_BASE              0x30000000u  /* 128 KB, CM33 System TCM */
#define IMXRT_DTCM_SIZE              (128u * 1024u)
#define IMXRT_OCRAM_BASE             0x30480000u  /* OCRAM (M33 view) */
#define IMXRT_OCRAM2_BASE            IMXRT_OCRAM_BASE

#define IMXRT_FLEXSPI1_BASE          0x28000000u  /* FlexSPI1 AHB window (NS) */
#define IMXRT_FLEXSPI2_BASE          0x04000000u  /* FlexSPI2 AHB window (NS) */

/* Peripheral Register Bases ************************************************/

#define IMXRT_EDMA4_BASE                   0x42000000u  /* DMA MP */
#define IMXRT_DMA4__TCD_BASE               0x42010000u  /* DMA TCD */
#define IMXRT_BLK_CTRL_WAKEUPMIX_BASE      0x42420000u  /* Block Control WAKEUP Domain */
#define IMXRT_MU2_MUA_BASE                 0x42430000u  /* Messaging Unit */
#define IMXRT_SEMA2_BASE                   0x42450000u  /* SEMA42 */
#define IMXRT_TRDC2_BASE                   0x42460000u  /* TRDC */
#define IMXRT_TSTMR2_TSTMRA_BASE           0x42480000u  /* TSTMR */
#define IMXRT_WDOG3_BASE                   0x42490000u  /* WDOG */
#define IMXRT_WDOG4_BASE                   0x424a0000u  /* WDOG */
#define IMXRT_WDOG5_BASE                   0x424b0000u  /* WDOG */
#define IMXRT_LPIT2_BASE                   0x424c0000u  /* LPIT */
#define IMXRT_LPTMR2_BASE                  0x424d0000u  /* LPTMR */
#define IMXRT_TPM3_BASE                    0x424e0000u  /* TPM */
#define IMXRT_TPM4_BASE                    0x424f0000u  /* TPM */
#define IMXRT_I3C2_BASE                    0x42520000u  /* I3C */
#define IMXRT_LPI2C3_BASE                  0x42530000u  /* Low-Power Inter-Integrated Circuit */
#define IMXRT_LPSPI3_BASE                  0x42550000u  /* Low-Power Serial Peripheral Interface */
#define IMXRT_LPSPI4_BASE                  0x42560000u  /* Low-Power Serial Peripheral Interface */
#define IMXRT_LPUART3_BASE                 0x42570000u  /* LPUART */
#define IMXRT_LPUART4_BASE                 0x42580000u  /* LPUART */
#define IMXRT_LPUART5_BASE                 0x42590000u  /* LPUART */
#define IMXRT_LPUART6_BASE                 0x425a0000u  /* LPUART */
#define IMXRT_FLEXIO1_BASE                 0x425c0000u  /* FLEXIO */
#define IMXRT_FLEXIO2_BASE                 0x425d0000u  /* FLEXIO */
#define IMXRT_FLEXSPIC_BASE                0x425e0000u  /* FlexSPI */
#define IMXRT_OTFAD1_BASE                  0x425e0000u  /* OTFAD */
#define IMXRT_ADC1_BASE                    0x42600000u  /* ADC */
#define IMXRT_PWM1_BASE                    0x42650000u  /* PWM */
#define IMXRT_PWM2_BASE                    0x42660000u  /* PWM */
#define IMXRT_PWM3_BASE                    0x42670000u  /* PWM */
#define IMXRT_PWM4_BASE                    0x42680000u  /* PWM */
#define IMXRT_TMR1_BASE                    0x42690000u  /* TMR */
#define IMXRT_TMR2_BASE                    0x426a0000u  /* TMR */
#define IMXRT_TMR3_BASE                    0x426b0000u  /* TMR */
#define IMXRT_TMR4_BASE                    0x426c0000u  /* TMR */
#define IMXRT_TMR5_BASE                    0x426d0000u  /* TMR */
#define IMXRT_TMR6_BASE                    0x426e0000u  /* TMR */
#define IMXRT_TMR7_BASE                    0x426f0000u  /* TMR */
#define IMXRT_TMR8_BASE                    0x42700000u  /* TMR */
#define IMXRT_EQDC1_BASE                   0x42710000u  /* Quadrature_Decoder */
#define IMXRT_EQDC2_BASE                   0x42720000u  /* Quadrature_Decoder */
#define IMXRT_EQDC3_BASE                   0x42730000u  /* Quadrature_Decoder */
#define IMXRT_EQDC4_BASE                   0x42740000u  /* Quadrature_Decoder */
#define IMXRT_XBAR1_BASE                   0x42750000u  /* XBAR */
#define IMXRT_XBAR2_BASE                   0x42760000u  /* XBAR */
#define IMXRT_XBAR3_BASE                   0x42770000u  /* XBAR */
#define IMXRT_AOI1_BASE                    0x42780000u  /* AOI */
#define IMXRT_AOI2_BASE                    0x42790000u  /* AOI */
#define IMXRT_EWM_BASE                     0x427b0000u  /* EWM */
#define IMXRT_AOI3_BASE                    0x427e0000u  /* AOI */
#define IMXRT_AOI4_BASE                    0x427f0000u  /* AOI */
#define IMXRT_TRDC3_BASE                   0x42810000u  /* TRDC */
#define IMXRT_USDHC2_BASE                  0x42860000u  /* uSDHC */
#define IMXRT_MSGINTR1_BASE                0x428a0000u  /* MSGINTR */
#define IMXRT_MSGINTR2_BASE                0x428b0000u  /* MSGINTR */
#define IMXRT_MSGINTR3_BASE                0x428c0000u  /* MSGINTR */
#define IMXRT_MSGINTR4_BASE                0x428d0000u  /* MSGINTR */
#define IMXRT_MSGINTR5_BASE                0x428e0000u  /* MSGINTR */
#define IMXRT_MSGINTR6_BASE                0x428f0000u  /* MSGINTR */
#define IMXRT_FLEXSPI_SLV_BASE             0x42900000u  /* FlexSPI_FLR */
#define IMXRT_SEMC_BASE                    0x42910000u  /* SEMC */
#define IMXRT_MECC1_BASE                   0x42920000u  /* MECC64 */
#define IMXRT_MECC2_BASE                   0x42930000u  /* MECC64 */
#define IMXRT_ASRC_BASE                    0x429a0000u  /* ASRC */
#define IMXRT_KPP_BASE                     0x42a00000u  /* KPP */
#define IMXRT_IOMUXC_BASE                  0x42a10000u  /* IOMUXC */
#define IMXRT_ECAT_BASE                    0x42a80000u  /* ETHERCAT */
#define IMXRT_SPDIF_BASE                   0x42ba0000u  /* SPDIF */
#define IMXRT_SAI2_BASE                    0x42bb0000u  /* SAI */
#define IMXRT_SAI4_BASE                    0x42bd0000u  /* SAI */
#define IMXRT_PDM_BASE                     0x42be0000u  /* MICFIL */
#define IMXRT_SINC1_BASE                   0x42bf0000u  /* SINC */
#define IMXRT_SINC2_BASE                   0x42c00000u  /* SINC */
#define IMXRT_SINC3_BASE                   0x42c10000u  /* SINC */
#define IMXRT_USBOTG1_BASE                 0x42c80000u  /* USBC */
#define IMXRT_USBNC_OTG1_BASE              0x42c80200u  /* USBNC */
#define IMXRT_USBPHY1_BASE                 0x42ca0000u  /* USBPHY */
#define IMXRT_USBHSDCD1_BASE               0x42ca0800u  /* USBDCD */
#define IMXRT_USBHSDCD2_BASE               0x42cb0800u  /* USBDCD */
#define IMXRT_LPIT3_BASE                   0x42cc0000u  /* LPIT */
#define IMXRT_LPTMR3_BASE                  0x42cd0000u  /* LPTMR */
#define IMXRT_LPI2C6_BASE                  0x42d40000u  /* Low-Power Inter-Integrated Circuit */
#define IMXRT_LPSPI5_BASE                  0x42d50000u  /* Low-Power Serial Peripheral Interface */
#define IMXRT_LPSPI6_BASE                  0x42d60000u  /* Low-Power Serial Peripheral Interface */
#define IMXRT_LPUART8_BASE                 0x42da0000u  /* LPUART */
#define IMXRT_CMP3_BASE                    0x42de0000u  /* ACMP */
#define IMXRT_ADC2_BASE                    0x42e00000u  /* ADC */
#define IMXRT_DAC_BASE                     0x42e20000u  /* DAC */
#define IMXRT_VREF_BASE                    0x42e30000u  /* VREF */
#define IMXRT_IEE_BASE                     0x42e40000u  /* IEE */
#define IMXRT_IEE_APC_BASE                 0x42e44000u  /* IEE_APC */
#define IMXRT_GPT2_BASE                    0x42ec0000u  /* GPT */
#define IMXRT_GPIO2_BASE                   0x43810000u  /* GPIO */
#define IMXRT_GPIO3_BASE                   0x43820000u  /* GPIO */
#define IMXRT_GPIO4_BASE                   0x43830000u  /* GPIO */
#define IMXRT_GPIO5_BASE                   0x43840000u  /* GPIO */
#define IMXRT_GPIO6_BASE                   0x43850000u  /* GPIO */
#define IMXRT_EDMA_BASE                    0x44000000u  /* DMA MP */
#define IMXRT_DMA3__TCD_BASE               0x44010000u  /* DMA TCD */
#define IMXRT_BLK_CTRL_NS_AONMIX_BASE      0x44210000u  /* Block Control Non-Secure AON Domain */
#define IMXRT_MU1_MUA_BASE                 0x44220000u  /* Messaging Unit */
#define IMXRT_SEMA1_BASE                   0x44260000u  /* SEMA42 */
#define IMXRT_TRDC1_BASE                   0x44270000u  /* TRDC */
#define IMXRT_SYS_CTR_CONTROL_BASE         0x44290000u  /* SYS_CTR_CONTROL */
#define IMXRT_SYS_CTR_COMPARE_BASE         0x442a0000u  /* SYS_CTR_COMPARE */
#define IMXRT_SYS_CTR_READ_BASE            0x442b0000u  /* SYS_CTR_READ */
#define IMXRT_TSTMR1_TSTMRA_BASE           0x442c0000u  /* TSTMR */
#define IMXRT_WDOG1_BASE                   0x442d0000u  /* WDOG */
#define IMXRT_WDOG2_BASE                   0x442e0000u  /* WDOG */
#define IMXRT_LPIT1_BASE                   0x442f0000u  /* LPIT */
#define IMXRT_LPTMR1_BASE                  0x44300000u  /* LPTMR */
#define IMXRT_TPM1_BASE                    0x44310000u  /* TPM */
#define IMXRT_TPM2_BASE                    0x44320000u  /* TPM */
#define IMXRT_I3C1_BASE                    0x44330000u  /* I3C */
#define IMXRT_LPI2C1_BASE                  0x44340000u  /* Low-Power Inter-Integrated Circuit */
#define IMXRT_LPI2C2_BASE                  0x44350000u  /* Low-Power Inter-Integrated Circuit */
#define IMXRT_LPSPI1_BASE                  0x44360000u  /* Low-Power Serial Peripheral Interface */
#define IMXRT_LPSPI2_BASE                  0x44370000u  /* Low-Power Serial Peripheral Interface */
#define IMXRT_LPUART1_BASE                 0x44380000u  /* LPUART */
#define IMXRT_LPUART2_BASE                 0x44390000u  /* LPUART */
#define IMXRT_CAN1_BASE                    0x443a0000u  /* CAN */
#define IMXRT_SAI1_BASE                    0x443b0000u  /* SAI */
#define IMXRT_IOMUXC_AON_BASE              0x443c0000u  /* IOMUXC_AON */
#define IMXRT_M33_PCF1_BASE                0x443e0000u  /* CMX_PERFMON */
#define IMXRT_M33_PSF1_BASE                0x443f0000u  /* CMX_PERFMON */
#define IMXRT_XCACHE_PC_BASE               0x44400000u  /* XCACHE */
#define IMXRT_XCACHE_PS_BASE               0x44400800u  /* XCACHE */
#define IMXRT_CP_CM33_IMX9RTC__CM33_CACHE_ECC_MCM_BASE 0x44401000u  /* CM33_CACHE_ECC_MCM */
#define IMXRT_BLK_CTRL_BBSMMIX_BASE        0x44410000u  /* blk_ctrl_bbsmmix */
#define IMXRT_CP_CM33_IMX9RTC__CM33_TCM_MCM_BASE 0x44420000u  /* CM33_TCM_MCM */
#define IMXRT_BBNSM_BASE                   0x44440000u  /* BBNSM */
#define IMXRT_CCM_BASE                     0x44450000u  /* CCM */
#define IMXRT_SRC_GENERAL_REG_BASE         0x44460000u  /* SRC General */
#define IMXRT_AON_MIX_SLICE_BASE           0x44460800u  /* SRC MIX SLICE */
#define IMXRT_WAKEUP_MIX_SLICE_BASE        0x44460c00u  /* SRC MIX SLICE */
#define IMXRT_MEGA_MIX_SLICE_BASE          0x44461000u  /* SRC MIX SLICE */
#define IMXRT_NETC_MIX_SLICE_BASE          0x44461400u  /* SRC MIX SLICE */
#define IMXRT_CM33PLATFORM_MIX_SLICE_BASE  0x44461800u  /* SRC MIX SLICE */
#define IMXRT_CM7PLATFORM_MIX_SLICE_BASE   0x44461c00u  /* SRC MIX SLICE */
#define IMXRT_AON_MIF_S28SPREGH_BASE       0x44462000u  /* MEM Type I */
#define IMXRT_AON_MIF_LN28FDSOI_SPLLRAM_BASE 0x44462400u  /* MEM Type II */
#define IMXRT_WAKEUP_MIF_S28SPREGH_BASE    0x44462800u  /* MEM Type I */
#define IMXRT_WAKEUP_MIF_LN28FDSOI_SPLLRAM_BASE 0x44462c00u  /* MEM Type II */
#define IMXRT_MEGA_MIF_S28SPREGH_BASE      0x44463000u  /* MEM Type I */
#define IMXRT_MEGA_MIF_LN28FDSOI_SPLLRAM_BASE 0x44463400u  /* MEM Type II */
#define IMXRT_NETC_MIF_S28SPREGH_BASE      0x44463800u  /* MEM Type I */
#define IMXRT_NETC_MIF_LN28FDSOI_SPLLRAM_BASE 0x44463c00u  /* MEM Type II */
#define IMXRT_CM33PLATFORM_CACHE_BASE      0x44464000u  /* MEM Type I */
#define IMXRT_CM33PLATFORM_TCM_BASE        0x44464400u  /* MEM Type I */
#define IMXRT_CM7PLATFORM_CACHE_BASE       0x44464800u  /* MEM Type I */
#define IMXRT_CM7PLATFORM_TCM_BASE         0x44464c00u  /* MEM Type I with PSW */
#define IMXRT_GPC_CPU_CTRL_BASE            0x44470000u  /* no description available */
#define IMXRT_GPC_GLOBAL_BASE              0x44472000u  /* no description available */
#define IMXRT_GPC_SYS_SLEEP_BASE           0x44472800u  /* no description available */
#define IMXRT_ANADIG_LDO_BBSM_BASE         0x44480000u  /* RT1180_ANADIG_REGISTER */
#define IMXRT_ANADIG_OSC_BASE              0x44480000u  /* RT1180_ANADIG_REGISTER */
#define IMXRT_ANADIG_PLL_BASE              0x44480000u  /* RT1180_ANADIG_REGISTER */
#define IMXRT_ANADIG_PMU_BASE              0x44480000u  /* RT1180_ANADIG_REGISTER */
#define IMXRT_ANADIG_SLOTS_BASE            0x44480000u  /* IPS Domain */
#define IMXRT_ANADIG_TEMPSENSOR_BASE       0x44480000u  /* RT1180_ANADIG_REGISTER */
#define IMXRT_ETHERNET_PLL_BASE            0x44484180u  /* Fractional PLL */
#define IMXRT_AUDIO_PLL_BASE               0x44484280u  /* Fractional PLL */
#define IMXRT_OSC_RC_400M_BASE             0x44484380u  /* no description available */
#define IMXRT_TMPSNS_BASE                  0x44484580u  /* TMPSNS */
#define IMXRT_PHY_LDO_BASE                 0x44484680u  /* no description available */
#define IMXRT_VMBANDGAP_BASE               0x44484780u  /* no description available */
#define IMXRT_BLK_CTRL_S_AONMIX_BASE       0x444f0000u  /* Block Control Secure AONMIX */
#define IMXRT_AXBS_BASE                    0x44510000u  /* AXBS */
#define IMXRT_DCDC_BASE                    0x44520000u  /* DCDC */
#define IMXRT_LPUART7_BASE                 0x44570000u  /* LPUART */
#define IMXRT_CAN3_BASE                    0x445b0000u  /* CAN */
#define IMXRT_FLEXSPI2C_BASE               0x445e0000u  /* FlexSPI */
#define IMXRT_OTFAD2_BASE                  0x445e0000u  /* OTFAD */
#define IMXRT_GPT1_BASE                    0x446c0000u  /* GPT */
#define IMXRT_GPIO1_BASE                   0x47400000u  /* GPIO */
#define IMXRT_OCOTP_BASE                   0x47518000u  /* no description available */
#define IMXRT_MU_APPS_S3MUA_BASE           0x47520000u  /* ELEMUA */
#define IMXRT_MU_RT_S3MUA_BASE             0x47540000u  /* ELEMUA */
#define IMXRT_EIM_BASE                     0x4b860000u  /* EIM */
#define IMXRT_ERM_BASE                     0x4b864000u  /* ERM */
#define IMXRT_NETC_F0_PCI_HDR_TYPE0_BASE   0x60000000u  /* NETC PCI Express ECAM PF config */
#define IMXRT_NETC_F1_PCI_HDR_TYPE0_BASE   0x60001000u  /* NETC PCI Express ECAM PF config */
#define IMXRT_NETC_F2_PCI_HDR_TYPE0_BASE   0x60002000u  /* NETC PCI Express ECAM PF config */
#define IMXRT_NETC_F3_PCI_HDR_TYPE0_BASE   0x60003000u  /* NETC PCI Express ECAM PF config */
#define IMXRT_NETC_F4_PCI_HDR_TYPE0_BASE   0x60004000u  /* NETC PCI Express ECAM PF config */
#define IMXRT_IERC_F0_PCI_HDR_TYPE0_BASE   0x600f8000u  /* PCI Express ECAM Event Collector config */
#define IMXRT_NETC_VF1_PCI_HDR_TYPE0_BASE  0x60100000u  /* NETC PCI Express ECAM VF config */
#define IMXRT_NETC_IERB_BASE               0x60800000u  /* NETC Integrated Endpoint Register Block */
#define IMXRT_IERC_IERB_BASE               0x60810000u  /* Event Collector Integrated Endpoint Register Block */
#define IMXRT_NETC_PRIV_BASE               0x60900000u  /* NETC privileged */
#define IMXRT_SW0_BASE_BASE                0x60a00000u  /* Switch base */
#define IMXRT_SW0_COMMON_BASE              0x60a00000u  /* Switch and ENETC common base */
#define IMXRT_SW0_PORT0_BASE               0x60a04000u  /* Port */
#define IMXRT_SW0_ETH_MAC_PORT0_BASE       0x60a05000u  /* Ethernet MAC port */
#define IMXRT_SW0_PORT1_BASE               0x60a08000u  /* Port */
#define IMXRT_SW0_ETH_MAC_PORT1_BASE       0x60a09000u  /* Ethernet MAC port */
#define IMXRT_SW0_PORT2_BASE               0x60a0c000u  /* Port */
#define IMXRT_SW0_ETH_MAC_PORT2_BASE       0x60a0d000u  /* Ethernet MAC port */
#define IMXRT_SW0_PORT3_BASE               0x60a10000u  /* Port */
#define IMXRT_SW0_ETH_MAC_PORT3_BASE       0x60a11000u  /* Ethernet MAC port */
#define IMXRT_SW0_PORT4_BASE               0x60a14000u  /* Port */
#define IMXRT_SW0_PSEUDO_MAC_PORT4_BASE    0x60a15000u  /* Pseudo MAC port */
#define IMXRT_SW0_GLOBAL_BASE              0x60a80000u  /* NETC global */
#define IMXRT_ENETC0_SI0_BASE              0x60b00000u  /* ENETC Station Interface */
#define IMXRT_ENETC0_BASE_BASE             0x60b10000u  /* ENETC base */
#define IMXRT_ENETC0_COMMON_BASE           0x60b10000u  /* Switch and ENETC common base */
#define IMXRT_ENETC0_PORT_BASE             0x60b14000u  /* Port */
#define IMXRT_ENETC0_ETH_MAC_PORT_BASE     0x60b15000u  /* Ethernet MAC port */
#define IMXRT_ENETC0_GLOBAL_BASE           0x60b20000u  /* NETC global */
#define IMXRT_ENETC1_SI0_BASE              0x60b40000u  /* ENETC Station Interface */
#define IMXRT_ENETC1_BASE_BASE             0x60b50000u  /* ENETC base */
#define IMXRT_ENETC1_COMMON_BASE           0x60b50000u  /* Switch and ENETC common base */
#define IMXRT_ENETC1_PORT_BASE             0x60b54000u  /* Port */
#define IMXRT_ENETC1_PSEUDO_MAC_PORT_BASE  0x60b55000u  /* Pseudo MAC port */
#define IMXRT_ENETC1_GLOBAL_BASE           0x60b60000u  /* NETC global */
#define IMXRT_TMR0_BASE_BASE               0x60b80000u  /* STIMER */
#define IMXRT_TMR0_GLOBAL_BASE             0x60b90000u  /* NETC global */
#define IMXRT_EMDIO_BASE_BASE              0x60ba0000u  /* NETC EMDIO base function */
#define IMXRT_EMDIO_GLOBAL_BASE            0x60bb0000u  /* NETC global */
#define IMXRT_ENETC1_SI1_BASE              0x60c10000u  /* ENETC Station Interface */
#define IMXRT_SysTick0_BASE                0xe000e010u  /* M33 Systick module */

/* Compatibility aliases ****************************************************/

#define IMXRT_USB_BASE               IMXRT_USBOTG1_BASE
#define IMXRT_USBPHY_BASE            IMXRT_USBPHY1_BASE
#define IMXRT_ANADIG_BASE            IMXRT_ANADIG_SLOTS_BASE
#define IMXRT_RGPIO1_BASE            IMXRT_GPIO1_BASE
#define IMXRT_RGPIO2_BASE            IMXRT_GPIO2_BASE
#define IMXRT_RGPIO3_BASE            IMXRT_GPIO3_BASE
#define IMXRT_RGPIO4_BASE            IMXRT_GPIO4_BASE
#define IMXRT_RGPIO5_BASE            IMXRT_GPIO5_BASE
#define IMXRT_RGPIO6_BASE            IMXRT_GPIO6_BASE
#define IMXRT_RTWDOG1_BASE           IMXRT_WDOG1_BASE
#define IMXRT_RTWDOG2_BASE           IMXRT_WDOG2_BASE
#define IMXRT_RTWDOG3_BASE           IMXRT_WDOG3_BASE
#define IMXRT_RTWDOG4_BASE           IMXRT_WDOG4_BASE
#define IMXRT_RTWDOG5_BASE           IMXRT_WDOG5_BASE
#define IMXRT_OCOTP_FSB_BASE         IMXRT_OCOTP_BASE
#define IMXRT_GPC_SYS_SLEEP_CTRL_BASE IMXRT_GPC_SYS_SLEEP_BASE

#endif /* __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_MEMORYMAP_H */
