#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test11 - help entry";

void test11_test(void)
{
}

void test11_desc(void)
{
  delay(2); Serial.println("\n\rTest 11 Description:");
  delay(2); Serial.println("  Long multi-line description of the test");
  delay(2); Serial.println("  ");
}

void test11(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test11_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test11");
    test11_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
