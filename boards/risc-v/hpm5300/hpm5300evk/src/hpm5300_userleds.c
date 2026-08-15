/****************************************************************************
 * boards/risc-v/hpm5300/hpm5300evk/src/hpm5300_userleds.c
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
#include <stdbool.h>
#include <nuttx/board.h>
#include <arch/board/board.h>

#include "chip.h"
#include "hpm_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* The hpm5300evk user LED is on PA23 and is active low */

#define GPIO_LED1  (GPIO_OUTPUT | GPIO_OUTPUT_ONE | GPIO_PORTA | GPIO_PIN23)

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* This array maps an LED number to GPIO pin configuration */

static uint32_t g_ledcfg[BOARD_NLEDS] =
{
  GPIO_LED1,
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_userled_initialize
 ****************************************************************************/

uint32_t board_userled_initialize(void)
{
  /* Configure the LED GPIO for output */

  hpm_gpio_config(GPIO_LED1);

  return BOARD_NLEDS;
}

/****************************************************************************
 * Name: board_userled
 ****************************************************************************/

void board_userled(int led, bool ledon)
{
  if ((unsigned)led < BOARD_NLEDS)
    {
      /* The LED is active low: writing false turns it on */

      hpm_gpio_write(g_ledcfg[led], !ledon);
    }
}

/****************************************************************************
 * Name: board_userled_all
 ****************************************************************************/

void board_userled_all(uint32_t ledset)
{
  hpm_gpio_write(GPIO_LED1, (ledset & BOARD_USERLED_BIT) == 0);
}
