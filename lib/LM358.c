/*
 * Copyright (C) 2016
 * Authors : Jimmy MARMIN, Mahamoud Mohamed FARAH and Alexandre Bécart
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

#include "LM358.h"
#include <rflpc17xx/rflpc17xx.h>

static rflpc_pin_t _pin;
extern const connector_pins_t CONNECTORS[];

// FIX ADC : A supprimer lors de la prochaine release de RFLPC
static int _pin_to_adc_function(rflpc_pin_t pin)
{
   switch (pin) {
      case RFLPC_PIN_P0_23:
      case RFLPC_PIN_P0_24:
      case RFLPC_PIN_P0_25:
      case RFLPC_PIN_P0_26:
         return 0x01;
      case RFLPC_PIN_P0_3:
      case RFLPC_PIN_P0_2:
         return 0x02;
      case RFLPC_PIN_P1_30:
      case RFLPC_PIN_P1_31:
      default:
         return 0x03;
   }
}
// FIX ADC

void LM358_init(connector_t connector) {
  _pin = CONNECTORS[connector].pin1;
  rflpc_adc_init(_pin, RFLPC_CCLK_8);

  // FIX ADC : A supprimer lors de la prochaine release de RFLPC.
  rflpc_pin_set(_pin, _pin_to_adc_function(_pin), RFLPC_PIN_MODE_RESISTOR_PULL_UP, 0);
  // FIX ADC
}

int LM358_read_light() {
  rflpc_adc_sample(_pin);
  return rflpc_adc_read(_pin);
}
