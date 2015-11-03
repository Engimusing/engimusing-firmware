#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test01 - GPIO LED Test";

#define PINS_TO_TEST    8
#define TEST_ITERATIONS 4

void test01_test(void)
{
  static int pins[8] = {2,4,6,3,5,7,8,10};

  for(int p = 0; p < PINS_TO_TEST; p++) {
    pinMode(pins[p], OUTPUT);
    digitalWrite(pins[p], HIGH);
  }

  for(int i = 0; i < TEST_ITERATIONS; i++) {
    for(int p = 0; p < PINS_TO_TEST; p++) {
      digitalWrite(pins[p], LOW);
      delay(350);
      digitalWrite(pins[p], HIGH);
      delay(350);
    }
  }
  Serial.println("  Test Complete");
}


void test01_desc(void)
{
    Serial.println("\n\rTest Description:");
    Serial.println("  This test is used to test that the 8 connector pins can be driven.");
    Serial.println("  The DF11_10H_to_DF11_10R_X2 LED logic analyzer board is used to");
    Serial.println("  visually watch the LEDs go through a test pattern.");
    Serial.println("  ");
    Serial.println("  ");
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

