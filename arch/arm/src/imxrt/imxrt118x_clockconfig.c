/****************************************************************************
 * arch/arm/src/imxrt/imxrt118x_clockconfig.c
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

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include <arch/barriers.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "hardware/imxrt_ccm.h"
#include "hardware/rt118x/imxrt118x_osc.h"
#include "hardware/rt118x/imxrt118x_pll.h"
#include "imxrt_clockconfig.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define IMXRT118X_RC24M_FREQUENCY       24000000u
#define IMXRT118X_RC400M_FREQUENCY      400000000u
#define IMXRT118X_XTAL_FREQUENCY        BOARD_XTAL_FREQUENCY
#define IMXRT118X_SYSPLL1_FREQUENCY     1000000000u
#define IMXRT118X_SYSPLL2_FREQUENCY     528000000u
#define IMXRT118X_SYSPLL3_FREQUENCY     480000000u

#define SOURCES_COMMON(a, b) \
  {IMXRT_CLK_OSC_RC24M, IMXRT_CLK_OSC_RC400M, (a), (b)}

/* The mux input ordering is root-specific.  This table is derived from the
 * RT1186 clock mux table in the NXP device SDK, not from the RT117x.
 */

static const uint8_t g_clock_sources[IMXRT_CCM_ROOT_COUNT][4] =
{
  SOURCES_COMMON(IMXRT_CLK_ARM_PLL,          IMXRT_CLK_SYS_PLL3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3,         IMXRT_CLK_ARM_PLL),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1,         IMXRT_CLK_SYS_PLL2_PFD1),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL2,         IMXRT_CLK_SYS_PLL3_PFD2),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL2,         IMXRT_CLK_SYS_PLL3_PFD1),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3,         IMXRT_CLK_SYS_PLL2_PFD1),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_OSC24M,           IMXRT_CLK_SYS_PLL3_DIV2),
  SOURCES_COMMON(IMXRT_CLK_OSC24M,           IMXRT_CLK_SYS_PLL3_DIV2),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_PFD0,    IMXRT_CLK_SYS_PLL2_PFD0),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_PFD2,    IMXRT_CLK_SYS_PLL2_PFD1),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL2,         IMXRT_CLK_SYS_PLL1),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3,         IMXRT_CLK_OSC24M),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3,         IMXRT_CLK_OSC24M),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3,         IMXRT_CLK_OSC24M),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_PFD1,    IMXRT_CLK_SYS_PLL2),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_PFD1,    IMXRT_CLK_SYS_PLL2),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_PFD1,    IMXRT_CLK_SYS_PLL2),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL2_PFD2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL2_PFD2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1,         IMXRT_CLK_SYS_PLL2_PFD0),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3,         IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3,         IMXRT_CLK_SYS_PLL2_PFD3),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_PFD3,    IMXRT_CLK_SYS_PLL2_PFD1),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV2,    IMXRT_CLK_SYS_PLL1_DIV5),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1,         IMXRT_CLK_AUDIO_PLL),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1,         IMXRT_CLK_AUDIO_PLL),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1,         IMXRT_CLK_AUDIO_PLL),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3,         IMXRT_CLK_SYS_PLL3_PFD1),
  SOURCES_COMMON(IMXRT_CLK_OSC24M,           IMXRT_CLK_SYS_PLL3_DIV2),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV5,    IMXRT_CLK_AUDIO_PLL),
  SOURCES_COMMON(IMXRT_CLK_AUDIO_PLL,        IMXRT_CLK_SYS_PLL3_PFD2),
  SOURCES_COMMON(IMXRT_CLK_AUDIO_PLL,        IMXRT_CLK_SYS_PLL3_PFD2),
  SOURCES_COMMON(IMXRT_CLK_AUDIO_PLL,        IMXRT_CLK_SYS_PLL3_PFD2),
  SOURCES_COMMON(IMXRT_CLK_AUDIO_PLL,        IMXRT_CLK_SYS_PLL3_PFD2),
  SOURCES_COMMON(IMXRT_CLK_AUDIO_PLL,        IMXRT_CLK_SYS_PLL3_PFD2),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3,         IMXRT_CLK_AUDIO_PLL),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_AUDIO_PLL),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL3_DIV2,    IMXRT_CLK_SYS_PLL1_DIV2),
  SOURCES_COMMON(IMXRT_CLK_SYS_PLL1_DIV5,    IMXRT_CLK_ARM_PLL)
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: imxrt_clockroot_configure
 *
 * Description:
 *   Configure an RT118x clock root.  The hardware encodes divider N as N-1.
 *
 ****************************************************************************/

