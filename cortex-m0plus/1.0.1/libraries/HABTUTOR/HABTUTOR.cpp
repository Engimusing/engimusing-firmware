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
#include "HABTUTOR.h"
#include "tickHandler.h"
#include "switches.h"
#include <Arduino.h>

extern LEUARTClass Serial;
extern boardIO IO;
extern AnalogLP Analog;
TimersLP Timer;

// Types:
static const char switches[] = "SWITCH";
static const char sensor[]   = "SENSOR";
static const char led[]      = "LED";
static const char buzzer[]   = "BUZZER";
static const char pot[]      = "POT";
// IDs:
static const char red[]      = "RED";
static const char black[]    = "BLACK";
static const char reed[]     = "REED";
static const char green[]    = "QRE";
// ACTIONs:
static const char on[]       = "ON";
static const char off[]      = "OFF";
static const char stat[]     = "STATUS";
static const char pub[]      = "PUB";
static const char intv[]     = "INTERVAL";
static const char freqy[]    = "FREQ";
static const char dur[]      = "DURATION";

static const char *onoff[]   = {"ISON","ISOFF"};
static const char modu[]     = "{\"MODULE\":\"";
static const char mid[]      = "\":\"";
static const char com[]      = "\",\"";
static const char tail[]     = "\"}\r\n";
static const char topu[]     = "{\"TOP\":\"";
static const char midu[]     = "\",\"PLD\":\"";
static const char rs2on[]    = "CLOSED";
static const char rs2off[]   = "OPEN";

tickHandler redsw;
tickHandler blacksw;
tickHandler reedsw;
tickHandler lightsens;
tickHandler potpub;

static uint8_t redsw_module[ITEM_TOKEN_LENGTH];
static uint8_t blacksw_module[ITEM_TOKEN_LENGTH];
static uint8_t reedsw_module[ITEM_TOKEN_LENGTH];
static uint8_t lightsens_module[ITEM_TOKEN_LENGTH];
static uint8_t pot_module[ITEM_TOKEN_LENGTH];

switchesClass sw_reed(REEDSW_PIN,"REED", ReedSwitchISR);
switchesClass sw_red(REDSW_PIN, "RED", RedSwitchISR);
switchesClass sw_blk(BLKSW_PIN, "BLACK", BlackSwitchISR);
switchesClass sw_sen(LTSENS_PIN, "SENSOR", LightSensorISR);

void ReedSwitchISR(void)
{
  sw_reed.sw_int++;
}

void RedSwitchISR(void)
{
  sw_red.sw_int = 1;
}

void BlackSwitchISR(void)
{
  sw_blk.sw_int = 1;
}

void LightSensorISR(void)
{
  sw_sen.sw_int = 1;
}


// PD7 - Red Switch
// PC0 - QRE Sensor Out
// PC1 - Switch Pullup
// PC4 - Buzzer
// PB7 - Red LED
// PB8 - Reed Switch
// PD6 - ADC Voltage
// PD4 - Black Switch
void HABTUTORClass::begin(void)
{
  uint8_t s1[] = "HABTUTOR";
  COMM.add_module(s1, decode_cmd);
  Serial.printf("{\"MODULE\":\"HABTUTOR\"}\r\n");

  COMM.add_tick_handler(handle_tick);

  pinMode( SWPULL_PIN, OUTPUT);       // Switch pull up
  digitalWrite(SWPULL_PIN, HIGH);

  sw_red.begin();
  sw_blk.begin();
  sw_reed.begin();
  sw_sen.begin();
  pinMode(HABLED_PIN, OUTPUT);       // LED
  pinMode(BUZZER_PIN, OUTPUT);       // Buzzer
}



HABTUTORClass::HABTUTORClass()
{
}

void HABTUTORClass::addModule(const char* s)
{
  COMM.add_module((uint8_t*)s, decode_cmd);
  strcpy((char*)redsw_module, (char*)s);
  strcpy((char*)blacksw_module, (char*)s);
  strcpy((char*)reedsw_module, (char*)s);
  strcpy((char*)lightsens_module, (char*)s);
}

void HABTUTORClass::handle_tick(void)
{
  sw_red.pub_switch(redsw_module);
  sw_blk.pub_switch(blacksw_module);
  sw_reed.pub_switch(reedsw_module);
  sw_sen.pub_switch(lightsens_module);
  if(potpub.serviceTick())    {pub_pot_voltage(pot_module);}
}

