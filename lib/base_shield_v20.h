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

#ifndef _BASE_SHIELD_H_
#define _BASE_SHIELD_H_

#include <rflpc17xx/rflpc17xx.h>

#define MBED_UNDEFINED 0

/* Digital */
#define BASE_SHIELD_D2_2 MBED_DIP8
#define BASE_SHIELD_D2_3 MBED_DIP26
#define BASE_SHIELD_D3_3 MBED_DIP26
#define BASE_SHIELD_D3_4 MBED_DIP25
#define BASE_SHIELD_D4_4 MBED_DIP25
#define BASE_SHIELD_D4_5 MBED_DIP24
#define BASE_SHIELD_D5_5 MBED_DIP24
#define BASE_SHIELD_D5_6 MBED_DIP23
#define BASE_SHIELD_D6_6 MBED_DIP23
#define BASE_SHIELD_D6_7 MBED_DIP10
#define BASE_SHIELD_D7_7 MBED_DIP10
#define BASE_SHIELD_D7_8 MBED_DIP9
#define BASE_SHIELD_D8_8 MBED_DIP9
#define BASE_SHIELD_D8_9 MBED_DIP22

/* Analog */
#define BASE_SHIELD_A0_0 MBED_DIP15
#define BASE_SHIELD_A0_1 MBED_DIP16
#define BASE_SHIELD_A1_1 MBED_DIP16
#define BASE_SHIELD_A1_2 MBED_DIP17
#define BASE_SHIELD_A2_2 MBED_DIP17
#define BASE_SHIELD_A2_3 MBED_DIP18
#define BASE_SHIELD_A3_3 MBED_DIP18
#define BASE_SHIELD_A3_4 MBED_DIP19

/* UART */
#define BASE_SHIELD_UART_RX MBED_DIP27
#define BASE_SHIELD_UART_DX MBED_DIP28

/* I2C */
#define BASE_SHIELD_I2C_SDA MBED_UNDEFINED
#define BASE_SHIELD_I2C_SCL MBED_UNDEFINED

#endif /* _BASE_SHIELD_H_ */
