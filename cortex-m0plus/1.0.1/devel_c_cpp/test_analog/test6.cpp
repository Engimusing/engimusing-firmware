#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test06 - help entry";

void test06_test(void)
{
}

void test06_desc(void)
{
  Serial.println("\n\rTest 06 Description:");
  Serial.println("  Long multi-line description of the test");
  Serial.println("  ");
}

void test06(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test06_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test06");
    test06_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}

