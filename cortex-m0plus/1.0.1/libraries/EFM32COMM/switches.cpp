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

static const char tail[]     = "\"}\r\n";
static const char topu[]     = "{\"TOP\":\"";
static const char midu[]     = "\",\"PLD\":\"";
static const char rs2on[]    = "CLOSED";
static const char rs2off[]   = "OPEN";


switchesClass::switchesClass(uint32_t _pin, String name, void (*_switchISR)(void))
{
  pin = _pin;
  sw_int = 1;
  switch_state = 1;
  strcpy((char*)switch_name, name.c_str());
  switchISR = _switchISR;
}

void switchesClass::begin(void)
{
  pinMode(pin, GPIO_MODE_INPUTPULLFILTER);
  digitalWrite(pin, HIGH);
  attachInterrupt(pin, switchISR, CHANGE);
}


void switchesClass::pub_switch(uint8_t* item_module)
{
  static uint8_t event_in_progress = 0;
  uint8_t current_switch = (~digitalRead(pin) & 0x01);

  if(sw_int < 0) {sw_int = 0;}

  if((event_in_progress == 0) && (sw_int == 0) && (current_switch != switch_state)) {
    switch_msg(item_module);
  }
  if(event_in_progress || sw_int) {
    if(event_in_progress == 0) {
      decrement_sw_int();
      switch_msg(item_module);
      event_in_progress = 1;
    } else if(event_in_progress == 1) {
      if(sw_int) {
	decrement_sw_int();
	switch_msg(item_module);
      } else {
	event_in_progress = 0;
      }
    }
  }
}

void switchesClass::switch_msg(uint8_t* item_module)
{
  char rs1[MODULE_STRING_LENGTH+15];

  sprintf(rs1, "%s%s/SWITCH/%s/STATE%s", topu, item_module, switch_name, midu);

  uint8_t onoff = (switch_state) ? OFF_MESSAGE : ON_MESSAGE;
  switch_state = (switch_state) ? 0 : 1;
  if(onoff == ON_MESSAGE) {
    Serial.printf("%s%s%s",rs1,rs2on,tail);
  } else if(onoff == OFF_MESSAGE) {
    Serial.printf("%s%s%s",rs1,rs2off,tail);
  }
}

void switchesClass::decrement_sw_int(void)
{
  noInterrupts();
  sw_int--;
  interrupts();
}
