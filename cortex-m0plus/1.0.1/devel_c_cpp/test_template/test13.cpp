#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test13 - help entry";

void test13_test(void)
{
}

void test13_desc(void)
{
  delay(2); Serial.println("\n\rTest 13 Description:");
  delay(2); Serial.println("  Long multi-line description of the test");
  delay(2); Serial.println("  ");
}

void test13(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test13_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test13");
    test13_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
