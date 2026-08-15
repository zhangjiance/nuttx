/****************************************************************************
 * arch/risc-v/src/hpm5300/hardware/hpm5300/hpm5300_sysctl.h
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

#ifndef __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_SYSCTL_H
#define __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_SYSCTL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "hpm_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Register offsets *********************************************************/

#define HPM_SYSCTL_GROUP0_LINK0_VALUE               (HPM_SYSCTL_BASE + 0x0800)
#define HPM_SYSCTL_GROUP0_LINK0_SET                 (HPM_SYSCTL_BASE + 0x0804)
#define HPM_SYSCTL_GROUP0_LINK0_CLEAR               (HPM_SYSCTL_BASE + 0x0808)
#define HPM_SYSCTL_GROUP0_LINK0_TOGGLE              (HPM_SYSCTL_BASE + 0x080c)
#define HPM_SYSCTL_GROUP0_LINK1_VALUE               (HPM_SYSCTL_BASE + 0x0810)
#define HPM_SYSCTL_GROUP0_LINK1_SET                 (HPM_SYSCTL_BASE + 0x0814)
#define HPM_SYSCTL_GROUP0_LINK1_CLEAR               (HPM_SYSCTL_BASE + 0x0818)
#define HPM_SYSCTL_GROUP0_LINK1_TOGGLE              (HPM_SYSCTL_BASE + 0x081c)
#define HPM_SYSCTL_AFFILIATE_CPU0_VALUE             (HPM_SYSCTL_BASE + 0x0900)
#define HPM_SYSCTL_AFFILIATE_CPU0_SET               (HPM_SYSCTL_BASE + 0x0904)
#define HPM_SYSCTL_AFFILIATE_CPU0_CLEAR             (HPM_SYSCTL_BASE + 0x0908)
#define HPM_SYSCTL_AFFILIATE_CPU0_TOGGLE            (HPM_SYSCTL_BASE + 0x090c)

#define HPM_SYSCTL_GLOBAL00                         (HPM_SYSCTL_BASE + 0x2000)

/* Clock registers: CLOCK_CPU[0] at 0x1800, CLOCK[0..35] at 0x1804.
 * HPM5300 clock node indices: MCT0=0, CAN0-3=1-4, GPTMR0-3=9-12,
 * I2C0-3=13-16, SPI0-3=17-20, UART0-7=21-28, XPI0=29, ANA0-3=30-33,
 * REF0/1=34/35.
 */

