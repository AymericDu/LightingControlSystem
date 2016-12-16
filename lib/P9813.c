/*
 * Copyright (C) 2016
 * Authors : Alexandre Bécart and Aymeric Ducroquetz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "P9813.h"
#include "connectors.h"
#include <rflpc17xx/rflpc17xx.h>
#include <stdint.h>

#define NB_LED 1

extern const connector_pins_t CONNECTORS[];

static rflpc_pin_t _data_pin;
static rflpc_pin_t _clk_pin;
static uint8_t rgb[NB_LED*3];

void sendByte(uint8_t b) {
    uint8_t i;

    // Send one bit at a time, starting with the MSB
    for (i=0; i<8; i++) {
        if (b & 0x80)
          rflpc_gpio_set_pin(_data_pin);
        else
          rflpc_gpio_clr_pin(_data_pin);

        rflpc_gpio_set_pin(_clk_pin);
        rflpc_gpio_clr_pin(_clk_pin);
        b <<= 1;
    }
}

void sendColor(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t r67 = ~(red & 0xC0) >> 6;;
    uint8_t g67 = ~(green & 0xC0) >> 4;
    uint8_t b67 = ~(blue & 0xC0) >> 2;
    uint8_t verify = 0xC0 | r67 | g67 | b67;

    sendByte(verify);
    sendByte(blue);
    sendByte(green);
    sendByte(red);
}

void setColorRGB(uint8_t led, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t i;

    // Send data frame prefix (32x "0")
    sendByte(0x00);
    sendByte(0x00);
    sendByte(0x00);
    sendByte(0x00);

    // Send color data for each one of the leds
    for (i=0; i < NB_LED; i++) {
        if (i == led) {
            rgb[i*3 + 0] = red;
            rgb[i*3 + 1] = green;
            rgb[i*3 + 2] = blue;
        }
        sendColor(rgb[i*3 + 0], rgb[i*3 + 1], rgb[i*3 + 2]);
    }

    // Terminate data frame (32x "0")
    sendByte(0x00);
    sendByte(0x00);
    sendByte(0x00);
    sendByte(0x00);
}

void initColorRGB(connector_t connector) {
  uint8_t i;

  _clk_pin = CONNECTORS[connector].pin1;
  _data_pin = CONNECTORS[connector].pin2;

  rflpc_gpio_set_pin_mode_output(_clk_pin, 0);
  rflpc_gpio_set_pin_mode_output(_data_pin, 0);

  for (i=0; i < NB_LED; i++) {
    rgb[i*3 + 0] = 0;
    rgb[i*3 + 1] = 0;
    rgb[i*3 + 2] = 0;
  }
}

void getColorRGB(uint8_t led, uint8_t *red, uint8_t *green, uint8_t *blue) {
  *red = rgb[led*3 + 0];
  *green = rgb[led*3 + 1];
  *blue = rgb[led*3 + 2];
}
