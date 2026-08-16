# ##############################################################################
# boards/arm/imxrt/frdm-imxrt1186/src/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
# ##############################################################################

target_sources(board PRIVATE imxrt_boot.c imxrt_bringup.c imxrt_clockconfig.c
                             imxrt_gpio.c)

set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/dtcm.ld")