#define HPM_SYSCTL_CLOCK_CPU_CLK_TOP_CPU0           (HPM_SYSCTL_BASE + 0x1800)
#define HPM_SYSCTL_CLOCK_CLK_TOP_MCT0               (HPM_SYSCTL_BASE + 0x1804 + 4 * 0)
#define HPM_SYSCTL_CLOCK_CLK_TOP_CAN0               (HPM_SYSCTL_BASE + 0x1804 + 4 * 1)
#define HPM_SYSCTL_CLOCK_CLK_TOP_CAN1               (HPM_SYSCTL_BASE + 0x1804 + 4 * 2)
#define HPM_SYSCTL_CLOCK_CLK_TOP_CAN2               (HPM_SYSCTL_BASE + 0x1804 + 4 * 3)
#define HPM_SYSCTL_CLOCK_CLK_TOP_CAN3               (HPM_SYSCTL_BASE + 0x1804 + 4 * 4)
#define HPM_SYSCTL_CLOCK_CLK_TOP_TMR0               (HPM_SYSCTL_BASE + 0x1804 + 4 * 9)
#define HPM_SYSCTL_CLOCK_CLK_TOP_TMR1               (HPM_SYSCTL_BASE + 0x1804 + 4 * 10)
#define HPM_SYSCTL_CLOCK_CLK_TOP_TMR2               (HPM_SYSCTL_BASE + 0x1804 + 4 * 11)
#define HPM_SYSCTL_CLOCK_CLK_TOP_TMR3               (HPM_SYSCTL_BASE + 0x1804 + 4 * 12)
#define HPM_SYSCTL_CLOCK_CLK_TOP_I2C0               (HPM_SYSCTL_BASE + 0x1804 + 4 * 13)
#define HPM_SYSCTL_CLOCK_CLK_TOP_I2C1               (HPM_SYSCTL_BASE + 0x1804 + 4 * 14)
#define HPM_SYSCTL_CLOCK_CLK_TOP_I2C2               (HPM_SYSCTL_BASE + 0x1804 + 4 * 15)
#define HPM_SYSCTL_CLOCK_CLK_TOP_I2C3               (HPM_SYSCTL_BASE + 0x1804 + 4 * 16)
#define HPM_SYSCTL_CLOCK_CLK_TOP_SPI0               (HPM_SYSCTL_BASE + 0x1804 + 4 * 17)
#define HPM_SYSCTL_CLOCK_CLK_TOP_SPI1               (HPM_SYSCTL_BASE + 0x1804 + 4 * 18)
#define HPM_SYSCTL_CLOCK_CLK_TOP_SPI2               (HPM_SYSCTL_BASE + 0x1804 + 4 * 19)
#define HPM_SYSCTL_CLOCK_CLK_TOP_SPI3               (HPM_SYSCTL_BASE + 0x1804 + 4 * 20)
#define HPM_SYSCTL_CLOCK_CLK_TOP_UART0              (HPM_SYSCTL_BASE + 0x1804 + 4 * 21)
#define HPM_SYSCTL_CLOCK_CLK_TOP_UART1              (HPM_SYSCTL_BASE + 0x1804 + 4 * 22)
#define HPM_SYSCTL_CLOCK_CLK_TOP_UART2              (HPM_SYSCTL_BASE + 0x1804 + 4 * 23)
#define HPM_SYSCTL_CLOCK_CLK_TOP_UART3              (HPM_SYSCTL_BASE + 0x1804 + 4 * 24)
#define HPM_SYSCTL_CLOCK_CLK_TOP_UART4              (HPM_SYSCTL_BASE + 0x1804 + 4 * 25)
#define HPM_SYSCTL_CLOCK_CLK_TOP_UART5              (HPM_SYSCTL_BASE + 0x1804 + 4 * 26)
#define HPM_SYSCTL_CLOCK_CLK_TOP_UART6              (HPM_SYSCTL_BASE + 0x1804 + 4 * 27)
#define HPM_SYSCTL_CLOCK_CLK_TOP_UART7              (HPM_SYSCTL_BASE + 0x1804 + 4 * 28)
#define HPM_SYSCTL_CLOCK_CLK_TOP_XPI0               (HPM_SYSCTL_BASE + 0x1804 + 4 * 29)
#define HPM_SYSCTL_CLOCK_CLK_TOP_ANA0               (HPM_SYSCTL_BASE + 0x1804 + 4 * 30)
#define HPM_SYSCTL_CLOCK_CLK_TOP_ANA1               (HPM_SYSCTL_BASE + 0x1804 + 4 * 31)
#define HPM_SYSCTL_CLOCK_CLK_TOP_ANA2               (HPM_SYSCTL_BASE + 0x1804 + 4 * 32)
#define HPM_SYSCTL_CLOCK_CLK_TOP_ANA3               (HPM_SYSCTL_BASE + 0x1804 + 4 * 33)
#define HPM_SYSCTL_CLOCK_CLK_TOP_REF0               (HPM_SYSCTL_BASE + 0x1804 + 4 * 34)
#define HPM_SYSCTL_CLOCK_CLK_TOP_REF1               (HPM_SYSCTL_BASE + 0x1804 + 4 * 35)

/* GLOBAL00 (clock scenario) bit fields *************************************/

#define SYSCTL_GLOBAL00_MUX_MASK                    (0xFFU)

