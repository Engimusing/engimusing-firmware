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

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include "Arduino.h"

#define SSR_ON_1_PIN   12  // PD7
#define SSR_ON_2_PIN    4  // PC14
#define SSR_ON_3_PIN    5  // PC15
#define SSR_ON_4_PIN    6  // PE12
#define SSR_ON_5_PIN    7  // PE13
#define SSR_ON_6_PIN   14  // PA0
#define SSR_ON_7_PIN    2  // PB7
#define SSR_ON_8_PIN    3  // PB8


void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(SSR_ON_1_PIN, OUTPUT);
  digitalWrite(SSR_ON_1_PIN, HIGH);

  pinMode(SSR_ON_2_PIN, OUTPUT);
  digitalWrite(SSR_ON_2_PIN, HIGH);

  pinMode(SSR_ON_3_PIN, OUTPUT);
  digitalWrite(SSR_ON_3_PIN, HIGH);

  pinMode(SSR_ON_4_PIN, OUTPUT);
  digitalWrite(SSR_ON_4_PIN, HIGH);

  pinMode(SSR_ON_5_PIN, OUTPUT);
  digitalWrite(SSR_ON_5_PIN, HIGH);

  pinMode(SSR_ON_6_PIN, OUTPUT);
  digitalWrite(SSR_ON_6_PIN, HIGH);

  pinMode(SSR_ON_7_PIN, OUTPUT);
  digitalWrite(SSR_ON_7_PIN, HIGH);

  pinMode(SSR_ON_8_PIN, OUTPUT);
  digitalWrite(SSR_ON_8_PIN, HIGH);

  delay(1000);

  Serial.println("Simple AQH3213 OCTAL RS232x2 SSR Relay Example 0");
  Serial1.println("Simple AQH3213 OCTAL RS232x2 SSR Relay Example 1");
}

void loop()
{
  static int on = LOW;
  static int rly = 0;

  digitalWrite(LED_BUILTIN, on);

  switch (rly++)
  {
    case 0:
      digitalWrite(SSR_ON_1_PIN, on);
      break;
    case 1:
      digitalWrite(SSR_ON_1_PIN, on);
      break;
    case 2:
      digitalWrite(SSR_ON_2_PIN, on);
      break;
    case 3:
      digitalWrite(SSR_ON_2_PIN, on);
      break;
    case 4:
      digitalWrite(SSR_ON_3_PIN, on);
      break;
    case 5:
      digitalWrite(SSR_ON_3_PIN, on);
      break;
    case 6:
      digitalWrite(SSR_ON_4_PIN, on);
      break;
    case 7:
      digitalWrite(SSR_ON_4_PIN, on);
      break;
    case 8:
      digitalWrite(SSR_ON_5_PIN, on);
      break;
    case 9:
      digitalWrite(SSR_ON_5_PIN, on);
      break;
    case 10:
      digitalWrite(SSR_ON_6_PIN, on);
      break;
    case 11:
      digitalWrite(SSR_ON_6_PIN, on);
      break;
    case 12:
      digitalWrite(SSR_ON_7_PIN, on);
      break;
    case 13:
      digitalWrite(SSR_ON_7_PIN, on);
      break;
    case 14:
      digitalWrite(SSR_ON_8_PIN, on);
      break;
    case 15:
    default:
      digitalWrite(SSR_ON_8_PIN, on);
      rly = 0;
      break;
  }

  delay(500);
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
}


