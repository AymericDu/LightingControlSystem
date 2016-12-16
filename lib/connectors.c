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

#include "connectors.h"
#include "base_shield_v20.h"

connector_pins_t CONNECTORS[] = {
  {BASE_SHIELD_D2_2, BASE_SHIELD_D2_3},
  {BASE_SHIELD_D3_3, BASE_SHIELD_D3_4},
  {BASE_SHIELD_D4_4, BASE_SHIELD_D4_5},
  {BASE_SHIELD_D5_5, BASE_SHIELD_D5_6},
  {BASE_SHIELD_D6_6, BASE_SHIELD_D6_7},
  {BASE_SHIELD_D7_7, BASE_SHIELD_D7_8},
  {BASE_SHIELD_D8_8, BASE_SHIELD_D8_9},
  {BASE_SHIELD_A0_0, BASE_SHIELD_A0_1},
  {BASE_SHIELD_A1_1, BASE_SHIELD_A1_2},
  {BASE_SHIELD_A2_2, BASE_SHIELD_A2_3},
  {BASE_SHIELD_A3_3, BASE_SHIELD_A3_4}
};