/* Clock register bit fields ************************************************/

#define SYSCTL_CLOCK_MUX_MASK                       (0x700U)
#define SYSCTL_CLOCK_MUX_SHIFT                      (8U)
#define SYSCTL_CLOCK_DIV_MASK                       (0xFFU)
#define SYSCTL_CLOCK_DIV_SHIFT                      (0U)

/* Clock sources (pre-shifted to the MUX field position [10:8]) */

#define SYSCTL_CLOCK_MUX_OSC0_CLK0                  (0U << SYSCTL_CLOCK_MUX_SHIFT)
#define SYSCTL_CLOCK_MUX_PLL0_CLK0                  (1U << SYSCTL_CLOCK_MUX_SHIFT)
#define SYSCTL_CLOCK_MUX_PLL0_CLK1                  (2U << SYSCTL_CLOCK_MUX_SHIFT)
#define SYSCTL_CLOCK_MUX_PLL0_CLK2                  (3U << SYSCTL_CLOCK_MUX_SHIFT)
#define SYSCTL_CLOCK_MUX_PLL1_CLK0                  (4U << SYSCTL_CLOCK_MUX_SHIFT)
#define SYSCTL_CLOCK_MUX_PLL1_CLK1                  (5U << SYSCTL_CLOCK_MUX_SHIFT)
#define SYSCTL_CLOCK_MUX_PLL1_CLK2                  (6U << SYSCTL_CLOCK_MUX_SHIFT)
#define SYSCTL_CLOCK_MUX_PLL1_CLK3                  (7U << SYSCTL_CLOCK_MUX_SHIFT)

#define SYSCTL_CLOCK_DIV(x)                         ((x) - 1)

/* CPU clock register (CLOCK_CPU_CLK_TOP_CPU0) bit fields */

#define SYSCTL_CLOCK_CPU_MUX_SHIFT                  (8U)
#define SYSCTL_CLOCK_CPU_MUX_MASK                   (0x700U)
#define SYSCTL_CLOCK_CPU_SUB0_DIV_SHIFT             (16U)
#define SYSCTL_CLOCK_CPU_SUB0_DIV_MASK              (0xF0000U)
#define SYSCTL_CLOCK_CPU_SUB1_DIV_SHIFT             (20U)
#define SYSCTL_CLOCK_CPU_SUB1_DIV_MASK              (0xF00000U)

#define SYSCTL_CLOCK_CPU_MUX_OSC0_CLK0              (0U << SYSCTL_CLOCK_CPU_MUX_SHIFT)
#define SYSCTL_CLOCK_CPU_MUX_PLL0_CLK0              (1U << SYSCTL_CLOCK_CPU_MUX_SHIFT)
#define SYSCTL_CLOCK_CPU_MUX_PLL0_CLK1              (2U << SYSCTL_CLOCK_CPU_MUX_SHIFT)
#define SYSCTL_CLOCK_CPU_MUX_PLL0_CLK2              (3U << SYSCTL_CLOCK_CPU_MUX_SHIFT)
#define SYSCTL_CLOCK_CPU_MUX_PLL1_CLK0              (4U << SYSCTL_CLOCK_CPU_MUX_SHIFT)
#define SYSCTL_CLOCK_CPU_MUX_PLL1_CLK1              (5U << SYSCTL_CLOCK_CPU_MUX_SHIFT)
#define SYSCTL_CLOCK_CPU_MUX_PLL1_CLK2              (6U << SYSCTL_CLOCK_CPU_MUX_SHIFT)
#define SYSCTL_CLOCK_CPU_MUX_PLL1_CLK3              (7U << SYSCTL_CLOCK_CPU_MUX_SHIFT)

