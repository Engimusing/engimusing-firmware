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

#include <Arduino.h>
#include "switches.h"
#include "EFM32COMM.h"


switchesClass::switchesClass(String name, void (*_switchISR)(void), uint8_t bounce_count, uint8_t switch_typ)
{
  strcpy((char*)switch_name, name.c_str());
  switchISR = _switchISR;
  bounce_cnt = bounce_count;
  switch_type = switch_typ;
  event_in_progress = 0;
  sw_previous_state = 0;
}


void switchesClass::begin(uint32_t _pin, uint8_t* module)
{
  pin = _pin;
  intrPinMode(pin, INPUT_PU_FILTER);
  init = 0;
  sw_int = 0;
  if(switch_type == SW_MOMENTARY) {
    attachInterrupt(pin, switchISR, RISING);
  }
}

void switchesClass::pub_switch(uint8_t* module)
{
  uint8_t current_switch = (intrDigitalRead(pin) & 0x01);

  if(sw_int < 0) {sw_int = 0;}

  if(init == 0) {
    init = 1;
    switch_state = (intrDigitalRead(pin) & 0x01);
    switch_msg(module, switch_state);
    sw_int = 0;
    return;
  }
  if((event_in_progress == 0) && ( (switch_type == SW_DETECTOR) && (switch_state != current_switch)
				   || (switch_type == SW_MOMENTARY) && (sw_int > 0)) ) { // switch event happened
    event_in_progress = 1;
  } else if((event_in_progress > 0) && (event_in_progress < bounce_cnt)) { // wait until bounce count
    event_in_progress++;
  } else if(event_in_progress >= bounce_cnt) { // report event
    if(switch_type == SW_MOMENTARY) {
      //Serial.printf("%d ",sw_int);
      switch_msg(module, 1);
      clear_sw_int();
    } else {
      if(switch_state != current_switch) {
	switch_state = current_switch;
	switch_msg(module, current_switch);
      }
    }
    event_in_progress = 0;
    return;
  }
}

void switchesClass::switch_msg(uint8_t* module, uint8_t current_switch)
{

  Serial.printf("{\"TOP\":\"%s?/SWITCH/%s\",\"PLD\":\"", module, switch_name);

  if(current_switch) {
    Serial.printf("CLOSED\"}\r\n");
  } else {
    Serial.printf("OPEN\"}\r\n");
  }
}

void switchesClass::decrement_sw_int(void)
{
  noInterrupts();
  sw_int--;
  interrupts();
}

void switchesClass::clear_sw_int(void)
{
  noInterrupts();
  sw_int = 0;
  interrupts();
}
