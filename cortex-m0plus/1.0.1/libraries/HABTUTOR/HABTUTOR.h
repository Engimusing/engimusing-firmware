/*
  Copyright (c) 2015 Engimusing LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include "Arduino.h"


class HABTUTORClass
{
 public:
  HABTUTORClass();
  void begin(void);
 private:
  static void decode_cmd(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
  static void handle_tick(void);
  static void pub_led(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id);
  static void pub_red_switch(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id);
  static void pub_black_switch(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id);
  static void pub_reed_switch(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id);
  static void pub_light_sensor(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id);
  static void pub_pot_voltage(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id);
  static uint32_t read_pot(void);
};


extern HABTUTORClass HABT;

