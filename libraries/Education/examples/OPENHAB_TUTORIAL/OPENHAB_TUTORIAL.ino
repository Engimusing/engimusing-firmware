/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.

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

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu. Or adjust the pins below to work with another DF11 engiumsing board.
#endif

#include "Arduino.h"
extern AnalogLP  Analog;

#define SW1_PIN       2
#define POT_PIN       3
#define REEDSW_PIN    4
#define HABLED_PIN    5
#define BUZZER_PIN    6
#define SWPULL_PIN    7
#define LTSENS_PIN    8
#define SW2_PIN      10

void setup()
{
  Serial.begin(115200);

  pinMode(SWPULL_PIN, OUTPUT);       // Switch pull up
  digitalWrite(SWPULL_PIN, HIGH);

  pinMode(HABLED_PIN, OUTPUT);       // Turn off HAB Tutorial Red LED
  digitalWrite(HABLED_PIN, LOW);

  pinMode(BUZZER_PIN, OUTPUT);       // Buzzer output low
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(SW1_PIN, INPUT);           // Switch 1 input

  pinMode(SW2_PIN, INPUT);           // Switch 2 input

  pinMode(LTSENS_PIN, INPUT_PULLUP);        // QRE sensor input

  pinMode(REEDSW_PIN, INPUT);        // reed switch sensor input

  delay(1000);
  Serial.println("OpenHAB Tutorial Example");
}

void loop()
{
  static int on = HIGH;

  digitalWrite(HABLED_PIN, on);

  if (digitalRead(SW1_PIN) == 0) {
    Serial.println("SW1 on");
  }

  if (digitalRead(SW2_PIN) == 0) {
    Serial.println("SW2 on");
  }

  if (digitalRead(REEDSW_PIN) == 0) {
    Serial.println("REED_SW on");
  }

  if (digitalRead(LTSENS_PIN) == 0) {
    Serial.println("Light Sensor on");
  }

  if (on) {
    static int buzz = 0;

    if (buzz++ >= 5) {
      tone(BUZZER_PIN, 1000, 100);
      buzz = 0;
    }

    uint32_t r = Analog.analogReadVDDsample();
    Analog.analogReference(INTERNALVDD);
    Analog.analogReadResolution(RES_12BITS);
    uint32_t v = Analog.analogReadPin(POT_PIN);
    uint32_t mV =  ((v * r) / 4096);
    Serial.print("POT Voltage ADC = ");
    Serial.print((float)mV / 1000.0f);
    Serial.println();
  }
  delay(1000);
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
}



