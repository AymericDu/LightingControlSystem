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

#ifndef _P9813_H_
#define _P9813_H_

#include "connectors.h"
#include <rflpc17xx/rflpc17xx.h>
#include <stdint.h>

void setColorRGB(uint8_t led, uint8_t red, uint8_t green, uint8_t blue);

void initColorRGB(connector_t connector);

void getColorRGB(uint8_t led, uint8_t *red, uint8_t *green, uint8_t *blue);

#endif
