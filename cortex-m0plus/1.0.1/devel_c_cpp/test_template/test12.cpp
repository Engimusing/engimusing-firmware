#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test12 - help entry";

void test12_test(void)
{
}

void test12_desc(void)
{
  delay(2); Serial.println("\n\rTest 12 Description:");
  delay(2); Serial.println("  Long multi-line description of the test");
  delay(2); Serial.println("  ");
}

void test12(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test12_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test12");
    test12_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
