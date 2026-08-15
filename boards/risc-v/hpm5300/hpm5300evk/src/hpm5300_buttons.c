/****************************************************************************
 * boards/risc-v/hpm5300/hpm5300evk/src/hpm5300_buttons.c
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

#include <stdint.h>
#include <errno.h>
#include <nuttx/arch.h>
#include <nuttx/board.h>
#include <nuttx/irq.h>
#include <arch/board/board.h>

#include "chip.h"
#include "hpm_gpio.h"
#include "riscv_internal.h"

#ifdef CONFIG_INPUT_BUTTONS_LOWER

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* The hpm5300evk user button is on PA9 and is active low.  Configure it
 * as an input with a 22K pull-up and Schmitt trigger.
 */

#define GPIO_BUTTON1 (GPIO_INPUT | PAD_PULL_UP_22K | PAD_SCHMITT_TRIGGER | \
                      GPIO_PORTA | GPIO_PIN9)

#define BUTTON1_PIN   9

/* Bit mask for PA9 in the 32-bit IF/OE/IE... register banks.  NOTE:
 * GPIO_PIN9 is the pinset *encoding* (9 << 16), not the mask -- using it
 * in a bank register would touch bits 19/16 instead of bit 9.
 */

#define BUTTON1_MASK  GPIO_PIN(BUTTON1_PIN)

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const uint32_t g_buttons[NUM_BUTTONS] =
{
  GPIO_BUTTON1,
};

/* Interrupt handler installed by board_button_irq() */

static xcpt_t g_btn_handler;
static FAR void *g_btn_arg;

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_button_initialize
 *
 * Description:
 *   board_button_initialize() must be called to initialize button
 *   resources.  After that, board_buttons() may be called to collect the
 *   current state of all buttons or board_button_irq() may be called to
 *   register button interrupt handlers.
 *
 ****************************************************************************/

uint32_t board_button_initialize(void)
{
  int i;

  /* Configure the GPIO pins as inputs */

  for (i = 0; i < NUM_BUTTONS; i++)
    {
      hpm_gpio_config(g_buttons[i]);
    }

  return NUM_BUTTONS;
}

/****************************************************************************
 * Name: board_buttons
 ****************************************************************************/

uint32_t board_buttons(void)
{
  uint32_t ret = 0;
  int i;

  /* Check the state of each key */

  for (i = 0; i < NUM_BUTTONS; i++)
    {
      /* The button is active low: a LOW value means pressed */

      if (!hpm_gpio_read(g_buttons[i]))
        {
          ret |= (1 << i);
        }
    }

  return ret;
}

/****************************************************************************
 * Name: hpm5300_button_isr
 *
 * Description:
 *   Interrupt handler for the GPIO0 bank A interrupt (PLIC source
 *   IRQn_GPIO0_A).  Clears the button's GPIO interrupt flag and forwards
 *   the interrupt to the handler installed by board_button_irq().
 *
 ****************************************************************************/

static int hpm5300_button_isr(int irq, FAR void *context, FAR void *arg)
{
  /* Clear the GPIO interrupt flag (write 1 clears) */

  putreg32(BUTTON1_MASK, HPM_GPIO_IF_VAL(HPM_GPIO_GPIOA));

  if (g_btn_handler != NULL)
    {
      return g_btn_handler(irq, context, g_btn_arg);
    }

  return OK;
}

/****************************************************************************
 * Name: board_button_irq
 *
 * Description:
 *   board_button_irq() may be called to register an interrupt handler that
 *   will be called when a button is depressed or released, or to unregister
 *   the handler.  The button interrupts on both edges via the GPIO0 bank A
 *   interrupt (HPM_IRQ_GPIO0_A).
 *
 ****************************************************************************/

int board_button_irq(int id, xcpt_t irqhandler, void *arg)
{
  int ret;

  if (id < MIN_IRQBUTTON || id > MAX_IRQBUTTON)
    {
      return -EINVAL;
    }

  if (irqhandler == NULL)
    {
      /* This is a request to disable interrupts */

      hpm_gpio_irqenable(GPIO_BUTTON1, false);
      up_disable_irq(HPM_IRQ_GPIO0_A);
      irq_detach(HPM_IRQ_GPIO0_A);

      g_btn_handler = NULL;
      g_btn_arg     = NULL;

      return OK;
    }

  /* Save the callback and attach our wrapper ISR */

  g_btn_handler = irqhandler;
  g_btn_arg     = arg;

  ret = irq_attach(HPM_IRQ_GPIO0_A, hpm5300_button_isr, NULL);
  if (ret < 0)
    {
      g_btn_handler = NULL;
      g_btn_arg     = NULL;
      return ret;
    }

  /* Configure PA9 to interrupt on both edges (press and release) and
   * enable the interrupt at the GPIO module; up_enable_irq() takes care
   * of the PLIC priority and enable bits.
   */

  hpm_gpio_irqconfig(GPIO_BUTTON1, true);
  up_enable_irq(HPM_IRQ_GPIO0_A);

  /* Drain any stale PLIC pending state and the GPIO interrupt flag: this
   * function runs inside a critical section, so an edge that occurred here
   * could otherwise leave stale pending state behind.  A fresh press after
   * this function returns produces a new edge with interrupts enabled.
   */

  {
    uint32_t val;

    do
      {
        val = getreg32(HPM_PLIC_CLAIM);
        if (val != 0)
          {
            putreg32(val, HPM_PLIC_CLAIM);
          }
      }
    while (val != 0);

    putreg32(BUTTON1_MASK, HPM_GPIO_IF_VAL(0));
  }

  return OK;
}

#endif /* CONFIG_INPUT_BUTTONS_LOWER */
