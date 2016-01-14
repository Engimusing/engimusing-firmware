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
static String test_help = "test05 - tone() function";
extern TimersLP Timers;

void test05_test(void)
{
  delayMicroseconds(50);

  Timers.tone(2, 100000);
  delayMicroseconds(2000);
  Timers.noTone(2);

  delayMicroseconds(250);
  Timers.tone(2, 10000);
  delayMicroseconds(2000);
  Timers.noTone(2);

  delayMicroseconds(50);

  Timers.tone(2, 10000, 3);

  while (Timers.tone_active(2) > 0);
  Serial.println("Done");
}

void test05_desc(void)
{
  Serial.println("\n\rTest 05 Description:");
  Serial.println("  Generate tones at various frequencies and");
  Serial.println("  check frequency with a logic analyzer");
  Serial.println("  ");
}

void test05(uint8_t function)
{
  switch (function) {
    case TESTHELP:
      Serial.print(test_help);
      break;
    case DESCRIPTION:
      test05_desc();
      break;
    case RUNTEST:
      Serial.println("\n\rRun test05");
      test05_test();
      break;
    default:
      Serial.println("\n\rBad Test Function");
      break;
  }
}