#define SYSCTL_CLOCK_CPU_DIV(x)                     ((x) - 1) /* Field [7:0], per hpm_sysctl_regs.h */
#define SYSCTL_CLOCK_CPU_SUB0_DIV(x)                (((x) - 1) << SYSCTL_CLOCK_CPU_SUB0_DIV_SHIFT)
#define SYSCTL_CLOCK_CPU_SUB1_DIV(x)                (((x) - 1) << SYSCTL_CLOCK_CPU_SUB1_DIV_SHIFT)

/* Group0 LINK0 bit definitions.
 * Bit n in the link register corresponds to linkable resource
 * (256 + n): resource 256=ahb0 bit0, 257=lmm0 bit1, 258=mchtmr0 bit2,
 * 260-263=can0-3 bits 4-7, 269-272=gptmr0-3 bits 13-16, 273-276=i2c0-3
 * bits 17-20, 277-280=spi0-3 bits 21-24, 281-287=uart0-6 bits 25-31.
 */

#define SYSCTL_GROUP0_LINK0_AHB0                     (1 << 0)
#define SYSCTL_GROUP0_LINK0_LMM0                     (1 << 1)
#define SYSCTL_GROUP0_LINK0_MCHTMR0                  (1 << 2)
#define SYSCTL_GROUP0_LINK0_ROM0                     (1 << 3)
#define SYSCTL_GROUP0_LINK0_CAN0                     (1 << 4)
#define SYSCTL_GROUP0_LINK0_CAN1                     (1 << 5)
#define SYSCTL_GROUP0_LINK0_CAN2                     (1 << 6)
#define SYSCTL_GROUP0_LINK0_CAN3                     (1 << 7)
#define SYSCTL_GROUP0_LINK0_PTPC                     (1 << 8)
#define SYSCTL_GROUP0_LINK0_GPTMR0                   (1 << 13)
#define SYSCTL_GROUP0_LINK0_GPTMR1                   (1 << 14)
#define SYSCTL_GROUP0_LINK0_GPTMR2                   (1 << 15)
#define SYSCTL_GROUP0_LINK0_GPTMR3                   (1 << 16)
#define SYSCTL_GROUP0_LINK0_I2C0                     (1 << 17)
#define SYSCTL_GROUP0_LINK0_I2C1                     (1 << 18)
#define SYSCTL_GROUP0_LINK0_I2C2                     (1 << 19)
#define SYSCTL_GROUP0_LINK0_I2C3                     (1 << 20)
#define SYSCTL_GROUP0_LINK0_SPI0                     (1 << 21)
#define SYSCTL_GROUP0_LINK0_SPI1                     (1 << 22)
#define SYSCTL_GROUP0_LINK0_SPI2                     (1 << 23)
#define SYSCTL_GROUP0_LINK0_SPI3                     (1 << 24)
#define SYSCTL_GROUP0_LINK0_UART0                    (1 << 25)
#define SYSCTL_GROUP0_LINK0_UART1                    (1 << 26)
#define SYSCTL_GROUP0_LINK0_UART2                    (1 << 27)
#define SYSCTL_GROUP0_LINK0_UART3                    (1 << 28)
#define SYSCTL_GROUP0_LINK0_UART4                    (1 << 29)
#define SYSCTL_GROUP0_LINK0_UART5                    (1 << 30)
#define SYSCTL_GROUP0_LINK0_UART6                    (1 << 31)

/* Group0 LINK1 bit definitions.
 * Resource 288=uart7 bit0, 289/290=wdg0/1 bits 1/2, 291=mbx0 bit3,
 * 292=tsns bit4, 293=crc0 bit5, 294/295=adc0/1 bits 6/7, 296/297=dac0/1
 * bits 8/9, 298=acmp bit10, 299/300=opa0/1 bits 11/12, 301=mot0 bit13,
 * 302=rng0 bit14, 303=sdp0 bit15, 304=kman bit16, 305=gpio bit17,
 * 306=hdma bit18, 307=xpi0 bit19, 308=usb0 bit20, 309/310=ref0/1
 * bits 21/22.
 */

