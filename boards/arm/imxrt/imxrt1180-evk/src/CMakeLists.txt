# ##############################################################################
# boards/arm/imxrt/imxrt1180-evk/src/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
# ##############################################################################

set(SRCS imxrt_boot.c imxrt_bringup.c imxrt_clockconfig.c imxrt_gpio.c)

if(CONFIG_ARCH_LEDS)
  list(APPEND SRCS imxrt_autoleds.c)
else()
  list(APPEND SRCS imxrt_userleds.c)
endif()

if(CONFIG_ARCH_BUTTONS)
  list(APPEND SRCS imxrt_buttons.c)
endif()

target_sources(board PRIVATE ${SRCS})

set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/dtcm.ld")
