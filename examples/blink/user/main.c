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

// Read GPIO2 current state.
#define GPIO2_V ((GPIO_REG_READ(GPIO_IN_ADDRESS)&BIT2)!=0)
// Set GPIO2 high.
#define GPIO2_H (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, BIT2))
// Set GPIO2 low.
#define GPIO2_L (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, BIT2))

static os_timer_t timer;

void ICACHE_FLASH_ATTR blink(void *arg)
{
  bool state = GPIO2_V;

  os_printf("LED state: %d\n", state);
  state ? GPIO2_L : GPIO2_H;
}

void ICACHE_FLASH_ATTR user_init()
{
  // We don't need WiFi for this example.
  wifi_set_opmode(NULL_MODE);

  // Initialize UART.
  uart_init(BIT_RATE_74880, BIT_RATE_74880);

  // Initialize GPIOs
  gpio_init();

  // Set up GPIO2.

  // Select function of the pin.
  // Each pin may have different "roles". Here we setup GPIO2 as regular GPIO pin.
  // The detailed information about available pin functions are
  // available at: http://espressif.com/sites/default/files/documentation/0d-esp8266_pin_list_release_15-11-2014.xlsx
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);

  // Disable pin pull up resistor.
  PIN_PULLUP_DIS(PERIPHS_IO_MUX_GPIO2_U);

  // Set pin as output with initial value high.
  GPIO_OUTPUT_SET(2, 1);

  // Setup timer to call our callback in 1 second intervals.
  os_timer_disarm(&timer);
  os_timer_setfn(&timer, (os_timer_func_t *) blink, 0);
  os_timer_arm(&timer, 1000, true);
}
