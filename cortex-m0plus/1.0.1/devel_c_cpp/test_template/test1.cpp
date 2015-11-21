#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test01 - help entry";

void test01_test(void)
{
}

void test01_desc(void)
{
  Serial.println("\n\rTest 01 Description:");
  Serial.println("  Long multi-line description of the test");
  Serial.println("  ");
}

void test01(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
    break;
  case DESCRIPTION:
    test01_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test01");
    test01_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
