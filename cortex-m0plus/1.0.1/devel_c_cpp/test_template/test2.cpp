#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test02 - help entry";

void test02_test(void)
{
}

void test02_desc(void)
{
  Serial.println("\n\rTest 02 Description:");
  Serial.println("  Long multi-line description of the test");
  Serial.println("  ");
}

void test02(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test02_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test02");
    test02_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
