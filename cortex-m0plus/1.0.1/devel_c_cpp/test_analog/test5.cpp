#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test05 - help entry";

void test05_test(void)
{
}

void test05_desc(void)
{
  delay(2); Serial.println("\n\rTest 05 Description:");
  delay(2); Serial.println("  Long multi-line description of the test");
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
