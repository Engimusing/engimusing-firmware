#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test03 - help entry";

void test03_test(void)
{
}

void test03_desc(void)
{
    Serial.println("\n\rTest Description:");
    Serial.println("  Long multi-line description of the test");
}

void test03(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test03_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test03");
    test03_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
