/****************************************************************************
 * boards/arm/imxrt/imxrt1180-evk/src/imxrt1180-evk.h
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

#ifndef __BOARDS_ARM_IMXRT_IMXRT1180_EVK_SRC_IMXRT1180_EVK_H
#define __BOARDS_ARM_IMXRT_IMXRT1180_EVK_SRC_IMXRT1180_EVK_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include "hardware/rt118x/imxrt118x_pinmux.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Both user LEDs are active high. */

#define GPIO_LED_GREEN (GPIO_GPIO4_IO27 | GPIO_OUTPUT_ZERO)
#define GPIO_LED_RED   (GPIO_GPIO4_IO26 | GPIO_OUTPUT_ZERO)

/* SW8 is pulled high and driven low while pressed. */

#define GPIO_SW8       GPIO_GPIO1_IO04

#define LED_DRIVER_PATH "/dev/userleds"

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef CONFIG_ARCH_LEDS
void imxrt_autoled_initialize(void);
#endif

#endif /* __BOARDS_ARM_IMXRT_IMXRT1180_EVK_SRC_IMXRT1180_EVK_H */