void HABTUTORClass::sch_pot_voltage(uint32_t interval, const char* item_module)
{
  Serial.printf("item_module = %s\r\n",item_module);
  strcpy((char*)pot_module, (char*)item_module);
  potpub.setInterval(interval);
}


void HABTUTORClass::pub_pot_voltage(uint8_t* item_module)
{
  uint32_t mV = read_pot();
  Serial.printf("%s%s/POT/1/STATE%s%d.%dV%s",topu, item_module, midu, mV/1000, mV%1000, tail);
}

void HABTUTORClass::decode_cmd(uint8_t* item_module,
			       uint8_t* item_type,
			       uint8_t* item_id,
			       uint8_t* item_action,
			       uint8_t* item_payload)
{
  uint8_t debug = 0;
  if(debug) {Serial.printf("item_module = %s, item_type = %s, item_id = %s, item_action = %s, item_payload = %s\r\n",
			   item_module,item_type,item_id,item_action,item_payload);}

  if(strcmp((char*)item_type, led) == 0) {
    if(strcmp((char*)item_action, on) == 0) {
      digitalWrite(HABLED_PIN, HIGH);
      return;
    }
    if(strcmp((char*)item_action, off) == 0) {
      digitalWrite(HABLED_PIN, LOW);
      return;
    }
    if(strcmp((char*)item_action, stat) == 0) {
      uint8_t l = (~digitalRead(HABLED_PIN) & 0x01);
      Serial.printf("%s%s%sLED%s%s%s",modu,item_module,com,mid,onoff[l],tail);
      return;
    }
  }
  if(strcmp((char*)item_type, switches) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      if(strcmp((char*)item_id, red) == 0) {
	Serial.printf("%s%s%sREDSW%s%s%s",modu,item_module,com,mid,onoff[digitalRead(REDSW_PIN)],tail);
	return;
      }
      if(strcmp((char*)item_id, black) == 0) {
	Serial.printf("%s%s%sBLKSW%s%s%s",modu,item_module,com,mid,onoff[digitalRead(BLKSW_PIN)],tail);
	return;
      }
      if(strcmp((char*)item_id, reed) == 0) {
	Serial.printf("%s%s%sREEDSW%s%s%s",modu,item_module,com,mid,onoff[digitalRead(REEDSW_PIN)],tail);
	return;
      }
    }
  }
  if(strcmp((char*)item_type, sensor) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      Serial.printf("%s%s%sSENSOR%s%s%s",modu,item_module,com,mid,onoff[digitalRead(LTSENS_PIN)],tail);
      return;
    }
  }
  if(strcmp((char*)item_type, pot) == 0) {
    if(strcmp((char*)item_action, stat) == 0) {
      uint32_t mV = read_pot();
      Serial.printf("%s%s%sPOT%s%d.%dV%s",modu,item_module,com,mid,mV/1000,mV%1000,tail);
    }
    if(strcmp((char*)item_action, intv) == 0) {
      strcpy((char*)pot_module, (char*)item_module);
      potpub.setInterval(atoi((char*)item_payload));
      return;
    }
  }
  if(strcmp((char*)item_type, buzzer) == 0) {
    static uint32_t freq = 1000;
    static uint32_t duration = 0;
    static uint32_t bzstate = 0;

    if(strcmp((char*)item_action, on) == 0) {
      Timer.noTone(6);
      Timer.tone(6, freq, duration);
      bzstate = 1;
      return;
    }
    if(strcmp((char*)item_action, off) == 0) {
      Timer.noTone(6);
      bzstate = 0;
      return;
    }
    if(strcmp((char*)item_action, stat) == 0) {
      Serial.printf("%s%s%sBUZZER%s%s\",\"FREQ\":\"%d\",\"DURATION\":\"%d%s",
		    modu,item_module,com,mid,onoff[bzstate],freq,duration,tail);
      return;
    }
    if(strcmp((char*)item_action, freqy) == 0) {
      uint32_t f = atoi((char*)item_payload);
      if((f >= 0) && (f < 20000)) {
	freq = f;
      }
      return;
    }
    if(strcmp((char*)item_action, dur) == 0) {
      uint32_t d = atoi((char*)item_payload);
      if(d >= 0) {
	duration = d;
      }
      return;
    }
  }
}

uint32_t HABTUTORClass::read_pot(void)
{
  uint32_t r = Analog.analogReadVDDsample();
  Analog.analogReference(INTERNALVDD);
  Analog.analogReadResolution(RES_12BITS);
  uint32_t v = Analog.analogReadPin(POT_PIN);
  return ((v * r)/4096);
}


HABTUTORClass HABT;


