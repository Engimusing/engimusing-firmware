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
#include "QRE1113.h"
#include "tickHandler.h"
#include "switches.h"
#include <Arduino.h>

extern LEUARTClass Serial;
extern boardIO IO;
TimersLP Timer;

// Types:
static const char sensor[]   = "SENSOR";
// IDs:
static const char green[]    = "QRE";
// ACTIONs:
static const char stat[]     = "STATUS";

static const char *onoff[]   = {"ISON","ISOFF"};
static const char modu[]     = "{\"MODULE\":\"";
static const char mid[]      = "\":\"";
static const char com[]      = "\",\"";
static const char tail[]     = "\"}\r\n";

tickHandler lightsens;

static uint8_t lightsens_module[ITEM_TOKEN_LENGTH];
static uint32_t qpin = 0;

switchesClass sw_sen("SENSOR", LightSensorISR, 2, SW_MOMENTARY);

void LightSensorISR(void)
{
  sw_sen.sw_int++;
}

void QRE1113Class::begin(uint8_t pin, const char* s)
{
  uint8_t s1[] = "QRE1113";
  COMM.add_module(s1, decode_cmd);
  Serial.printf("{\"MODULE\":\"QRE1113\"}\r\n");
  addModule(s);

  COMM.add_tick_handler(handle_tick);

  qpin = pin;
  sw_sen.begin(pin, lightsens_module);
}

void QRE1113Class::addModule(const char* s)
{
  COMM.add_module((uint8_t*)s, decode_cmd);
  strcpy((char*)lightsens_module, (char*)s);
}

void QRE1113Class::handle_tick(void)
{
  sw_sen.pub_switch(lightsens_module);
}

void QRE1113Class::decode_cmd(uint8_t* item_module,
			      uint8_t* item_type,
			      uint8_t* item_id,
			      uint8_t* item_action,
			      uint8_t* item_payload)
{
  uint8_t debug = 0;
  if(debug) {Serial.printf("item_module = %s, item_type = %s, item_id = %s, item_action = %s, item_payload = %s\r\n",
			   item_module,item_type,item_id,item_action,item_payload);}

  if(strcmp((char*)item_type, sensor) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      Serial.printf("%s%s%sSENSOR%s%s%s",modu,item_module,com,mid,onoff[digitalRead(qpin)],tail);
      return;
    }
  }
}

