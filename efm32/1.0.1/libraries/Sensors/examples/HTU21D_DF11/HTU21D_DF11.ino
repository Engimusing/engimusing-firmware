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
#include <HTU21DDevice.h>

HTU21DDevice htu21d;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple HTU21D example 0");
  digitalWrite(LED_BUILTIN, LOW);
  htu21d.begin(Wire0, 10);
}

void loop() {
  static int on = HIGH;

  digitalWrite(LED_BUILTIN, on);   // turn the LED on (HIGH is the voltage level)
  float hum = htu21d.calcHumidity(htu21d.readHumidity());
  float temp = htu21d.calcTemp(htu21d.readTemp());
  delay(1000);                       // wait for a second
  Serial.print("temperature = ");
  Serial.print(temp);
  Serial.print("   humidity = ");
  Serial.println(hum);

  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
}

