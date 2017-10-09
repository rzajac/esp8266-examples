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
#include <uart.h>
#include <osapi.h>
#include <easygpio/easygpio.h>

#define BLINK_PIN 2

static os_timer_t timer;

void ICACHE_FLASH_ATTR blink(void *arg)
{
  uint8_t flag = (uint8_t) ((uint32_t) arg);

  os_printf("LED: %d\n", flag);
  easygpio_outputSet(BLINK_PIN, flag);

  os_timer_disarm(&timer);
  os_timer_setfn(&timer, (os_timer_func_t *)blink, (void *) (flag == 1 ? 0 : 1));
  os_timer_arm(&timer, 1000, false);
}

void ICACHE_FLASH_ATTR user_init()
{
  // We don't need WiFi for this example.
  wifi_station_set_auto_connect(false);
  wifi_station_disconnect();
  wifi_softap_dhcps_stop();

  // Initialize UART.
  uart_init(BIT_RATE_74880, BIT_RATE_74880);

  // Initialize GPIOs
  gpio_init();

  easygpio_pinMode(BLINK_PIN, EASYGPIO_NOPULL, EASYGPIO_OUTPUT);

  os_timer_disarm(&timer);
  os_timer_setfn(&timer, (os_timer_func_t *)blink, 0);
  os_timer_arm(&timer, 1000, false);
}
