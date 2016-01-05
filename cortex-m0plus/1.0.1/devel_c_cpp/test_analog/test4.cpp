#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test04 - help entry";

void test04_test(void)
{
}

void test04_desc(void)
{
  Serial.println("\n\rTest 04 Description:");
  Serial.println("  Long multi-line description of the test");
  Serial.println("  ");
}

void test04(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
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

