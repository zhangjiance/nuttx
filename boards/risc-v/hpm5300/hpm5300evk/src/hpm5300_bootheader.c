/****************************************************************************
 * boards/risc-v/hpm5300/hpm5300evk/src/hpm5300_bootheader.c
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

#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define HPM_BOOTHEADER_TAG    (0xBFU)

/* Image layout: the ROM bootloader expects the boot header at flash
 * offset 0x1000 and the nor_cfg_option at offset 0x400. The NuttX image
 * (vectors + text + data LMA) starts at offset 0x3000 and executes in
 * place (XIP).
 *
 * NOTE: fw_info.offset is the image offset RELATIVE TO THE BOOT HEADER
 * (0x80003000 - 0x80001000 = 0x2000), matching the SDK's
 * __app_offset__ = __app_load_addr__ - __boot_header_load_addr__.
 */

#define APP_LOAD_ADDR         (0x80003000UL)
#define APP_OFFSET            (0x2000UL)

/****************************************************************************
 * Private Types
 ****************************************************************************/

typedef struct
{
  uint32_t offset;            /* 0x0: offset to boot_header start */
  uint32_t size;              /* 0x4: size in bytes */
  uint32_t flags;             /* 0x8: fw type / hash type */
  uint32_t reserved0;         /* 0xC */
  uint32_t load_addr;         /* 0x10: load address */
  uint32_t reserved1;         /* 0x14 */
  uint32_t entry_point;       /* 0x18: application entry */
  uint32_t reserved2;         /* 0x1C */
  uint8_t  hash[64];          /* 0x20: hash value */
  uint8_t  iv[32];            /* 0x60: initial vector */
} fw_info_table_t;

typedef struct
{
  uint8_t  tag;               /* 0x0: must be '0xbf' */
  uint8_t  version;           /* 0x1: header version */
  uint16_t length;            /* 0x2: header length, max 8KB */
  uint32_t flags;             /* 0x4: SRK set / signature type */
  uint16_t sw_version;        /* 0x8: software version */
  uint8_t  fuse_version;      /* 0xA: fuse version */
  uint8_t  fw_count;          /* 0xB: number of fw */
  uint16_t dc_block_offset;   /* 0xC: device config block offset */
  uint16_t sig_block_offset;  /* 0xE: signature block offset */
} boot_header_t;

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* NOR flash read configuration option (XIP) */

__attribute__ ((section(".nor_cfg_option"), used))
const uint32_t nor_cfg_option[4] =
{
  0xfcf90002, 0x00000005, 0x1000, 0x0
};

/* Firmware info table */

extern void __start(void);
extern uint32_t __fw_size__[];

__attribute__ ((section(".fw_info_table"), used))
const fw_info_table_t fw_info =
{
  APP_OFFSET,                 /* offset */
  (uint32_t)__fw_size__,      /* size */
  0,                          /* flags */
  0,                          /* reserved0 */
  APP_LOAD_ADDR,              /* load_addr */
  0,                          /* reserved1 */
  (uint32_t)&__start,         /* entry_point */
  0,                          /* reserved2 */
  {0},                        /* hash */
  {0},                        /* iv */
};

/* Boot header */

__attribute__ ((section(".boot_header"), used))
const boot_header_t boot_header =
{
  HPM_BOOTHEADER_TAG,         /* tag */
  0x10,                       /* version */
  sizeof(boot_header_t) + sizeof(fw_info_table_t),
  0,                          /* flags */
  0,                          /* sw_version */
  0,                          /* fuse_version */
  1,                          /* fw_count */
  0,                          /* dc_block_offset */
  0,                          /* sig_block_offset */
};
