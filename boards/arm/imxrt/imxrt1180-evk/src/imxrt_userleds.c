/****************************************************************************
 * boards/arm/imxrt/imxrt1180-evk/src/imxrt_userleds.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdbool.h>
#include <stdint.h>

#include <arch/board/board.h>

#include "imxrt_gpio.h"
#include "imxrt1180-evk.h"

#ifndef CONFIG_ARCH_LEDS

/****************************************************************************
 * Public Functions
 ****************************************************************************/

uint32_t board_userled_initialize(void)
{
  imxrt_config_gpio(GPIO_LED_GREEN);
  imxrt_config_gpio(GPIO_LED_RED);

  return BOARD_NLEDS;
}

void board_userled(int led, bool ledon)
{
  gpio_pinset_t pinset;

  if (led == BOARD_USERLED_GREEN)
    {
      pinset = GPIO_LED_GREEN;
    }
  else if (led == BOARD_USERLED_RED)
    {
      pinset = GPIO_LED_RED;
    }
  else
    {
      return;
    }

  imxrt_gpio_write(pinset, ledon);
}

void board_userled_all(uint32_t ledset)
{
  imxrt_gpio_write(GPIO_LED_GREEN,
                   (ledset & BOARD_USERLED_GREEN_BIT) != 0);
  imxrt_gpio_write(GPIO_LED_RED,
                   (ledset & BOARD_USERLED_RED_BIT) != 0);
}

#endif /* !CONFIG_ARCH_LEDS */
