#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test16 - help entry";

void test16_test(void)
{
}

void test16_desc(void)
{
  Serial.println("\n\rTest 16 Description:");
  Serial.println("  Long multi-line description of the test");
  Serial.println("  ");
}

void test16(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test16_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test16");
    test16_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
