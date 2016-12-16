/*
 * Copyright (C) 2016
 * Authors : Benoît Delecroix, Mickaël Cartion and Aymeric Ducroquetz
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

#include "TM1637.h"
#include "connectors.h"
#include <rflpc17xx/rflpc17xx.h>

extern const connector_pins_t CONNECTORS[];

static rflpc_pin_t _dio_pin;
static rflpc_pin_t _clk_pin;

static int _off;
static int _colon;
static uint8_t _brightness;
static uint8_t _content[4];

const uint8_t DIGIT_TABLE[] = {0x3f, 0x06, 0x5b, 0x4f,
                               0x66, 0x6d, 0x7d, 0x07,
                               0x7f, 0x6f, 0x77, 0x7c,
                               0x39, 0x5e, 0x79, 0x71
                              };

// We recommand the usage of:
// TM1637_init: To init the TM1637
// TM1637_output: To print decimal values to the TM1637
// TM1637_output_position: To print one decimal value to one column to the TM1637
// TM1637_sendRawDigits: Print values to the TM1637 from hexadecimal value that represents each segment to turn on/off.

// Convert a decimal value to a hexa one.
inline uint8_t conv(uint8_t n)
{
   uint8_t segments;

   if (n <= sizeof(DIGIT_TABLE)) {
       segments = DIGIT_TABLE[n];
   }else if (n == 0xFF) {
       segments = DIGIT_NULL;
   } else {
       segments = DIGIT_UNKOWN;
   }

   return segments;
}

// Tell to the TM1637 that we'll start to send data.
void TM1637_start()
{
  rflpc_gpio_set_pin_mode_output(_dio_pin, 1);
  rflpc_gpio_set_pin_mode_output(_clk_pin, 1);
  rflpc_gpio_set_pin_mode_output(_dio_pin, 0);
  rflpc_gpio_set_pin_mode_output(_clk_pin, 0);
}

// Tell to the TM1637 that we'll stop to send data.
void TM1637_stop()
{
  rflpc_gpio_set_pin_mode_output(_clk_pin, 0);
  rflpc_gpio_set_pin_mode_output(_dio_pin, 0);
  rflpc_gpio_set_pin_mode_output(_clk_pin, 1);
  rflpc_gpio_set_pin_mode_output(_dio_pin, 1);
}

// Send a value to the TM1637. Don't use it
int TM1637_send(uint8_t data)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        rflpc_gpio_set_pin_mode_output(_clk_pin, 0);
        rflpc_gpio_set_pin_mode_output(_dio_pin, data & 1);
        data >>= 1;
        rflpc_gpio_set_pin_mode_output(_clk_pin, 1);
    }

    // check ack
    rflpc_gpio_set_pin_mode_output(_clk_pin, 0);
    rflpc_gpio_set_pin_mode_output(_dio_pin, 1);
    rflpc_gpio_set_pin_mode_output(_clk_pin, 1);
    rflpc_gpio_set_pin_mode_input(_dio_pin, RFLPC_PIN_MODE_RESISTOR_NONE);

    uint16_t count = 0;
    while (rflpc_gpio_get_val(_dio_pin)) {
        count++;
        if (count >= 200) {
            rflpc_gpio_set_pin_mode_output(_dio_pin, 1);
            return 0;
        }
    }

    rflpc_gpio_set_pin_mode_output(_dio_pin, 1);
    return 1;
}

// Send bit per bit to every segment per column. Each column value need a representation of bits in hexa
// For exemple, to print 9317 it's: TM1637_sendRawDigits(3, {0x6F,0x4F,0x06,0x07})
// If you wanna turn on the colon, you need to put b7 to 1 in the second digit.
// For example with 93:17, its {0x6F,0xCF,0x06,0x07}
//      b0
// b5 |    | b1
//      b6
// b4 |    | b2
//      b3
int TM1637_sendRawDigits(int light, uint8_t raw[4])
{
    uint8_t i;
    for (i=0; i < 4; i++) {
        _content[i] = raw[i];
    }

    TM1637_start();
    TM1637_send(ADDR_AUTO);
    TM1637_stop();
    TM1637_start();
    TM1637_send(0xC0);
    for (i=0; i < 4; i++) {
        TM1637_send(raw[i]);
    }
    TM1637_stop();
    TM1637_setBrightness(light);
    return 0;
}

// Initialize the TM1637 to clkpin and diopin.
// clkpin and diopin are GPIO pins.
void TM1637_init(connector_t connector)
{
    _clk_pin = CONNECTORS[connector].pin1;
    _dio_pin = CONNECTORS[connector].pin2;

    rflpc_gpio_set_pin_mode_output(_dio_pin, 0);
    rflpc_gpio_set_pin_mode_output(_clk_pin, 0);

    _brightness = 2;
    _colon      = 0;
    _off        = 1;

    uint8_t i;
    for (i = 0; i < sizeof(_content); i++) {
        _content[i] = DIGIT_NULL;

    }

    TM1637_sendRawDigits(1, _content);
}

// Set the brightness value to the 7seg
// brightness: The value of the brightness [0-7]
void TM1637_setBrightness(uint8_t brightness)
{
    if (brightness > 7)
        brightness = 7;

    _brightness = brightness;

    TM1637_start();
    TM1637_send(0x88 | _brightness);
    TM1637_stop();
}

// Send value to each column to the 7seg.
// light: The brightness of the 7seg [0-7]
// colon: Enable or disable the colon [0-1]
// raw: an array of 4 values which will be print to the 7seg. Value can go from 0 to 9
int TM1637_output(int light, int colon, uint8_t raw[4])
{
    uint8_t  i;
    for (i = 0; i < 4; i++) {
        _content[i] = conv(raw[i]);
    }
    if (colon) {
        _content[POSITION_COLON] |= 0x80;
    }
    TM1637_start();
    TM1637_send(ADDR_AUTO);
    TM1637_stop();
    TM1637_start();
    TM1637_send(0xC0);
    for (i = 0; i < 4; i++) {
        TM1637_send(_content[i]);
    }
    TM1637_stop();

    TM1637_setBrightness(light);

    return 0;
}

// Print a value at a selected position in the 7seg module.
// light: The brightness of the 7seg [0-7]
// position: The position where you want to print val [0-3]
// colon: Enable or disable the colon [0-1]
// val: The value you want to print [0..9-A..F]
int TM1637_output_position(int light, int position, int colon, uint8_t val)
{
    if(position > 4 && position < 0)
        return -1;

    _content[position]=conv(val);

    if (colon) {
        _content[POSITION_COLON] |= 0x80;
    }

    TM1637_sendRawDigits(light, _content);
    return 0;
}
