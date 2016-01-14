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

#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test03 - pulseIn() Send pulses";
extern TimersLP Timers;

void test03_test(void)
{
  pinMode(2, INPUT);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(8, LOW);
  digitalWrite(10, HIGH);

  delay(2000);
  Serial.println("\n\rArmed");
  while (digitalRead(2) == HIGH);
  digitalWrite(10, LOW);
  Timers.delay_us(150);

  // Pulse pin 3 low for 20us
  digitalWrite(3, LOW);
  delayMicroseconds(20);
  //  Timers.delay_us(20);
  digitalWrite(3, HIGH);
  Timers.delay_us(50);
  while (digitalRead(2) == LOW);
  digitalWrite(10, HIGH);
  Timers.delay_us(150);

  // Pulse pin 5 high for 1ms
  digitalWrite(5, HIGH);
  //  Timers.delay_us(1000);
  delayMicroseconds(1000);
  digitalWrite(5, LOW);
  Timers.delay_us(50);
  while (digitalRead(2) == HIGH);
  digitalWrite(10, LOW);
  Timers.delay_us(250);

  // Pulse pin 8 high for 200 milliseconds
  digitalWrite(8, HIGH);
  delay(200);
  //  Timers.delay_ms(1000);
  digitalWrite(8, LOW);

  Serial.println("\n\pulses sent");
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(10, HIGH);
}


void test03_desc(void)
{
  Serial.println("\n\rTest 03 Description:");
  Serial.println("  Run this test before test05");
  Serial.println("  It waits for pin 2 to go low before");
  Serial.println("  it sends pulses. Then it sends pulses");
  Serial.println("  on each edge of pin 2 it detects.");
}

void test03(uint8_t function)
{
  switch (function) {
    case TESTHELP:
      Serial.print(test_help);
      break;
    case DESCRIPTION:
      test03_desc();
      break;
    case RUNTEST:
      Serial.println("\n\rRun test03");
      test03_test();
      break;
    default:
      Serial.println("\n\rBad Test Function");
      break;
  }
}

