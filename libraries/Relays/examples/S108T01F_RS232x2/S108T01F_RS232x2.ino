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

  Example for the S108T01F RS232x2 Relay board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include "Arduino.h"

#define SSR_ON_PIN  6


void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(SSR_ON_PIN, OUTPUT);
  digitalWrite(SSR_ON_PIN, HIGH);

  delay(1000);

  Serial.println("Simple S108T01F RS232x2 SSR Relay Example 0");
  Serial1.println("Simple S108T01F RS232x2 SSR Relay Example 1");
}

void loop()
{
  static int on = HIGH;

  digitalWrite(LED_BUILTIN, on);

  digitalWrite(SSR_ON_PIN, on);

  delay(250);
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
 }

 
