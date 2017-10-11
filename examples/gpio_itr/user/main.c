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

// Missing function prototypes.
void ets_isr_mask(unsigned intr);
void ets_isr_unmask(unsigned intr);

// The positive edge counter.
volatile uint32_t edge_counter;

// Logging timer.
static os_timer_t timer;

void ICACHE_FLASH_ATTR log_counter(void *arg)
{
  os_printf("Edge counter: %d\n", edge_counter);
}

void isr_handler(void *arg)
{
  uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
  if (gpio_status & BIT(2)) {

    // Disable interrupt.
    gpio_pin_intr_state_set(GPIO_ID_PIN(2), GPIO_PIN_INTR_DISABLE);

    // Clear interrupt status.
    GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status & BIT(2));

    uint32_t *c = arg;
    (*c)++;

    gpio_pin_intr_state_set(GPIO_ID_PIN(2), GPIO_PIN_INTR_POSEDGE);

    // The ESP8266 Technical reference PDF at 13.1.2. says:
    //
    // In non-OS version of SDK, functions with ICACHE_FLASH_ATTR properties,
    // including print function os_printf defined in IROM section of the Flash,
    // should NOT be invoked in the whole process of interrupt handling
    // process such as GPIO, UART, FRC, etc.
    //
    // This might be the solution:

    os_timer_disarm(&timer);
    os_timer_setfn(&timer, (os_timer_func_t *) log_counter, NULL);
    os_timer_arm(&timer, 10, false);
  }
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
  //
  // Each pin may have different "roles". Here we setup GPIO2 as regular GPIO pin.
  // The detailed information about available pin functions are
  // available at: http://espressif.com/sites/default/files/documentation/0d-esp8266_pin_list_release_15-11-2014.xlsx
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);

  // Disable pin pull up resistor.
  PIN_PULLUP_DIS(PERIPHS_IO_MUX_GPIO2_U);

  // Configure GPIO2 as input.
  GPIO_DIS_OUTPUT(GPIO_ID_PIN(2));

  ETS_GPIO_INTR_DISABLE();

  // Set GPIO pin as input.
  ETS_GPIO_INTR_ATTACH(isr_handler, &edge_counter);

  // Reset GPIO_PIN2 register to 0.
  gpio_register_set(GPIO_PIN_ADDR(GPIO_ID_PIN(2)),
                    GPIO_PIN_INT_TYPE_SET(GPIO_PIN_INTR_DISABLE) |
                    GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_DISABLE) |
                    GPIO_PIN_SOURCE_SET(GPIO_AS_PIN_SOURCE));

  // Clear GPIO2 status.
  GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, GPIO_ID_PIN(2));

  // Enable interrupt.
  gpio_pin_intr_state_set(GPIO_ID_PIN(2), GPIO_PIN_INTR_POSEDGE);

  ETS_GPIO_INTR_ENABLE();
}