#define SYSCTL_GROUP0_LINK1_UART7                    (1 << 0)
#define SYSCTL_GROUP0_LINK1_WDG0                     (1 << 1)
#define SYSCTL_GROUP0_LINK1_WDG1                     (1 << 2)
#define SYSCTL_GROUP0_LINK1_MBX0                     (1 << 3)
#define SYSCTL_GROUP0_LINK1_TSNS                     (1 << 4)
#define SYSCTL_GROUP0_LINK1_CRC0                     (1 << 5)
#define SYSCTL_GROUP0_LINK1_ADC0                     (1 << 6)
#define SYSCTL_GROUP0_LINK1_ADC1                     (1 << 7)
#define SYSCTL_GROUP0_LINK1_DAC0                     (1 << 8)
#define SYSCTL_GROUP0_LINK1_DAC1                     (1 << 9)
#define SYSCTL_GROUP0_LINK1_ACMP                     (1 << 10)
#define SYSCTL_GROUP0_LINK1_OPA0                     (1 << 11)
#define SYSCTL_GROUP0_LINK1_OPA1                     (1 << 12)
#define SYSCTL_GROUP0_LINK1_MOT0                     (1 << 13)
#define SYSCTL_GROUP0_LINK1_RNG0                     (1 << 14)
#define SYSCTL_GROUP0_LINK1_SDP0                     (1 << 15)
#define SYSCTL_GROUP0_LINK1_KMAN                     (1 << 16)
#define SYSCTL_GROUP0_LINK1_GPIO                     (1 << 17)
#define SYSCTL_GROUP0_LINK1_HDMA                     (1 << 18)
#define SYSCTL_GROUP0_LINK1_XPI0                     (1 << 19)
#define SYSCTL_GROUP0_LINK1_USB0                     (1 << 20)
#define SYSCTL_GROUP0_LINK1_REF0                     (1 << 21)
#define SYSCTL_GROUP0_LINK1_REF1                     (1 << 22)

/* Resource indices */

#define SYSCTL_RESOURCE_CPU0                         (0)
#define SYSCTL_RESOURCE_MCHTMR0                      (258)
#define SYSCTL_RESOURCE_GPTMR0                       (269)
#define SYSCTL_RESOURCE_GPTMR1                       (270)
#define SYSCTL_RESOURCE_GPTMR2                       (271)
#define SYSCTL_RESOURCE_GPTMR3                       (272)
#define SYSCTL_RESOURCE_I2C0                         (273)
#define SYSCTL_RESOURCE_I2C1                         (274)
#define SYSCTL_RESOURCE_I2C2                         (275)
#define SYSCTL_RESOURCE_I2C3                         (276)
#define SYSCTL_RESOURCE_SPI0                         (277)
#define SYSCTL_RESOURCE_SPI1                         (278)
#define SYSCTL_RESOURCE_SPI2                         (279)
#define SYSCTL_RESOURCE_SPI3                         (280)
#define SYSCTL_RESOURCE_UART0                        (281)
#define SYSCTL_RESOURCE_UART1                        (282)
#define SYSCTL_RESOURCE_UART2                        (283)
#define SYSCTL_RESOURCE_UART3                        (284)
#define SYSCTL_RESOURCE_UART4                        (285)
#define SYSCTL_RESOURCE_UART5                        (286)
#define SYSCTL_RESOURCE_UART6                        (287)
#define SYSCTL_RESOURCE_UART7                        (288)
#define SYSCTL_RESOURCE_GPIO                         (305)
#define SYSCTL_RESOURCE_HDMA                         (306)
#define SYSCTL_RESOURCE_XPI0                         (307)
#define SYSCTL_RESOURCE_USB0                         (308)
#define SYSCTL_RESOURCE_REF0                         (309)
#define SYSCTL_RESOURCE_REF1                         (310)

#endif /* __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_SYSCTL_H */
