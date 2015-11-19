#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test10 - help entry";

void test10_test(void)
{
}

void test10_desc(void)
{
  delay(2); Serial.println("\n\rTest 10 Description:");
  delay(2); Serial.println("  Long multi-line description of the test");
  delay(2); Serial.println("  ");
}

void test10(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test10_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test10");
    test10_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
