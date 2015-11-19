#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test02 - pulseIn() test";
extern TimersLP Timers;

void test02_test(void)
{
  uint32_t a, b, dly;


  delay(2); Serial.println("\n\rTest that bad pin fails");
  dly = Timers.pulseIn(2, HIGH, 100);

  delay(2); Serial.println("\n\rTest starting level wrong timeout");
  a = micros();
  dly = Timers.pulseIn(3, HIGH, 100);
  b = micros();
  delay(1); Serial.print("delta-micros = "); Serial.println(b-a);
  delay(1); Serial.print("delay = "); Serial.println(dly);

  delay(2); Serial.println("\n\rTest timeout works");
  a = micros();
  dly = Timers.pulseIn(3, LOW, 100000);
  b = micros();
  delay(1); Serial.print("delta-micros = "); Serial.println(b-a);
  delay(1); Serial.print("delay = "); Serial.println(dly);

}

void test02_desc(void)
{
  delay(2); Serial.println("\n\rTest 02 Description:");
  delay(2); Serial.println("  Test pulseIn() function timeouts and bad pins");
}

void test02(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test02_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test02");
    test02_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
