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

#ifndef _CONNECTORS_H_
#define _CONNECTORS_H_

#include <stdint.h>

typedef enum {
  /** BASE SHIELD **/
  /* Digital */
  BASE_SHIELD_D2 = 0,
  BASE_SHIELD_D3,
  BASE_SHIELD_D4,
  BASE_SHIELD_D5,
  BASE_SHIELD_D6,
  BASE_SHIELD_D7,
  BASE_SHIELD_D8,
  /* Analog */
  BASE_SHIELD_A0,
  BASE_SHIELD_A1,
  BASE_SHIELD_A2,
  BASE_SHIELD_A3
} connector_t;

typedef struct {
  uint8_t pin1;
  uint8_t pin2;
} connector_pins_t;

#endif
