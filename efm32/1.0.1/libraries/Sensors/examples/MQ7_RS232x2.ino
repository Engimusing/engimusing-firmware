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

#if !defined(EFM32TG110)
#error Incorrect Board Selected! Please select Engimusing EFM32TG110 from the Tools->Board: menu.
#endif
 
#include "Arduino.h"
#include <MQ7Device.h>

MQ7Device Mq7;

void setup() {
  int PWM_CTL = 7;
  int SENSOR = A0;

  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple MQ7 Gas Sensor example 0");
  Serial1.println("Simple MQ7 Gas Sensor example 1");
  digitalWrite(LED_BUILTIN, LOW);
  Mq7.begin(PWM_CTL, SENSOR);
}

void loop() {
  static int on = HIGH;
  Device::ValueStruct output;

  digitalWrite(LED_BUILTIN, on);   // turn the LED on (HIGH is the voltage level)

  Mq7.update();

  output = Mq7.readValue(0);
  int level = output.value.integer;

  delay(1000);                       // wait for a second
  Serial.print("   CO level = ");
  Serial.println(level);

  Serial1.print("   CO level = ");
  Serial1.println(level);

  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
}

