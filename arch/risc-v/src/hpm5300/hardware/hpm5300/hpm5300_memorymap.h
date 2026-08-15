/****************************************************************************
 * arch/risc-v/src/hpm5300/hardware/hpm5300/hpm5300_memorymap.h
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

#ifndef __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_MEMORYMAP_H
#define __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_MEMORYMAP_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* On-chip flash */

#define HPM_FLASH_BASE        0x80000000

/* ILM / DLM local memory */

#define HPM_ILM_BASE          0x00000000
#define HPM_ILM_SIZE          0x00020000  /* 128K */
#define HPM_DLM_BASE          0x00080000
#define HPM_DLM_SIZE          0x00020000  /* 128K */

/* AHB SRAM */

#define HPM_AHB_SRAM_BASE     0xF0400000
#define HPM_AHB_SRAM_SIZE     0x00008000  /* 32K */

/* PLIC */

#define HPM_PLIC_BASE         0xE4000000

/* Machine timer */

#define HPM_MCHTMR_BASE       0xE6000000

/* GPIO */

#define HPM_GPIO0_BASE        0xF00D0000
#define HPM_GPIOM_BASE        0xF00D8000

/* Timers */

#define HPM_GPTMR0_BASE       0xF0000000
#define HPM_GPTMR1_BASE       0xF0004000
#define HPM_GPTMR2_BASE       0xF0008000
#define HPM_GPTMR3_BASE       0xF000C000

/* UARTs */

#define HPM_UART0_BASE        0xF0040000
#define HPM_UART1_BASE        0xF0044000
#define HPM_UART2_BASE        0xF0048000
#define HPM_UART3_BASE        0xF004C000
#define HPM_UART4_BASE        0xF0050000
#define HPM_UART5_BASE        0xF0054000
#define HPM_UART6_BASE        0xF0058000
#define HPM_UART7_BASE        0xF005C000
#define HPM_PUART_BASE        0xF4124000

/* I2C */

#define HPM_I2C0_BASE         0xF0060000
#define HPM_I2C1_BASE         0xF0064000
#define HPM_I2C2_BASE         0xF0068000
#define HPM_I2C3_BASE         0xF006C000

/* SPI */

#define HPM_SPI0_BASE         0xF0070000
#define HPM_SPI1_BASE         0xF0074000
#define HPM_SPI2_BASE         0xF0078000
#define HPM_SPI3_BASE         0xF007C000

/* Misc */

#define HPM_CRC0_BASE         0xF0080000
#define HPM_TSNS_BASE         0xF0090000
#define HPM_MBX0A_BASE        0xF00A0000
#define HPM_EWDG0_BASE        0xF00B0000
#define HPM_EWDG1_BASE        0xF00B4000
#define HPM_PEWDG_BASE        0xF4128000
#define HPM_HDMA_BASE         0xF00C8000
#define HPM_DMAMUX_BASE       0xF00C4000

/* CAN */

#define HPM_CAN0_BASE         0xF0280000
#define HPM_CAN1_BASE         0xF0284000
#define HPM_CAN2_BASE         0xF0288000
#define HPM_CAN3_BASE         0xF028C000

/* Motor control */

#define HPM_PTPC_BASE         0xF02FC000
#define HPM_QEI0_BASE         0xF0300000
#define HPM_QEI1_BASE         0xF0304000
#define HPM_QEO0_BASE         0xF0308000
#define HPM_QEO1_BASE         0xF030C000
#define HPM_MMC0_BASE         0xF0310000
#define HPM_MMC1_BASE         0xF0314000
#define HPM_PWM0_BASE         0xF0318000
#define HPM_PWM1_BASE         0xF031C000
#define HPM_RDC_BASE          0xF0320000
#define HPM_PLB_BASE          0xF0324000
#define HPM_SYNT_BASE         0xF0328000
#define HPM_SEI_BASE          0xF032C000
#define HPM_TRGM0_BASE        0xF033C000

/* USB */

#define HPM_USB0_BASE         0xF300C000

/* Security */

#define HPM_SDP_BASE          0xF3040000
#define HPM_SEC_BASE          0xF3044000
#define HPM_MON_BASE          0xF3048000
#define HPM_RNG_BASE          0xF304C000
#define HPM_OTP_BASE          0xF3050000
#define HPM_KEYM_BASE         0xF3054000

/* Analog */

#define HPM_ADC0_BASE         0xF3080000
#define HPM_ADC1_BASE         0xF3084000
#define HPM_DAC0_BASE         0xF3090000
#define HPM_DAC1_BASE         0xF3094000
#define HPM_OPAMP0_BASE       0xF30A0000
#define HPM_OPAMP1_BASE       0xF30A4000
#define HPM_ACMP_BASE         0xF30B0000

/* System control */

#define HPM_SYSCTL_BASE       0xF4000000
#define HPM_IOC_BASE          0xF4040000
#define HPM_PLLCTL_BASE       0xF40C0000
#define HPM_PPOR_BASE         0xF4100000
#define HPM_PCFG_BASE         0xF4104000
#define HPM_PCFG_DCDC_MODE    (HPM_PCFG_BASE + 0x10)
#define HPM_PCFG_DCDC_ADVPARAM (HPM_PCFG_BASE + 0x24)
#define HPM_PGPR0_BASE        0xF4110000
#define HPM_PGPR1_BASE        0xF4114000
#define HPM_PIOC_BASE         0xF4118000
#define HPM_PGPIO_BASE        0xF411C000
#define HPM_PTMR_BASE         0xF4120000
#define HPM_PDGO_BASE         0xF4134000

#endif /* __ARCH_RISCV_SRC_HPM5300_HARDWARE_HPM5300_HPM5300_MEMORYMAP_H */
