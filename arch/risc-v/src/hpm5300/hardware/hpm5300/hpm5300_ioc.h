/****************************************************************************
 * arch/risc-v/src/hpm5300/hardware/hpm5300/hpm5300_ioc.h
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

#ifndef __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_IOC_H
#define __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_IOC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "hardware/hpm_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* HPM5300 IOC register organization:
 *
 *   PAD[n].FUNC_CTL   HPM_IOC_BASE + n * 8
 *   PAD[n].PAD_CTL    HPM_IOC_BASE + n * 8 + 4
 *
 * Valid pads: PA00-PA31 (0-31), PB00-PB15 (32-47),
 *             PX00-PX07 (416-423), PY00-PY07 (448-455).
 */

#define HPM_IOC_PAD_NREGISTERS                   64

/* PAD register group index macro definition */

#define HPM_IOC_PAD_PA00_INDEX                   (0UL)
#define HPM_IOC_PAD_PA01_INDEX                   (1UL)
#define HPM_IOC_PAD_PA02_INDEX                   (2UL)
#define HPM_IOC_PAD_PA03_INDEX                   (3UL)
#define HPM_IOC_PAD_PA04_INDEX                   (4UL)
#define HPM_IOC_PAD_PA05_INDEX                   (5UL)
#define HPM_IOC_PAD_PA06_INDEX                   (6UL)
#define HPM_IOC_PAD_PA07_INDEX                   (7UL)
#define HPM_IOC_PAD_PA08_INDEX                   (8UL)
#define HPM_IOC_PAD_PA09_INDEX                   (9UL)
#define HPM_IOC_PAD_PA10_INDEX                   (10UL)
#define HPM_IOC_PAD_PA11_INDEX                   (11UL)
#define HPM_IOC_PAD_PA12_INDEX                   (12UL)
#define HPM_IOC_PAD_PA13_INDEX                   (13UL)
#define HPM_IOC_PAD_PA14_INDEX                   (14UL)
#define HPM_IOC_PAD_PA15_INDEX                   (15UL)
#define HPM_IOC_PAD_PA16_INDEX                   (16UL)
#define HPM_IOC_PAD_PA17_INDEX                   (17UL)
#define HPM_IOC_PAD_PA18_INDEX                   (18UL)
#define HPM_IOC_PAD_PA19_INDEX                   (19UL)
#define HPM_IOC_PAD_PA20_INDEX                   (20UL)
#define HPM_IOC_PAD_PA21_INDEX                   (21UL)
#define HPM_IOC_PAD_PA22_INDEX                   (22UL)
#define HPM_IOC_PAD_PA23_INDEX                   (23UL)
#define HPM_IOC_PAD_PA24_INDEX                   (24UL)
#define HPM_IOC_PAD_PA25_INDEX                   (25UL)
#define HPM_IOC_PAD_PA26_INDEX                   (26UL)
#define HPM_IOC_PAD_PA27_INDEX                   (27UL)
#define HPM_IOC_PAD_PA28_INDEX                   (28UL)
#define HPM_IOC_PAD_PA29_INDEX                   (29UL)
#define HPM_IOC_PAD_PA30_INDEX                   (30UL)
#define HPM_IOC_PAD_PA31_INDEX                   (31UL)
#define HPM_IOC_PAD_PB00_INDEX                   (32UL)
#define HPM_IOC_PAD_PB01_INDEX                   (33UL)
#define HPM_IOC_PAD_PB02_INDEX                   (34UL)
#define HPM_IOC_PAD_PB03_INDEX                   (35UL)
#define HPM_IOC_PAD_PB04_INDEX                   (36UL)
#define HPM_IOC_PAD_PB05_INDEX                   (37UL)
#define HPM_IOC_PAD_PB06_INDEX                   (38UL)
#define HPM_IOC_PAD_PB07_INDEX                   (39UL)
#define HPM_IOC_PAD_PB08_INDEX                   (40UL)
#define HPM_IOC_PAD_PB09_INDEX                   (41UL)
#define HPM_IOC_PAD_PB10_INDEX                   (42UL)
#define HPM_IOC_PAD_PB11_INDEX                   (43UL)
#define HPM_IOC_PAD_PB12_INDEX                   (44UL)
#define HPM_IOC_PAD_PB13_INDEX                   (45UL)
#define HPM_IOC_PAD_PB14_INDEX                   (46UL)
#define HPM_IOC_PAD_PB15_INDEX                   (47UL)
#define HPM_IOC_PAD_PX00_INDEX                   (416UL)
#define HPM_IOC_PAD_PX01_INDEX                   (417UL)
#define HPM_IOC_PAD_PX02_INDEX                   (418UL)
#define HPM_IOC_PAD_PX03_INDEX                   (419UL)
#define HPM_IOC_PAD_PX04_INDEX                   (420UL)
#define HPM_IOC_PAD_PX05_INDEX                   (421UL)
#define HPM_IOC_PAD_PX06_INDEX                   (422UL)
#define HPM_IOC_PAD_PX07_INDEX                   (423UL)
#define HPM_IOC_PAD_PY00_INDEX                   (448UL)
#define HPM_IOC_PAD_PY01_INDEX                   (449UL)
#define HPM_IOC_PAD_PY02_INDEX                   (450UL)
#define HPM_IOC_PAD_PY03_INDEX                   (451UL)
#define HPM_IOC_PAD_PY04_INDEX                   (452UL)
#define HPM_IOC_PAD_PY05_INDEX                   (453UL)
#define HPM_IOC_PAD_PY06_INDEX                   (454UL)
#define HPM_IOC_PAD_PY07_INDEX                   (455UL)

/* Register address macro definition */

#define HPM_IOC_PAD_FUNC_CTL_OFFSET(n)     ((n) << 3)
#define HPM_IOC_PAD_PAD_CTL_OFFSET(n)      (((n) << 3) + 4)

#define HPM_IOC_PAD_FUNC_CTL_ADDRESS(n)    (HPM_IOC_BASE + HPM_IOC_PAD_FUNC_CTL_OFFSET(n))
#define HPM_IOC_PAD_PAD_CTL_ADDRESS(n)     (HPM_IOC_BASE + HPM_IOC_PAD_PAD_CTL_OFFSET(n))

#endif /* __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_IOC_H */
