/*
  Copyright (c) 2017 Engimusing LLC.  All right reserved.

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

#include "Arduino.h"
#include <Wire.h>
#include <TMP102Device.h>

TMP102Device tmp102;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple TMP102 example 0");
  Serial1.println("Simple TMP102 example 1");
  digitalWrite(LED_BUILTIN, LOW);
  tmp102.begin(Wire0, -1, true);
}

void loop() {
  static int on = HIGH;

  digitalWrite(LED_BUILTIN, on);   // turn the LED on (HIGH is the voltage level)
  float temp = tmp102.temperature();
  delay(1000);                       // wait for a second
  Serial.print("temperature = ");
  Serial.println(temp);

  Serial1.print("temperature = ");
  Serial1.println(temp);

  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
}

