/****************************************************************************
 * arch/risc-v/src/hpm5300/hpm_clockconfig.c
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
#include <assert.h>
#include <nuttx/debug.h>

#include <nuttx/arch.h>
#include <arch/board/board.h>

#include "hardware/hpm5300/hpm5300_sysctl.h"
#include "hardware/hpm_memorymap.h"
#include "hardware/hpm_pllctl.h"
#include "riscv_internal.h"
#include "chip.h"
#include "hpm.h"
#include "hpm_clockconfig.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define EXT_OSC 24000000

#define PLLCTLV2_PLL_MFN_FACTOR  (10U)               /* PLLCTLV2 PLL MFN Factor */
#define PLLCTLV2_PLL_MFD_DEFAULT (240UL * 1000000UL) /* PLLCTLV2 PLL Default MFD value */

#define PLLCTLV2_PLL_MFI_MIN     (16U)
#define PLLCTLV2_PLL_MFI_MAX     (42U)
#define PLLCTLV2_PLL_XTAL_FREQ   (24000000UL)

#define PLLCTLV2_PLL_FREQ_MIN    (PLLCTLV2_PLL_MFI_MIN * PLLCTLV2_PLL_XTAL_FREQ)
#define PLLCTLV2_PLL_FREQ_MAX    ((PLLCTLV2_PLL_MFI_MAX + 1U) * PLLCTLV2_PLL_XTAL_FREQ)

#define BUS_FREQ_MAX             (200000000UL)

/* PCFG DCDC converter bits (pcfg_dcdc_set_voltage_ccm_mode in the SDK) */

#define PCFG_DCDC_VOLT_MASK      (0xFFFU)
#define PCFG_DCDC_MODE_MIRROR_MASK (0xF000U) /* DCDC mode mirror [15:12] */
#define PCFG_DCDC_READY          (0x10000000U)
#define PCFG_DCDC_MIN_DUT_MASK   (0x7F00U)
#define PCFG_DCDC_MIN_DUT(x)     (((uint32_t)(x) << 8) & PCFG_DCDC_MIN_DUT_MASK)
#define PCFG_DCDC_VOLTAGE_480MHZ (1275U)

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/* Check whether a PLLCTLV2 MFI/DIV register reports a stable PLL.
 * Since we always set the ENABLE bit ourselves, the PLL counts as
 * stable only when it is not busy and the RESPONSE bit is set.
 */