int imxrt_clockroot_configure(unsigned int root, unsigned int mux,
                              unsigned int divider, bool enable)
{
  uint32_t reg;

  if (root >= IMXRT_CCM_ROOT_COUNT || mux > 3 || divider == 0 ||
      divider > 256)
    {
      return -EINVAL;
    }

  reg = CCM_ROOT_DIV(divider) | CCM_ROOT_MUX(mux);
  if (!enable)
    {
      reg |= CCM_ROOT_OFF;
    }

  putreg32(reg, IMXRT_CCM_ROOT_CTRL(root));
  UP_MB();

  /* Complete the CM33 peripheral write before returning. */

  (void)getreg32(IMXRT_CCM_ROOT_CTRL(root));

  return OK;
}

static uint32_t imxrt_pfd_frequency(enum imxrt_pll_e pll,
                                    unsigned int pfd)
{
  uint32_t frac;
  uint32_t reg;
  uint32_t source;

  if (pfd >= PLL_PFD_COUNT)
    {
      return 0;
    }

  if (pll == IMXRT_PLL_SYS2)
    {
      reg = getreg32(IMXRT_ANADIG_PLL_SYS2_PFD);
      source = imxrt_pll_frequency(IMXRT_PLL_SYS2);
    }
  else if (pll == IMXRT_PLL_SYS3)
    {
      reg = getreg32(IMXRT_ANADIG_PLL_SYS3_PFD);
      source = imxrt_pll_frequency(IMXRT_PLL_SYS3);
    }
  else
    {
      return 0;
    }

  if ((reg & PLL_PFD_GATE(pfd)) != 0)
    {
      return 0;
    }

  frac = (reg & PLL_PFD_FRAC_MASK(pfd)) >> PLL_PFD_FRAC_SHIFT(pfd);
  if (source == 0 || frac < 12 || frac > 35)
    {
      return 0;
    }

  return (uint32_t)(((uint64_t)source * 18u) / frac);
}

/****************************************************************************
 * Name: imxrt_pll_frequency
 ****************************************************************************/

