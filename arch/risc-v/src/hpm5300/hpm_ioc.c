/***************************************************************************
 * arch/risc-v/src/hpm5300/hpm_ioc.c
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
 ***************************************************************************/

/***************************************************************************
 * Included Files
 ***************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>
#include <errno.h>

#include "hardware/hpm_ioc.h"
#include "riscv_internal.h"
#include "hpm_ioc.h"

/***************************************************************************
 * Private Data
 ***************************************************************************/

/* This table is indexed by the Pad Mux register index and provides the
 * index to the corresponding Pad Control register.
 *
 * REVISIT:  This could be greatly simplified:  The Pad Control registers
 * map 1-to-1 with the Pad Mux registers except for two regions where
 * there are no corresponding Pad Mux registers.  The entire table could be
 * replaced to two range checks and the appropriate offset added to the Pad
 * Mux Register index.
 */

#if defined (CONFIG_ARCH_FAMILY_HPM5300)
static const uint16_t g_iocctl_map[HPM_IOC_PAD_NREGISTERS] =
{
  HPM_IOC_PAD_PA00_INDEX,
  HPM_IOC_PAD_PA01_INDEX,
  HPM_IOC_PAD_PA02_INDEX,
  HPM_IOC_PAD_PA03_INDEX,
  HPM_IOC_PAD_PA04_INDEX,
  HPM_IOC_PAD_PA05_INDEX,
  HPM_IOC_PAD_PA06_INDEX,
  HPM_IOC_PAD_PA07_INDEX,
  HPM_IOC_PAD_PA08_INDEX,
  HPM_IOC_PAD_PA09_INDEX,
  HPM_IOC_PAD_PA10_INDEX,
  HPM_IOC_PAD_PA11_INDEX,
  HPM_IOC_PAD_PA12_INDEX,
  HPM_IOC_PAD_PA13_INDEX,
  HPM_IOC_PAD_PA14_INDEX,
  HPM_IOC_PAD_PA15_INDEX,
  HPM_IOC_PAD_PA16_INDEX,
  HPM_IOC_PAD_PA17_INDEX,
  HPM_IOC_PAD_PA18_INDEX,
  HPM_IOC_PAD_PA19_INDEX,
  HPM_IOC_PAD_PA20_INDEX,
  HPM_IOC_PAD_PA21_INDEX,
  HPM_IOC_PAD_PA22_INDEX,
  HPM_IOC_PAD_PA23_INDEX,
  HPM_IOC_PAD_PA24_INDEX,
  HPM_IOC_PAD_PA25_INDEX,
  HPM_IOC_PAD_PA26_INDEX,
  HPM_IOC_PAD_PA27_INDEX,
  HPM_IOC_PAD_PA28_INDEX,
  HPM_IOC_PAD_PA29_INDEX,
  HPM_IOC_PAD_PA30_INDEX,
  HPM_IOC_PAD_PA31_INDEX,
  HPM_IOC_PAD_PB00_INDEX,
  HPM_IOC_PAD_PB01_INDEX,
  HPM_IOC_PAD_PB02_INDEX,
  HPM_IOC_PAD_PB03_INDEX,
  HPM_IOC_PAD_PB04_INDEX,
  HPM_IOC_PAD_PB05_INDEX,
  HPM_IOC_PAD_PB06_INDEX,
  HPM_IOC_PAD_PB07_INDEX,
  HPM_IOC_PAD_PB08_INDEX,
  HPM_IOC_PAD_PB09_INDEX,
  HPM_IOC_PAD_PB10_INDEX,
  HPM_IOC_PAD_PB11_INDEX,
  HPM_IOC_PAD_PB12_INDEX,
  HPM_IOC_PAD_PB13_INDEX,
  HPM_IOC_PAD_PB14_INDEX,
  HPM_IOC_PAD_PB15_INDEX,
  HPM_IOC_PAD_PX00_INDEX,
  HPM_IOC_PAD_PX01_INDEX,
  HPM_IOC_PAD_PX02_INDEX,
  HPM_IOC_PAD_PX03_INDEX,
  HPM_IOC_PAD_PX04_INDEX,
  HPM_IOC_PAD_PX05_INDEX,
  HPM_IOC_PAD_PX06_INDEX,
  HPM_IOC_PAD_PX07_INDEX,
  HPM_IOC_PAD_PY00_INDEX,
  HPM_IOC_PAD_PY01_INDEX,
  HPM_IOC_PAD_PY02_INDEX,
  HPM_IOC_PAD_PY03_INDEX,
  HPM_IOC_PAD_PY04_INDEX,
  HPM_IOC_PAD_PY05_INDEX,
  HPM_IOC_PAD_PY06_INDEX,
  HPM_IOC_PAD_PY07_INDEX,
};
#endif

