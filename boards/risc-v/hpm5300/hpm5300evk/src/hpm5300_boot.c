/****************************************************************************
 * boards/risc-v/hpm5300/hpm5300evk/src/hpm5300_boot.c
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

#include <nuttx/debug.h>

#include <nuttx/board.h>
#include <arch/board/board.h>

#include "chip.h"
#include "hpm_gpio.h"
#include "riscv_internal.h"

#include "hpm5300evk.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: hpm6340_boardinitialize
 *
 * Description:
 *   All FE310 architectures must provide the following entry point.
 *   This entry point is called early in the initialization -- after all
 *   memory has been configured and mapped but before any devices have been
 *   initialized.
 *
 ****************************************************************************/

void hpm5300_boardinitialize(void)
{
  int i;

  /* Silence the GPIO interrupt controller: the IF flags do not reset to
   * zero and floating pads would otherwise keep the GPIO0_A PLIC source
   * asserted from reset, starving the CPU in a claim/complete loop.
   * Clear the flags, then disable both the synchronous (IE) and the
   * asynchronous (AS) interrupt paths.
   */

  for (i = 0; i < HPM_GPIO_NBANKS; i++)
    {
      putreg32(0xffffffff, HPM_GPIO_IF_VAL(i));
      putreg32(0, HPM_GPIO_IE_VAL(i));
      putreg32(0, HPM_GPIO_AS_VAL(i));
    }

  /* Configure on-board LEDs if LED support has been selected. */

#ifdef CONFIG_ARCH_LEDS
  hpm5300_autoled_initialize();
#endif
}

/****************************************************************************
 * Name: board_late_initialize
 *
 * Description:
 *   If CONFIG_BOARD_LATE_INITIALIZE is selected, then an additional
 *   initialization call will be performed in the boot-up sequence to a
 *   function called board_late_initialize().  board_late_initialize() will
 *   be called immediately after up_initialize() is called and just before
 *   the initial application is started.  This additional initialization
 *   phase may be used, for example, to initialize board-specific device
 *   drivers.
 *
 * Input Parameters:
 *   None.
 *
 * Returned Value:
 *   None.
 *
 ****************************************************************************/

#ifdef CONFIG_BOARD_LATE_INITIALIZE
void board_late_initialize(void)
{
  hpm5300_bringup();
}
#endif
