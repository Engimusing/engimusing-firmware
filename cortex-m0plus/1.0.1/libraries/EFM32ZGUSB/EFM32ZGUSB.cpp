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
const char stat[]      = "STAT";
const char pub[]       = "PUB";
const char cel[]       = "CEL";
const char far[]       = "FAR";

const char *onoff[]   = {"ISON","ISOFF"};
const char modu[]     = "{\"MODULE\":\"EFMUSB\",\"";
const char mid[]      = "\":\"";
const char com[]      = "\",\"";
const char tail[]     = "\"}\r\n";
const char topu[]     = "{\"TOP\":\"";
const char midu[]     = "\",\"PLD\":\"";

void EFM32ZGUSBClass::begin(void)
{
  uint8_t s1[] = "EFMUSB";
  uint8_t s2[] = "home/efmusb";

  COMM.add_module(s1, decode_cmd);
  COMM.add_module(s2, decode_cmd);
  COMM.add_tick_handler(handle_tick);
  IO.commChipID();
  Serial.printf("{\"MODULE\":\"EFMUSB\"}\r\n");
}

EFM32ZGUSBClass::EFM32ZGUSBClass()
{
}

void EFM32ZGUSBClass::handle_tick(void)
{
  static uint32_t clk = 0;

  clk++;

  //  if((clk % 10) == 0)  Serial.printf("@\n\r");
}

void EFM32ZGUSBClass::pub_red_led(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  Serial.printf("%s%s/%s/%s/STATE%s%s%s",topu, item_module, item_type, item_id,  midu, onoff[digitalRead(RED_LED)], tail);
}

void EFM32ZGUSBClass::pub_green_led(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  Serial.printf("%s%s/%s/%s/STATE%s%s%s",topu, item_module, item_type, item_id,  midu, onoff[digitalRead(GREEN_LED)], tail);
}

void EFM32ZGUSBClass::pub_blue_led(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  Serial.printf("%s%s/%s/%s/STATE%s%s%s",topu, item_module, item_type, item_id,  midu, onoff[digitalRead(BLUE_LED)], tail);
}

void EFM32ZGUSBClass::pub_temp_cel(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("%s%s/%s/%s/STATE%s%d.%dC%s",topu, item_module, item_type, item_id,  midu, tempval.wholeC, tempval.fracC, tail);
}

void EFM32ZGUSBClass::pub_temp_far(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("%s%s/%s/%s/STATE%s%d.%dF%s",topu, item_module, item_type, item_id,  midu, tempval.wholeF, tempval.fracF, tail);
}

void EFM32ZGUSBClass::pub_cpu_vdd(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  uPvdd vddval = Analog.analogReadVDD();
  Serial.printf("%s%s/%s/%s/STATE%s%d.%dV%s",topu, item_module, item_type, item_id,  midu, vddval.wholeVDD, vddval.fracVDD, tail);
}

void EFM32ZGUSBClass::pub_board_name(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  Serial.printf("%s%s/%s/%s/STATE%s%s%s",topu, item_module, item_type, item_id,  midu, "EFMZGUSB", tail);
}

void EFM32ZGUSBClass::pub_bootloader_version(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  Serial.printf("%s%s/%s/%s/STATE%s%s%s",topu, item_module, item_type, item_id,  midu, IO.getBootloaderVersion(), tail);
}

void EFM32ZGUSBClass::pub_chip_id(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  Serial.printf("%s%s/%s/%s/STATE%s%s%s",topu, item_module, item_type, item_id,  midu, IO.getChipID(), tail);
}

void EFM32ZGUSBClass::pub_cpu_type(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  Serial.printf("%s%s/%s/%s/STATE%s%s%s",topu, item_module, item_type, item_id,  midu, IO.getCPUtype(), tail);
}

void EFM32ZGUSBClass::pub_flash_size(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  Serial.printf("%s%s/%s/%s/STATE%s%s%s",topu, item_module, item_type, item_id,  midu, IO.getFlashSize(), tail);
}

void EFM32ZGUSBClass::pub_sram_size(uint8_t* item_module, uint8_t* item_type, uint8_t* item_id)
{
  Serial.printf("%s%s/%s/%s/STATE%s%s%s",topu, item_module, item_type, item_id,  midu, IO.getSRAMsize(), tail);
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
	IO.ledRedOff();
	return;
      }
      if(strcmp((char*)item_action, stat) == 0) {
	Serial.printf("%sREDLED%s%s%s",modu,mid,onoff[digitalRead(RED_LED)],tail);
	return;
      }
      if(strcmp((char*)item_action, pub) == 0) {
	pub_red_led(item_module, item_type, item_id);
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
      if(strcmp((char*)item_action, pub) == 0) {
	pub_blue_led(item_module, item_type, item_id);
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
      if(strcmp((char*)item_action, pub) == 0) {
	pub_green_led(item_module, item_type, item_id);
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
      if(strcmp((char*)item_action, pub) == 0) {
	pub_temp_cel(item_module, item_type, item_id);
	return;
      }
    }
    if(strcmp((char*)item_id, far) == 0) {
      if(strcmp((char*)item_action, stat) == 0) {
	temperature tempval = Analog.analogReadTemp();
	Serial.printf("%sCPUTEMPF%s%d.%dF%s", modu, mid, tempval.wholeF, tempval.fracF, tail);
	return;
      }
      if(strcmp((char*)item_action, pub) == 0) {
	pub_temp_far(item_module, item_type, item_id);
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
    if(strcmp((char*)item_action, pub) == 0) {
      pub_cpu_vdd(item_module, item_type, item_id);
      return;
    }
  }
  if(strcmp((char*)item_type, brdinfo) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      IO.printBoardParameters();
      return;
    }
  }
  if(strcmp((char*)item_type, brdname) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      Serial.printf("%sBRDNAME%sEFMZGUSB%s",modu, mid, tail);
      return;
    }
    if(strcmp((char*)item_action, pub) == 0) {
      pub_board_name(item_module, item_type, item_id);
      return;
    }
  }
  if(strcmp((char*)item_type, blver) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      Serial.printf("%s",modu);
      IO.commBootloaderVersion();
      return;
    }
    if(strcmp((char*)item_action, pub) == 0) {
      pub_bootloader_version(item_module, item_type, item_id);
      return;
    }
  }
  if(strcmp((char*)item_type, chipid) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      Serial.printf("%sCHIPID%s%s%s",modu, mid, IO.getChipID(), tail);
      return;
    }
    if(strcmp((char*)item_action, pub) == 0) {
      pub_chip_id(item_module, item_type, item_id);
      return;
    }
  }
  if(strcmp((char*)item_type, cputype) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      Serial.printf("%s",modu);
      IO.commCPUtype();
      return;
    }
    if(strcmp((char*)item_action, pub) == 0) {
      pub_cpu_type(item_module, item_type, item_id);
      return;
    }
  }
  if(strcmp((char*)item_type, flashsize) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      Serial.printf("%s",modu);
      IO.commFlashSize();
      return;
    }
    if(strcmp((char*)item_action, pub) == 0) {
      pub_flash_size(item_module, item_type, item_id);
      return;
    }
  }
  if(strcmp((char*)item_type, sramsize) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      Serial.printf("%s",modu);
      IO.commSRAMsize();
      return;
    }
    if(strcmp((char*)item_action, pub) == 0) {
      pub_sram_size(item_module, item_type, item_id);
      return;
    }
  }
}


EFM32ZGUSBClass ZGUSB;