static bool hpm_pll_reg_stable(uintptr_t reg)
{
  uint32_t value = getreg32(reg);

  return ((value & HPM_PLLCTLV2_PLL_MFI_BUSY) == 0) &&
         ((value & HPM_PLLCTLV2_PLL_MFI_RESPONSE) != 0);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: hpm6750_get_osc_freq
 ****************************************************************************/

uint32_t hpm_get_osc_freq(void)
{
  return EXT_OSC;
}

/****************************************************************************
 * Name: hpm6750_clockconfig
 ****************************************************************************/

void hpm_clockconfig(void)
{
  uint32_t value;

  /* If the ROM bootloader left the CPU running on the 24MHz oscillator,
   * select the default clock scenario preset.  The hpm5300evk SDK board
   * (board_init_clock) does the same before re-configuring the clock
   * tree.
   */

  if ((getreg32(HPM_SYSCTL_CLOCK_CPU_CLK_TOP_CPU0) &
       SYSCTL_CLOCK_CPU_MUX_MASK) == SYSCTL_CLOCK_CPU_MUX_OSC0_CLK0)
    {
      value = getreg32(HPM_SYSCTL_GLOBAL00);
      putreg32((value & ~SYSCTL_GLOBAL00_MUX_MASK) | 2,
               HPM_SYSCTL_GLOBAL00);
    }

  /* Enable the "common" (LINK0) and "AHB" (LINK1) clock group resources.
   * UART0-6 and UART7 are added later, once their pins are muxed.
   */

  putreg32(0x007fffff, HPM_SYSCTL_GROUP0_LINK0_VALUE);
  putreg32(0x007ffffe, HPM_SYSCTL_GROUP0_LINK1_VALUE);

  /* Connect Group0 to CPU0 */

  putreg32(1, HPM_SYSCTL_AFFILIATE_CPU0_SET);

  /* Bump up the DCDC voltage to 1275mV before switching the CPU clock
   * to 480MHz.  The SDK's board_init_clock calls
   * pcfg_dcdc_set_voltage(HPM_PCFG, 1275) at this point; running the
   * core at 480MHz with the ROM's low-voltage setting is out of spec.
   */

  value = getreg32(HPM_PCFG_DCDC_MODE);
  value = (value & ~(PCFG_DCDC_VOLT_MASK | PCFG_DCDC_MODE_MIRROR_MASK)) |
          PCFG_DCDC_VOLTAGE_480MHZ |
          (((value >> 16) & 0x7U) << 12);
  putreg32(value, HPM_PCFG_DCDC_MODE);

  value = getreg32(HPM_PCFG_DCDC_ADVPARAM);
  value = (value & ~PCFG_DCDC_MIN_DUT_MASK) | PCFG_DCDC_MIN_DUT(0x6a);
  putreg32(value, HPM_PCFG_DCDC_ADVPARAM);

  while ((getreg32(HPM_PCFG_DCDC_MODE) & PCFG_DCDC_READY) == 0)
    {
    }

  /* Configure CPU0 clock & AXI Sub-clock & AHB Sub-clock:
   * CPU = PLL0_CLK0 / CPU_DIV = 480MHz, AXI/AHB = 160MHz.
   * NOTE: the SYSCTL_CLOCK_CPU_* macros already subtract 1 internally
   * (the register stores divisor - 1), so pass the real divisors here.
   *
   * Like the SDK's board_init_clock, select PLL0_CLK0 BEFORE tuning
   * the PLL: the clock request itself may be what powers the PLL up.
   */

  value = SYSCTL_CLOCK_CPU_MUX_PLL0_CLK0 |
          SYSCTL_CLOCK_CPU_DIV(CPU_DIV) |
          SYSCTL_CLOCK_CPU_SUB0_DIV(AXI_SUB_DIV) |
          SYSCTL_CLOCK_CPU_SUB1_DIV(AHB_SUB_DIV);
  putreg32(value, HPM_SYSCTL_CLOCK_CPU_CLK_TOP_CPU0);

  /* Configure PLL0 clock frequency: PLL0 = 24MHz * MFI = 960MHz,
   * same as the hpm5300evk SDK board.  PLLCTLV2 takes a single MFI
   * write followed by a stability wait.
   *
   * NOTE: the ROM bootloader does not necessarily leave PLL0 enabled
   * on this board, so set the MFI ENABLE bit explicitly (the SDK
   * boards rely on the ROM having done this already).
   */

  value = PLL0_FREQ % PLLCTLV2_PLL_XTAL_FREQ * PLLCTLV2_PLL_MFN_FACTOR;
  putreg32(value, HPM_PLLCTLV2_PLL0_MFN);

  value = HPM_PLLCTLV2_PLL_MFI_ENABLE |
          (PLL0_FREQ / PLLCTLV2_PLL_XTAL_FREQ);
  putreg32(value, HPM_PLLCTLV2_PLL0_MFI);
  for (value = 0; value < 1000000 &&
                  !hpm_pll_reg_stable(HPM_PLLCTLV2_PLL0_MFI); value++)
    {
    }

  /* Configure PLL0_CLK0 Post Divider: divide by 1.0 (960MHz) */

  value = (getreg32(HPM_PLLCTLV2_PLL0_DIV0) &
          ~HPM_PLLCTLV2_PLL_DIV_DIV_MASK) |
          HPM_PLLCTLV2_PLL_DIV_DIV(PLL0_DIV) |
          HPM_PLLCTLV2_PLL_DIV_ENABLE;
  putreg32(value, HPM_PLLCTLV2_PLL0_DIV0);
  for (value = 0; value < 1000000 &&
                  !hpm_pll_reg_stable(HPM_PLLCTLV2_PLL0_DIV0); value++)
    {
    }

  /* Machine timer on the 24MHz oscillator */

  value = (getreg32(HPM_SYSCTL_CLOCK_CLK_TOP_MCT0) &
          ~(SYSCTL_CLOCK_MUX_MASK | SYSCTL_CLOCK_DIV_MASK)) |
          (SYSCTL_CLOCK_MUX_OSC0_CLK0 | SYSCTL_CLOCK_DIV(1));
  putreg32(value, HPM_SYSCTL_CLOCK_CLK_TOP_MCT0);
}

void hpm_uart_clockconfig(void)
{
  uint32_t value;

  value = getreg32(HPM_SYSCTL_GROUP0_LINK0_VALUE);

#ifdef CONFIG_HPM_UART0
  putreg32(SYSCTL_CLOCK_MUX_OSC0_CLK0 | SYSCTL_CLOCK_DIV(1),
           HPM_SYSCTL_CLOCK_CLK_TOP_UART0);
  value |= SYSCTL_GROUP0_LINK0_UART0;
#endif

#ifdef CONFIG_HPM_UART1
  putreg32(SYSCTL_CLOCK_MUX_OSC0_CLK0 | SYSCTL_CLOCK_DIV(1),
           HPM_SYSCTL_CLOCK_CLK_TOP_UART1);
  value |= SYSCTL_GROUP0_LINK0_UART1;
#endif

#if defined CONFIG_HPM_UART2
  putreg32(SYSCTL_CLOCK_MUX_OSC0_CLK0 | SYSCTL_CLOCK_DIV(1),
           HPM_SYSCTL_CLOCK_CLK_TOP_UART2);
  value |= SYSCTL_GROUP0_LINK0_UART2;
#endif

#if defined CONFIG_HPM_UART3
  putreg32(SYSCTL_CLOCK_MUX_OSC0_CLK0 | SYSCTL_CLOCK_DIV(1),
           HPM_SYSCTL_CLOCK_CLK_TOP_UART3);
  value |= SYSCTL_GROUP0_LINK0_UART3;
#endif

#if defined CONFIG_HPM_UART4
  putreg32(SYSCTL_CLOCK_MUX_OSC0_CLK0 | SYSCTL_CLOCK_DIV(1),
           HPM_SYSCTL_CLOCK_CLK_TOP_UART4);
  value |= SYSCTL_GROUP0_LINK0_UART4;
#endif

#if defined CONFIG_HPM_UART5
  putreg32(SYSCTL_CLOCK_MUX_OSC0_CLK0 | SYSCTL_CLOCK_DIV(1),
           HPM_SYSCTL_CLOCK_CLK_TOP_UART5);
  value |= SYSCTL_GROUP0_LINK0_UART5;
#endif

#if defined CONFIG_HPM_UART6
  putreg32(SYSCTL_CLOCK_MUX_OSC0_CLK0 | SYSCTL_CLOCK_DIV(1),
           HPM_SYSCTL_CLOCK_CLK_TOP_UART6);
  value |= SYSCTL_GROUP0_LINK0_UART6;
#endif

  putreg32(value, HPM_SYSCTL_GROUP0_LINK0_SET);

#ifdef CONFIG_HPM_UART7
  putreg32(SYSCTL_CLOCK_MUX_OSC0_CLK0 | SYSCTL_CLOCK_DIV(1),
           HPM_SYSCTL_CLOCK_CLK_TOP_UART7);
  value = getreg32(HPM_SYSCTL_GROUP0_LINK1_VALUE);
  value |= SYSCTL_GROUP0_LINK1_UART7;
  putreg32(value, HPM_SYSCTL_GROUP0_LINK1_SET);
#endif
}
