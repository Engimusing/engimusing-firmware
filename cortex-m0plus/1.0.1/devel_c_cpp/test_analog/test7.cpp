#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test07 - help entry";

void test07_test(void)
{
}

void test07_desc(void)
{
  delay(2); Serial.println("\n\rTest 07 Description:");
  delay(2); Serial.println("  Long multi-line description of the test");
  delay(2); Serial.println("  ");
}

void test07(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test07_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test07");
    test07_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
