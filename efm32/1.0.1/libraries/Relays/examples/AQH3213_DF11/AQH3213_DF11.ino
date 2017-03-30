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

  Example for the AQH3213 DF11 Relay board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include "Arduino.h"

#define SSR_ON_B_PIN    8
#define SSR_ON_A_PIN   10

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(SSR_ON_A_PIN, OUTPUT);
  digitalWrite(SSR_ON_A_PIN, HIGH);

  pinMode(SSR_ON_B_PIN, OUTPUT);
  digitalWrite(SSR_ON_B_PIN, HIGH);

  delay(1000);

  Serial.println("Simple AQH3213 DF11 SSR Relay Example 0");
}

void loop()
{
  static int on = LOW;
  static int rly = 0;

  digitalWrite(LED_BUILTIN, on);

  switch (rly++)
  {
    case 0:
      digitalWrite(SSR_ON_A_PIN, on);
      break;
    case 1:
      digitalWrite(SSR_ON_A_PIN, on);
      break;
    case 2:
      digitalWrite(SSR_ON_B_PIN, on);
      break;
    case 3:
    default:
      digitalWrite(SSR_ON_B_PIN, on);
      rly = 0;
      break;
  }

  delay(500);
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
}


