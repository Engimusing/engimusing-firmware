#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test08 - help entry";

void test08_test(void)
{
}

void test08_desc(void)
{
  delay(2); Serial.println("\n\rTest 08 Description:");
  delay(2); Serial.println("  Long multi-line description of the test");
  delay(2); Serial.println("  ");
}

void test08(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test08_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test08");
    test08_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
