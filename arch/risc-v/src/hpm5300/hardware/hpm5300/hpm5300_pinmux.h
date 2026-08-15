/****************************************************************************
 * arch/risc-v/src/hpm5300/hardware/hpm5300/hpm5300_pinmux.h
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

#ifndef __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_PINMUX_H
#define __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_PINMUX_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "hpm_ioc.h"
#include "hpm_gpio.h"

/* UART0 */

#define GPIO_UART0_TXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA00_INDEX))
#define GPIO_UART0_TXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PB00_INDEX))
#define GPIO_UART0_TXD3    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PY00_INDEX))

#define GPIO_UART0_RXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA01_INDEX))
#define GPIO_UART0_RXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PB01_INDEX))
#define GPIO_UART0_RXD3    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PY01_INDEX))

/* UART1 */

#define GPIO_UART1_TXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA07_INDEX))
#define GPIO_UART1_TXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PB07_INDEX))
#define GPIO_UART1_TXD3    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PY07_INDEX))

#define GPIO_UART1_RXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA06_INDEX))
#define GPIO_UART1_RXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PB06_INDEX))
#define GPIO_UART1_RXD3    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PY06_INDEX))

/* UART2 */

#define GPIO_UART2_TXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA08_INDEX))
#define GPIO_UART2_TXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PB08_INDEX))

#define GPIO_UART2_RXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA09_INDEX))
#define GPIO_UART2_RXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PB09_INDEX))

/* UART3 */

#define GPIO_UART3_TXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA15_INDEX))
#define GPIO_UART3_TXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PB15_INDEX))

#define GPIO_UART3_RXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA14_INDEX))
#define GPIO_UART3_RXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PB14_INDEX))

/* UART4 */

#define GPIO_UART4_TXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA16_INDEX))
#define GPIO_UART4_TXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PX00_INDEX))

#define GPIO_UART4_RXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA17_INDEX))
#define GPIO_UART4_RXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PX01_INDEX))

/* UART5 */

#define GPIO_UART5_TXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA23_INDEX))
#define GPIO_UART5_TXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PX07_INDEX))

#define GPIO_UART5_RXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA22_INDEX))
#define GPIO_UART5_RXD2    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PX06_INDEX))

/* UART6 */

#define GPIO_UART6_TXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA24_INDEX))
#define GPIO_UART6_RXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA25_INDEX))

/* UART7 */

#define GPIO_UART7_TXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA31_INDEX))
#define GPIO_UART7_RXD1    (GPIO_PERIPH | PAD_ALT2 | GPIO_PADMUX(HPM_IOC_PAD_PA30_INDEX))

#endif /* __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_PINMUX_H */