uint32_t imxrt_pll_frequency(enum imxrt_pll_e pll)
{
  uint32_t ctrl;
  uint32_t div;
  uint32_t denom;
  uint32_t numer;
  uint32_t postdiv;
  uint64_t frequency;

  switch (pll)
    {
      case IMXRT_PLL_ARM:
        ctrl = getreg32(IMXRT_ANADIG_PLL_ARM_CTRL);
        if ((ctrl & (PLL_ARM_POWERUP | PLL_ARM_ENABLE | PLL_ARM_STABLE)) !=
            (PLL_ARM_POWERUP | PLL_ARM_ENABLE | PLL_ARM_STABLE) ||
            (ctrl & PLL_ARM_GATE) != 0)
          {
            return 0;
          }

        if ((ctrl & PLL_ARM_BYPASS) != 0)
          {
            return IMXRT118X_XTAL_FREQUENCY;
          }

        div = (ctrl & PLL_ARM_DIV_MASK) >> PLL_ARM_DIV_SHIFT;
        postdiv = 1u << (((ctrl & PLL_ARM_POSTDIV_MASK) >>
                          PLL_ARM_POSTDIV_SHIFT) + 1u);
        return (IMXRT118X_XTAL_FREQUENCY / (2u * postdiv)) * div;

      case IMXRT_PLL_SYS1:
        ctrl = getreg32(IMXRT_ANADIG_PLL_SYS1_CTRL);
        return ((ctrl & (PLL_SYS1_ENABLE | PLL_SYS1_STABLE |
                         PLL_SYS1_GATE)) ==
                (PLL_SYS1_ENABLE | PLL_SYS1_STABLE)) ?
               IMXRT118X_SYSPLL1_FREQUENCY : 0;

      case IMXRT_PLL_SYS2:
        ctrl = getreg32(IMXRT_ANADIG_PLL_SYS2_CTRL);
        return ((ctrl & (PLL_SYS2_POWERUP | PLL_SYS2_ENABLE |
                         PLL_SYS2_STABLE | PLL_SYS2_GATE)) ==
                (PLL_SYS2_POWERUP | PLL_SYS2_ENABLE | PLL_SYS2_STABLE)) ?
               IMXRT118X_SYSPLL2_FREQUENCY : 0;

      case IMXRT_PLL_SYS3:
        ctrl = getreg32(IMXRT_ANADIG_PLL_SYS3_CTRL);
        return ((ctrl & (PLL_SYS3_POWERUP | PLL_SYS3_ENABLE |
                         PLL_SYS3_STABLE | PLL_SYS3_GATE)) ==
                (PLL_SYS3_POWERUP | PLL_SYS3_ENABLE | PLL_SYS3_STABLE)) ?
               IMXRT118X_SYSPLL3_FREQUENCY : 0;

      case IMXRT_PLL_AUDIO:
        ctrl = getreg32(IMXRT_PLL_CTRL(IMXRT_AUDIO_PLL_BASE));
        if ((ctrl & (PLL_CTRL_POWERUP | PLL_CTRL_ENABLE |
                     PLL_CTRL_BYPASS)) !=
            (PLL_CTRL_POWERUP | PLL_CTRL_ENABLE))
          {
            return 0;
          }

        div = (ctrl & PLL_CTRL_DIV_MASK) >> PLL_CTRL_DIV_SHIFT;
        postdiv = 1u << ((ctrl & PLL_CTRL_POSTDIV_MASK) >>
                         PLL_CTRL_POSTDIV_SHIFT);
        numer = getreg32(IMXRT_PLL_NUM(IMXRT_AUDIO_PLL_BASE)) &
                PLL_NUM_MASK;
        denom = getreg32(IMXRT_PLL_DENOM(IMXRT_AUDIO_PLL_BASE)) &
                PLL_DENOM_MASK;
        if (denom == 0)
          {
            return 0;
          }

        frequency = (uint64_t)IMXRT118X_XTAL_FREQUENCY *
                    ((uint64_t)div * denom + numer);
        return (uint32_t)(frequency / ((uint64_t)denom * postdiv));

      default:
        return 0;
    }
}

/****************************************************************************
 * Name: imxrt_clocksource_frequency
 ****************************************************************************/

