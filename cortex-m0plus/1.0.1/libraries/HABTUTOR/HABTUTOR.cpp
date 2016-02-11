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
#include <Arduino.h>


extern LEUARTClass Serial;
extern boardIO IO;
extern AnalogLP Analog;
TimersLP Timer;


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

  Serial.printf("{\"MODULE\":\"HABTUTOR\"}\r\n");
  COMM.add_module(s1, decode_cmd);
  Serial.printf("HAB Tutorial  setup\r\n");
  pinMode( 7, OUTPUT);     // Switch pull up
  digitalWrite( 7, HIGH);
  pinMode(10, INPUT);      // Red Switch
  pinMode( 2, INPUT);      // Black Switch
  pinMode( 4, INPUT);      // Reed Switch
  pinMode( 5, OUTPUT);     // LED
  digitalWrite( 5, HIGH);
  pinMode( 8, INPUT_PULLUP);      // Reflective Object Sensor
  pinMode( 6, OUTPUT);     // Buzzer
}

HABTUTORClass::HABTUTORClass()
{
}


void HABTUTORClass::decode_cmd(uint8_t* item_type,
			       uint8_t* item_id,
			       uint8_t* item_action,
			       uint8_t* item_p1,
			       uint8_t* item_p2)
{
  // Types:
  const char switches[] = "SWITCH";
  const char sensor[]   = "SENSOR";
  const char led[]      = "LED";
  const char buzzer[]   = "BUZZER";
  const char pot[]      = "POT";
  // IDs:
  const char red[]      = "RED";
  const char black[]    = "BLACK";
  const char reed[]     = "REED";
  const char green[]    = "QRE";
  // ACTIONs:
  const char on[]       = "ON";
  const char off[]      = "OFF";

  uint32_t sw = 0;

  if(strcmp((char*)item_type, led) == 0) {
    if(strcmp((char*)item_action, on) == 0) {
      Serial.printf("{\"MODULE\":\"HABTUTOR\",\"LED\":\"ON\"}\r\n");
      digitalWrite(5, HIGH);
      return;
    }
    if(strcmp((char*)item_action, off) == 0) {
      Serial.printf("{\"MODULE\":\"HABTUTOR\",\"LED\":\"OFF\"}\r\n");
      digitalWrite(5, LOW);
      return;
    }
  }
  if(strcmp((char*)item_type, switches) == 0) {
    if(strcmp((char*)item_id, red) == 0) {
      sw = digitalRead(10);
      if(sw) {
	Serial.printf("{\"MODULE\":\"HABTUTOR\",\"REDSW\":\"HIGH\"}\r\n");
      } else {
	Serial.printf("{\"MODULE\":\"HABTUTOR\",\"REDSW\":\"LOW\"}\r\n");
      }
      return;
    }
    if(strcmp((char*)item_id, black) == 0) {
      sw = digitalRead(2);
      if(sw) {
	Serial.printf("{\"MODULE\":\"HABTUTOR\",\"BLKSW\":\"HIGH\"}\r\n");
      } else {
	Serial.printf("{\"MODULE\":\"HABTUTOR\",\"BLKSW\":\"LOW\"}\r\n");
      }
      return;
    }
  }
  if(strcmp((char*)item_type, reed) == 0) {
    sw = digitalRead(4);
    if(sw) {
      Serial.printf("{\"MODULE\":\"HABTUTOR\",\"REEDSW\":\"HIGH\"}\r\n");
    } else {
      Serial.printf("{\"MODULE\":\"HABTUTOR\",\"REEDSW\":\"LOW\"}\r\n");
    }
    return;
  }
  if(strcmp((char*)item_type, sensor) == 0) {
    sw = digitalRead(8);
    if(sw) {
      Serial.printf("{\"MODULE\":\"HABTUTOR\",\"SENSOR\":\"HIGH\"}\r\n");
    } else {
      Serial.printf("{\"MODULE\":\"HABTUTOR\",\"SENSOR\":\"LOW\"}\r\n");
    }
    return;
  }
  if(strcmp((char*)item_type, pot) == 0) {
    uint32_t r = Analog.analogReadVDDsample();
    Analog.analogReference(INTERNALVDD);
    Analog.analogReadResolution(RES_12BITS);
    uint32_t v = Analog.analogReadPin(3);
    uint32_t mV = ((v * r)/4096);
    Serial.printf("{\"MODULE\":\"HABTUTOR\",\"POT\":\"%d.%dV\"}\r\n",mV/1000,mV%1000);
  }
  if(strcmp((char*)item_type, buzzer) == 0) {
    uint32_t freq = 1000;
    uint32_t f = atoi((char*)item_p1);
    if((f > 0) && (f < 20000)) {
      freq = f;
    }
    uint32_t duration = 0;
    uint32_t d = atoi((char*)item_p2);
    if(d > 0) {
      duration = d;
    }
    if(strcmp((char*)item_action, on) == 0) {
      Timer.noTone(6);
      Timer.tone(6, freq, duration);
      return;
    }
    if(strcmp((char*)item_action, off) == 0) {
      Timer.noTone(6);
      return;
    }
  }
}


HABTUTORClass HABT;


