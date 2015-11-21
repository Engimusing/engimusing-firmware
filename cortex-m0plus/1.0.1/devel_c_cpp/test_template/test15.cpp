#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test15 - help entry";

void test15_test(void)
{
}

void test15_desc(void)
{
  Serial.println("\n\rTest 15 Description:");
  Serial.println("  Long multi-line description of the test");
  Serial.println("  ");
}

void test15(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test15_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test15");
    test15_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
