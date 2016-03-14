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

#define SWITCH_NAME_LENGTH 12
#define ON_MESSAGE  1
#define OFF_MESSAGE 0


class switchesClass
{
 public:
  uint8_t sw_int;
  switchesClass(uint32_t _pin, String name, void (*_switchISR)(void));
  void begin(void);
  void pub_switch(uint8_t* item_module); // publish changes in switch state

 private:
  uint32_t pin;  // connector pin connected to switch
  uint8_t switch_state; // current state of the switch
  uint8_t switch_name[SWITCH_NAME_LENGTH]; // name of the switch for publish message

  void switch_msg(uint8_t* item_module); // publish switch state to MQTT
  void (*switchISR)(void); // class function executed when switch ISR occurs
  void decrement_sw_int(void); // decrement int count
};

