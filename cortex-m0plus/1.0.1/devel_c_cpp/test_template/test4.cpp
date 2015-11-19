#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test04 - help entry";

void test04_test(void)
{
}

void test04_desc(void)
{
  delay(2); Serial.println("\n\rTest 04 Description:");
  delay(2); Serial.println("  Long multi-line description of the test");
  delay(2); Serial.println("  ");
}

void test04(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test04_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test04");
    test04_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