/***************************************************************************
 * Public Functions
 ***************************************************************************/

unsigned int hpm_iocpad_map(unsigned int iocpad)
{
  return (unsigned int)g_iocctl_map[iocpad];
}

int hpm_iocpad_configure(uintptr_t padctl, ioc_pinset_t ioset)
{
  uint32_t regval = 0;
  uint32_t value;
  uint32_t alt;
  uintptr_t funcctl;

  /* Select CMOS input or Schmitt Trigger input */

  if ((ioset & PAD_SCHMITT_TRIGGER) != 0)
    {
      regval |= IOC_PAD_PAD_HYS;
    }

  /* Select drive strength */

  value = (ioset & PAD_DRIVE_MASK) >> PAD_DRIVE_SHIFT;
  regval |= IOC_PAD_PAD_DS(value);

  /* Select speed */

  value = (ioset & PAD_SPEED_MASK) >> PAD_SPEED_SHIFT;
  regval |= IOC_PAD_PAD_SPD(value);

  /* Select CMOS output or Open Drain output */

  if ((ioset & PAD_OPENDRAIN) != 0)
    {
      regval |= IOC_PAD_PAD_OD;
    }

  /* Handle pull/keep selection */

  switch (ioset & _PAD_PULLTYPE_MASK)
    {
      default:
        break;

      case _PAD_PULL_KEEP:
        {
          regval |= IOC_PAD_PAD_KE;
        }
        break;

      case _PAD_PULL_ENABLE:
        {
          regval |= (IOC_PAD_PAD_KE | IOC_PAD_PAD_PE);

          /* PS selects the pull direction: 1 = pull-up, 0 = pull-down.
           * Only the pull-down description has a zero description field,
           * so any non-zero description selects pull-up.
           */

          if ((ioset & _PAD_PULLDESC_MASK) != 0)
            {
              regval |= IOC_PAD_PAD_PS;
            }

          value = (ioset & _PAD_PULLDESC_MASK) >> _PAD_PULLDESC_SHIFT;
          regval |= IOC_PAD_PAD_PRS(value);
        }
        break;
    }

  /* Select slow/fast slew rate */

  if ((ioset & PAD_SLEW_FAST) != 0)
    {
      regval |= IOC_PAD_PAD_SR;
    }

  /* Write the result to the specified Pad Control register */

  putreg32(regval, padctl);

  /* Configure IOC FUNCTL Register */

  funcctl = padctl - 0x0004;
  regval = 0;

  /* Configure analog */

  if ((ioset & FUNC_ANALOG_MASK) == FUNC_ANALOG)
    {
      regval |= IOC_PAD_FUNC_ANALOG;
      putreg32(regval, funcctl);

      return OK;
    }

  if ((ioset & PAD_ALT_MASK) == PAD_ALT0)
    {
      regval |= IOC_PAD_FUNC_LOOP_BACK;
      putreg32(regval, funcctl);

      return OK;
    }

  alt = (ioset & PAD_ALT_MASK) >> PAD_ALT_SHIFT;
  regval |= IOC_PAD_FUNC_ALT_SELECT(alt);

  putreg32(regval, funcctl);

  return OK;
}
