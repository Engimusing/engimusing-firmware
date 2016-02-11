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

#include "EFM32COMM.h"
#include "EFM32ZGUSB.h"
#include <Arduino.h>


extern LEUARTClass Serial;
extern boardIO IO;
extern AnalogLP Analog;

void EFM32ZGUSBClass::begin(void)
{
  uint8_t s1[] = "EFMUSB";

  COMM.add_module(s1, decode_cmd);
  IO.commChipID();
  Serial.printf("{\"MODULE\":\"EFMUSB\"}\r\n");
}

EFM32ZGUSBClass::EFM32ZGUSBClass()
{
}

/*

{"CPUID":"24353a02522fa331", "ADDR":"01"}   // set address to 01 for cpuid
{"CPUID":"24353a02522fa331", "MOD":"EFMUSB", "TYPE":"LED", "ID":"RED",   "ON"} // CPUID is target
{"ADDR":"01", "MOD":"EFMUSB", "TYPE":"LED", "ID":"RED",   "ON"} // address 01 is target

// following are targeted to the first (or only) device in a chain
{"MOD":"EFMUSB", "TYPE":"LED", "ID":"RED",   "ON"}
{"MOD":"EFMUSB", "TYPE":"LED", "ID":"RED",   "OFF"}
{"MOD":"EFMUSB", "TYPE":"LED", "ID":"GREEN", "ON"}
{"MOD":"EFMUSB", "TYPE":"LED", "ID":"GREEN", "OFF"}
{"MOD":"EFMUSB", "TYPE":"LED", "ID":"BLUE",  "ON"}
{"MOD":"EFMUSB", "TYPE":"LED", "ID":"BLUE",  "OFF"}
{"MOD":"EFMUSB", "TYPE":"CPUTEMP"}
{"MOD":"EFMUSB", "TYPE":"CPUVDD"}
{"MOD":"EFMUSB", "TYPE":"BRDINFO"}
{"MOD":"EFMUSB", "TYPE":"BRDNAME"}
{"MOD":"EFMUSB", "TYPE":"BLVER"}
{"MOD":"EFMUSB", "TYPE":"CHIPID"}
{"MOD":"EFMUSB", "TYPE":"CPUTYPE"}
{"MOD":"EFMUSB", "TYPE":"FLASHSIZE"}
{"MOD":"EFMUSB", "TYPE":"SRAMSIZE"}

*/

void EFM32ZGUSBClass::decode_cmd(uint8_t* item_type, 
				 uint8_t* item_id, 
				 uint8_t* item_action, 
				 uint8_t* item_p1,
				 uint8_t* item_p2)
{
  // Types:
  const char led[]       = "LED";
  const char cputemp[]   = "CPUTEMP";
  const char cpuvdd[]    = "CPUVDD";
  const char brdinfo[]   = "BRDINFO";
  const char brdname[]   = "BRDNAME";
  const char blver[]     = "BLVER";
  const char chipid[]    = "CHIPID";
  const char cputype[]   = "CPUTYPE";
  const char flashsize[] = "FLASHSIZE";
  const char sramsize[]  = "SRAMSIZE";
  // IDs:
  const char red[]       = "RED";
  const char blue[]      = "BLUE";
  const char green[]     = "GREEN";
  // ACTIONs:
  const char on[]        = "ON";
  const char off[]       = "OFF";


  if(strcmp((char*)item_type, led) == 0) {
    if(strcmp((char*)item_id, red) == 0) {
      if(strcmp((char*)item_action, on) == 0) {
	IO.ledRedOn();
	return;
      }
      if(strcmp((char*)item_action, off) == 0) {
	IO.ledRedOff();
	return;
      }
    }
    if(strcmp((char*)item_id, blue) == 0) {
      if(strcmp((char*)item_action, on) == 0) {
	IO.ledBlueOn();
	return;
      }
      if(strcmp((char*)item_action, off) == 0) {
	IO.ledBlueOff();
	return;
      }
    }
    if(strcmp((char*)item_id, green) == 0) {
      if(strcmp((char*)item_action, on) == 0) {
	IO.ledGreenOn();
	return;
      }
      if(strcmp((char*)item_action, off) == 0) {
	IO.ledGreenOff();
	return;
      }
    }
  }
  if(strcmp((char*)item_type, cputemp) == 0) {
    Analog.commTemperature();
    return;
  }
  if(strcmp((char*)item_type, cpuvdd) == 0) {
    Analog.commVDD();
    return;
  }
  if(strcmp((char*)item_type, brdinfo) == 0) {
    IO.printBoardParameters();
    return;
  }
  if(strcmp((char*)item_type, brdname) == 0) {
    IO.commBoardName();
    return;
  }
  if(strcmp((char*)item_type, blver) == 0) {
    IO.commBootloaderVersion();
    return;
  }
  if(strcmp((char*)item_type, chipid) == 0) {
    IO.commChipID();
    return;
  }
  if(strcmp((char*)item_type, cputype) == 0) {
    IO.commCPUtype();
    return;
  }
  if(strcmp((char*)item_type, flashsize) == 0) {
    IO.commFlashSize();
    return;
  }
  if(strcmp((char*)item_type, sramsize) == 0) {
    IO.commSRAMsize();
    return;
  }
}


EFM32ZGUSBClass ZGUSB;


