############################################################################
# boards/arm/imxrt/frdm-imxrt1186/src/Makefile
#
# SPDX-License-Identifier: Apache-2.0
############################################################################

include $(TOPDIR)/Make.defs

CSRCS = imxrt_boot.c imxrt_bringup.c imxrt_clockconfig.c imxrt_gpio.c

ifeq ($(CONFIG_FRDM_IMXRT1186_XIP),y)
CSRCS += imxrt_flexspi_nor_boot.c
CSRCS += imxrt_flexspi_nor_flash.c
CSRCS += imxrt_flexspi_nor_xmcd.c
endif

include $(TOPDIR)/boards/Board.mk