uint32_t imxrt_clocksource_frequency(enum imxrt_clock_source_e source)
{
  switch (source)
    {
      case IMXRT_CLK_OSC_RC24M:
        return IMXRT118X_RC24M_FREQUENCY;
      case IMXRT_CLK_OSC_RC400M:
        return IMXRT118X_RC400M_FREQUENCY;
      case IMXRT_CLK_OSC24M:
        return IMXRT118X_XTAL_FREQUENCY;
      case IMXRT_CLK_ARM_PLL:
        return imxrt_pll_frequency(IMXRT_PLL_ARM);
      case IMXRT_CLK_SYS_PLL1:
        return imxrt_pll_frequency(IMXRT_PLL_SYS1);
      case IMXRT_CLK_SYS_PLL1_DIV2:
        return imxrt_pll_frequency(IMXRT_PLL_SYS1) / 2u;
      case IMXRT_CLK_SYS_PLL1_DIV5:
        return imxrt_pll_frequency(IMXRT_PLL_SYS1) / 5u;
      case IMXRT_CLK_SYS_PLL2:
        return imxrt_pll_frequency(IMXRT_PLL_SYS2);
      case IMXRT_CLK_SYS_PLL2_PFD0:
      case IMXRT_CLK_SYS_PLL2_PFD1:
      case IMXRT_CLK_SYS_PLL2_PFD2:
      case IMXRT_CLK_SYS_PLL2_PFD3:
        return imxrt_pfd_frequency(IMXRT_PLL_SYS2,
                                   source - IMXRT_CLK_SYS_PLL2_PFD0);
      case IMXRT_CLK_SYS_PLL3:
        return imxrt_pll_frequency(IMXRT_PLL_SYS3);
      case IMXRT_CLK_SYS_PLL3_DIV2:
        return imxrt_pll_frequency(IMXRT_PLL_SYS3) / 2u;
      case IMXRT_CLK_SYS_PLL3_PFD0:
      case IMXRT_CLK_SYS_PLL3_PFD1:
      case IMXRT_CLK_SYS_PLL3_PFD2:
      case IMXRT_CLK_SYS_PLL3_PFD3:
        return imxrt_pfd_frequency(IMXRT_PLL_SYS3,
                                   source - IMXRT_CLK_SYS_PLL3_PFD0);
      case IMXRT_CLK_AUDIO_PLL:
        return imxrt_pll_frequency(IMXRT_PLL_AUDIO);
      default:
        return 0;
    }
}

/****************************************************************************
 * Name: imxrt_clockroot_frequency
 *
 * Description:
 *   Return the effective frequency for any RT118x CCM root.
 ****************************************************************************/

int imxrt_clockroot_frequency(unsigned int root, uint32_t *frequency)
{
  uint32_t divider;
  uint32_t mux;
  uint32_t reg;
  uint32_t source;

  if (root >= IMXRT_CCM_ROOT_COUNT || frequency == NULL)
    {
      return -EINVAL;
    }

  reg = getreg32(IMXRT_CCM_ROOT_CTRL(root));
  if ((reg & CCM_ROOT_OFF) != 0)
    {
      return -ENODEV;
    }

  divider = ((reg & CCM_ROOT_DIV_MASK) >> CCM_ROOT_DIV_SHIFT) + 1;

  mux = (reg & CCM_ROOT_MUX_MASK) >> CCM_ROOT_MUX_SHIFT;
  source = imxrt_clocksource_frequency(g_clock_sources[root][mux]);
  if (source == 0)
    {
      return -ENODEV;
    }

  *frequency = source / divider;
  return OK;
}

/****************************************************************************
 * Name: imxrt_clockgate_configure
 *
 * Description:
 *   Enable or disable an RT118x LPCG.
 *
 ****************************************************************************/

void imxrt_clockgate_configure(unsigned int gate, bool enable)
{
  uint32_t reg;

  DEBUGASSERT(gate < IMXRT_CCM_LPCG_COUNT);

  reg = getreg32(IMXRT_CCM_LPCG_DIR(gate));
  if (enable)
    {
      reg |= CCM_LPCG_DIR_ON;
    }
  else
    {
      reg &= ~CCM_LPCG_DIR_ON;
    }

  putreg32(reg, IMXRT_CCM_LPCG_DIR(gate));
  UP_MB();

  /* Complete the CM33 peripheral write before returning. */

  (void)getreg32(IMXRT_CCM_LPCG_DIR(gate));
}

/****************************************************************************
 * Name: imxrt_clockconfig
 *
 * Description:
 *   Configure the initial RT1180 clock roots used by NuttX.
 *
 ****************************************************************************/

void imxrt_clockconfig(void)
{
  /* Keep the early console on RC24M until NuttX owns the ELE/TRDC policy.
   * The general root and frequency APIs support all PLL-derived selections,
   * but inferring PLL ownership from status bits alone is not sufficient:
   * debugger handoff can leave a nominally stable PLL at a rate that differs
   * from the board's boot contract.
   */

  imxrt_clockroot_configure(CCM_CR_LPUART0102, 0, 1, true);
  imxrt_clockgate_configure(CCM_CCGR_LPUART1, true);
}
