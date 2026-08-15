# ##############################################################################
# boards/risc-v/hpm5300/hpm5300evk/src/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################

set(SRCS hpm5300_bringup.c hpm5300_boot.c hpm5300_bootheader.c)

if(CONFIG_ARCH_LEDS)
  list(APPEND SRCS hpm5300_autoleds.c)
endif()

if(CONFIG_USERLED_LOWER)
  list(APPEND SRCS hpm5300_userleds.c)
endif()

if(CONFIG_INPUT_BUTTONS_LOWER)
  list(APPEND SRCS hpm5300_buttons.c)
endif()

target_sources(board PRIVATE ${SRCS})

set(LDFILE ld.script)

set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/${LDFILE}")
