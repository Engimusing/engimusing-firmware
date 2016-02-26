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
#include "tickHandler.h"
#include <Arduino.h>


extern LEUARTClass Serial;
extern boardIO IO;
extern AnalogLP Analog;

// Types:
static const char led[]       = "LED";
static const char ledr[]      = "LEDR";
static const char cputemp[]   = "CPUTEMP";
static const char cpuvdd[]    = "CPUVDD";
static const char brdinfo[]   = "BRDINFO";
static const char tempVDD[]   = "TEMPVDD";
// IDs:
static const char red[]       = "RED";
static const char blue[]      = "BLUE";
static const char green[]     = "GREEN";
static const char all[]       = "ALL";
// ACTIONs:
static const char on[]        = "ON";
static const char off[]       = "OFF";
static const char stat[]      = "STATUS";
static const char pfrq[]      = "INTERVAL";
static const char pub[]       = "PUB";
static const char cel[]       = "CEL";
static const char far[]       = "FAR";

static const char *onoff[]   = {"ISON","ISOFF"};
static const char modu[]     = "{\"MODULE\":\"EFMUSB\",\"";
static const char mid[]      = "\":\"";
static const char com[]      = "\",\"";
static const char tail[]     = "\"}\r\n";
static const char topu[]     = "{\"TOP\":\"";
static const char midu[]     = "\",\"PLD\":\"";

void EFM32ZGUSBClass::begin(void)
{
  uint8_t s1[] = "EFMUSB";

  COMM.add_module(s1, decode_cmd);
  COMM.add_tick_handler(handle_tick);
  IO.commChipID();
  Serial.printf("{\"MODULE\":\"EFMUSB\"}\r\n");
}

void EFM32ZGUSBClass::addModule(const char* s)
{
  COMM.add_module((uint8_t*)s, decode_cmd);
}


EFM32ZGUSBClass::EFM32ZGUSBClass()
{
}


tickHandler tempcpub;
tickHandler tempfpub;
tickHandler vddpub;

static uint8_t tempc_module[ITEM_TOKEN_LENGTH];
static uint8_t tempf_module[ITEM_TOKEN_LENGTH];
static uint8_t vdd_module[ITEM_TOKEN_LENGTH];

void EFM32ZGUSBClass::handle_tick(void)
{
  if(tempcpub.serviceTick()) {pub_temp_cel(tempc_module);}
  if(tempfpub.serviceTick()) {pub_temp_far(tempf_module);}
  if(vddpub.serviceTick())   {pub_cpu_vdd(vdd_module);}
}

void EFM32ZGUSBClass::sch_temp_cel(uint32_t interval, const char* item_module)
{
  strcpy((char*)tempc_module, (char*)item_module);
  tempcpub.setInterval(interval);
}

void EFM32ZGUSBClass::sch_temp_far(uint32_t interval, const char* item_module)
{
  strcpy((char*)tempf_module, (char*)item_module);
  tempfpub.setInterval(interval);
}

void EFM32ZGUSBClass::sch_cpu_vdd(uint32_t interval, const char* item_module)
{
  strcpy((char*)vdd_module, (char*)item_module);
  vddpub.setInterval(interval);
}

void EFM32ZGUSBClass::pub_temp_cel(uint8_t* item_module)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("%s%s/CPUTEMP/CEL/STATE%s%d.%dC%s",topu, item_module, midu, tempval.wholeC, tempval.fracC, tail);
}

void EFM32ZGUSBClass::pub_temp_far(uint8_t* item_module)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("%s%s/CPUTEMP/FAR/STATE%s%d.%dF%s",topu, item_module, midu, tempval.wholeF, tempval.fracF, tail);
}

void EFM32ZGUSBClass::pub_cpu_vdd(uint8_t* item_module)
{
  uPvdd vddval = Analog.analogReadVDD();
  Serial.printf("%s%s/CPUVDD/1/STATE%s%d.%dV%s",topu, item_module, midu, vddval.wholeVDD, vddval.fracVDD, tail);
}


