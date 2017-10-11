/**
 * Copyright 2017 Rafal Zajac <rzajac@gmail.com>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include <user_interface.h>
#include <osapi.h>
#include <uart.h>

void ICACHE_FLASH_ATTR sys_init_done(void)
{
  os_printf("Hello World!\n");
}

void ICACHE_FLASH_ATTR user_init()
{
  // We don't need WiFi for this simple example.
  wifi_set_opmode_current(NULL_MODE);

  // Initialize UART.
  uart_init(BIT_RATE_74880, BIT_RATE_74880);

  // Set callback when system is done initializing.
  system_init_done_cb(sys_init_done);
}
