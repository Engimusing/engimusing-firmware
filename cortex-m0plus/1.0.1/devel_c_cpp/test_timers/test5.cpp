#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test05 - tone() function";
extern TimersLP Timers;

void test05_test(void)
{
  delayMicroseconds(50);

  Timers.tone(2,100000);
  delayMicroseconds(2000);
  Timers.noTone(2);

  delayMicroseconds(250);
  Timers.tone(2,10000);
  delayMicroseconds(2000);
  Timers.noTone(2);

  delayMicroseconds(50);

  Timers.tone(2,10000,3);

  while(Timers.tone_active(2) > 0);
  delay(2); Serial.println("Done");
}

void test05_desc(void)
{
  delay(2); Serial.println("\n\rTest 05 Description:");
  delay(2); Serial.println("  Generate tones at various frequencies and");
  delay(2); Serial.println("  check frequency with a logic analyzer");
  delay(2); Serial.println("  ");
}

void test05(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
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