void EFM32ZGUSBClass::decode_cmd(uint8_t* item_module,
				 uint8_t* item_type, 
				 uint8_t* item_id, 
				 uint8_t* item_action, 
				 uint8_t* item_payload)
{
  if(strcmp((char*)item_type, led) == 0) {
    if(strcmp((char*)item_id, red) == 0) {
      if(strcmp((char*)item_action, on) == 0) {
	digitalWrite(RED_LED, LOW);
	return;
      }
      if(strcmp((char*)item_action, off) == 0) {
	digitalWrite(RED_LED, HIGH);
	return;
      }
      if(strcmp((char*)item_action, stat) == 0) {
	Serial.printf("%sREDLED%s%s%s",modu,mid,onoff[digitalRead(RED_LED)],tail);
	return;
      }
    }
    if(strcmp((char*)item_id, blue) == 0) {
      if(strcmp((char*)item_action, on) == 0) {
	digitalWrite(BLUE_LED, LOW);
	return;
      }
      if(strcmp((char*)item_action, off) == 0) {
	digitalWrite(BLUE_LED, HIGH);
	return;
      }
      if(strcmp((char*)item_action, stat) == 0) {
	Serial.printf("%sBLUELED%s%s%s",modu,mid,onoff[digitalRead(BLUE_LED)],tail);
	return;
      }
    }
    if(strcmp((char*)item_id, green) == 0) {
      if(strcmp((char*)item_action, on) == 0) {
	digitalWrite(GREEN_LED, LOW);
	return;
      }
      if(strcmp((char*)item_action, off) == 0) {
	digitalWrite(GREEN_LED, HIGH);
	return;
      }
      if(strcmp((char*)item_action, stat) == 0) {
	Serial.printf("%sGREENLED%s%s%s",modu,mid,onoff[digitalRead(GREEN_LED)],tail);
	return;
      }
    }
    if(strcmp((char*)item_id, all) == 0) {
      if(strcmp((char*)item_action, on) == 0) {
	digitalWrite(RED_LED, LOW);
	digitalWrite(BLUE_LED, LOW);
	digitalWrite(GREEN_LED, LOW);
	return;
      }
      if(strcmp((char*)item_action, off) == 0) {
	digitalWrite(RED_LED, HIGH);
	digitalWrite(BLUE_LED, HIGH);
	digitalWrite(GREEN_LED, HIGH);
	return;
      }
      if(strcmp((char*)item_action, stat) == 0) {
	Serial.printf("%sREDLED%s%s%sBLUELED%s%s%sGREENLED%s%s%s",
		      modu,mid,onoff[digitalRead(RED_LED)],com,
		      mid,onoff[digitalRead(BLUE_LED)],com,
		      mid,onoff[digitalRead(GREEN_LED)],tail);
	return;
      }
    }
  }
  if(strcmp((char*)item_type, cputemp) == 0) {
    if(strcmp((char*)item_id, cel) == 0) {
      if(strcmp((char*)item_action, stat) == 0) {
	temperature tempval = Analog.analogReadTemp();
	Serial.printf("%sCPUTEMPC%s%d.%dC%s", modu, mid, tempval.wholeC, tempval.fracC, tail);
	return;
      }
      if(strcmp((char*)item_action, pfrq) == 0) {
	strcpy((char*)tempc_module, (char*)item_module);
	tempcpub.setInterval(atoi((char*)item_payload));
	return;
      }
    }
    if(strcmp((char*)item_id, far) == 0) {
      if(strcmp((char*)item_action, stat) == 0) {
	temperature tempval = Analog.analogReadTemp();
	Serial.printf("%sCPUTEMPF%s%d.%dF%s", modu, mid, tempval.wholeF, tempval.fracF, tail);
	return;
      }
      if(strcmp((char*)item_action, pfrq) == 0) {
	strcpy((char*)tempf_module, (char*)item_module);
	tempfpub.setInterval(atoi((char*)item_payload));
	return;
      }
    }
  }
  if(strcmp((char*)item_type, cpuvdd) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      uPvdd vddval = Analog.analogReadVDD();
      Serial.printf("%supVDD%s%d.%dV%s",modu, mid, vddval.wholeVDD,vddval.fracVDD, tail);
      return;
    }
    if(strcmp((char*)item_action, pfrq) == 0) {
      strcpy((char*)vdd_module, (char*)item_module);
      vddpub.setInterval(atoi((char*)item_payload));
      return;
    }
  }
  if(strcmp((char*)item_type, brdinfo) == 0) {
    IO.printBoardParameters();
    return;
  }
}


EFM32ZGUSBClass ZGUSB;

