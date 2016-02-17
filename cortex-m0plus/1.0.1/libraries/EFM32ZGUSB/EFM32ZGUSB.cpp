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
  uint8_t s2[] = "home/efmusb";

  COMM.add_module(s1, decode_cmd);
  COMM.add_module(s2, decode_cmd);
  IO.commChipID();
  Serial.printf("{\"MODULE\":\"EFMUSB\"}\r\n");
}

EFM32ZGUSBClass::EFM32ZGUSBClass()
{
}

/*

  {"CID":"24353a02522fa331", "ADR":"01"}   // set address to 01 for cpuid
  {"CID":"24353a02522fa331", "MOD":"EFMUSB", "TYP":"LED", "IID":"RED", "ON"} // CPUID is target
  {"ADR":"01", "MOD":"EFMUSB", "TYP":"LED", "IID":"RED", "ON"} // address 01 is target

  // following are targeted to the first (or only) device in a chain
  {"MOD":"EFMUSB", "TYP":"LED", "IID":"RED","ACT":"ON"}
  {"MOD":"EFMUSB", "TYP":"LED", "IID":"RED", "ACT":"OFF"}
  {"MOD":"EFMUSB", "TYP":"LED", "IID":"GREEN", "ACT":"ON"}
  {"MOD":"EFMUSB", "TYP":"LED", "IID":"GREEN", "ACT":"OFF"}
  {"MOD":"EFMUSB", "TYP":"LED", "IID":"BLUE", "ACT":"ON"}
  {"MOD":"EFMUSB", "TYP":"LED", "IID":"BLUE", "ACT":"OFF"}
  {"MOD":"EFMUSB", "TYP":"LED", "IID":"ALL", "ACT":"ON"}
  {"MOD":"EFMUSB", "TYP":"LED", "IID":"ALL", "ACT":"OFF"}

  {"MOD":"EFMUSB", "TYP":"LEDR", "IID":"RED"}
  {"MOD":"EFMUSB", "TYP":"LEDR", "IID":"GREEN"}
  {"MOD":"EFMUSB", "TYP":"LEDR", "IID":"BLUE"}
  {"MOD":"EFMUSB", "TYP":"LEDR", "IID":"ALL"}

  {"MOD":"EFMUSB", "TYP":"CPUTEMP"}
  {"MOD":"EFMUSB", "TYP":"CPUVDD"}
  {"MOD":"EFMUSB", "TYP":"BRDINFO"}
  {"MOD":"EFMUSB", "TYP":"BRDNAME"}
  {"MOD":"EFMUSB", "TYP":"BLVER"}
  {"MOD":"EFMUSB", "TYP":"CHIPID"}
  {"MOD":"EFMUSB", "TYP":"CPUTYPE"}
  {"MOD":"EFMUSB", "TYP":"FLASHSIZE"}
  {"MOD":"EFMUSB", "TYP":"SRAMSIZE"}
*/

void EFM32ZGUSBClass::decode_cmd(uint8_t* item_type, 
				 uint8_t* item_id, 
				 uint8_t* item_action, 
				 uint8_t* item_payload)
{
  // Types:
  const char led[]       = "LED";
  const char ledr[]      = "LEDR";
  const char cputemp[]   = "CPUTEMP";
  const char cpuvdd[]    = "CPUVDD";
  const char brdinfo[]   = "BRDINFO";
  const char brdname[]   = "BRDNAME";
  const char blver[]     = "BLVER";
  const char chipid[]    = "CHIPID";
  const char cputype[]   = "CPUTYPE";
  const char flashsize[] = "FLASHSIZE";
  const char sramsize[]  = "SRAMSIZE";
  const char tempVDD[]   = "TEMPVDD";
  // IDs:
  const char red[]       = "RED";
  const char blue[]      = "BLUE";
  const char green[]     = "GREEN";
  const char all[]       = "ALL";
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
    if(strcmp((char*)item_id, all) == 0) {
      if(strcmp((char*)item_action, on) == 0) {
	IO.ledAllOn();
	return;
      }
      if(strcmp((char*)item_action, off) == 0) {
	IO.ledAllOff();
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
  if(strcmp((char*)item_type, tempVDD) == 0) {
    Analog.commTempVDD();
    return;
  }
  if(strcmp((char*)item_type, ledr) == 0) {
    if(strcmp((char*)item_id, red) == 0) {
      IO.ledReadRed();
      return;
    }
    if(strcmp((char*)item_id, blue) == 0) {
      IO.ledReadBlue();
      return;
    }
    if(strcmp((char*)item_id, green) == 0) {
      IO.ledReadGreen();
      return;
    }
    if(strcmp((char*)item_id, all) == 0) {
      IO.ledReadAll();
      return;
    }
  }
}


EFM32ZGUSBClass ZGUSB;

