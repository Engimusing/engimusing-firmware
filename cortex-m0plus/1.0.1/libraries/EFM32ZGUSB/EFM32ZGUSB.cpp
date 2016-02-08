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

#include "EFM32XML.h"
#include "EFM32ZGUSB.h"
#include <Arduino.h>


extern LEUARTClass Serial;
extern boardIO IO;
extern AnalogLP Analog;

void EFM32ZGUSBClass::begin(void)
{
  uint8_t s1[] = "EFMUSB";

  XML.add_module(s1, decode_cmd);
  Serial.printf("efm32zgusb setup\r\n");
}

EFM32ZGUSBClass::EFM32ZGUSBClass()
{
}

/*
  <DEV cpuid="24353a02522fa331" addr="01">
  </DEV>

  <DEV cpuid="24353a02522fa331">
  <TYPE>LED</TYPE>
  <ID>val</ID>  <!-- RED/BLUE/GREEN -->
  <ACT>val</ACT>  <!-- ON/OFF -->
  </DEV>

  <DEV cpuid="24353a02522fa331" addr="01">
  <TYPE>LED</TYPE>
  <ID>val</ID>  <!-- RED/BLUE/GREEN -->
  <ACT>val</ACT>  <!-- ON/OFF -->
  </DEV>

  <DEV addr="01">
  <TYPE>val</TYPE>  <!-- TEMP -->
  <ACT>val</ACT>    <!-- GETC/GETF -->
  </DEV>

  <DEV addr="01">
  <TYPE>val</TYPE>  <!-- VDD  -->
  <ACT>val</ACT>  <!-- GET  -->
  </DEV>

  <DEV addr="01">
  <TYPE>val</TYPE>  <!-- BRDINFO : CHIPID, CLKFREQ, CPU, FLASHSIZE, LEDSOFF, SRAMSIZE -->
  <ACT>val</ACT>  <!-- GET  -->
  </DEV>
*/

void EFM32ZGUSBClass::decode_cmd(uint8_t* item_type, 
				 uint8_t* item_id, 
				 uint8_t* item_action, 
				 uint8_t* item_p1,
				 uint8_t* item_p2)
{
  // Types:
  const char led[]     = "LED";
  const char cputemp[] = "CPUTEMP";
  const char cpuvdd[]  = "CPUVDD";
  const char brdinfo[] = "BRDINFO";
  // IDs:
  const char red[]     = "RED";
  const char blue[]    = "BLUE";
  const char green[]   = "GREEN";
  // ACTIONs:
  const char on[]      = "ON";
  const char off[]     = "OFF";


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
    Analog.xmlTemperature();
    return;
  }
  if(strcmp((char*)item_type, cpuvdd) == 0) {
    Analog.xmlVDD();
    return;
  }
  if(strcmp((char*)item_type, brdinfo) == 0) {
    IO.printBoardParameters();
    return;
  }
}


EFM32ZGUSBClass ZGUSB;


