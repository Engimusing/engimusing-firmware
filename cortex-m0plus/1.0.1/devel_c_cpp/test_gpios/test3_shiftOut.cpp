#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test04 - Tests shiftOut()";

void test03_test(void)
{
  static uint8_t data[8] = {0xAA,0x55,0x33,0xCC,0x77,0x88,0xF0,0x0F};
  static int err_count = 0;
  static int pins[8] = {2,3,4,5,6,7,8,10};

  for(int i = 0; i < 8; i++) {
    pinMode(pins[i], INPUT_PULLDOWN);
  }
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4,LOW);
  pinMode(5, OUTPUT);  
  digitalWrite(5,LOW);
  Serial.println("shiftOut Test");
  delay(1);

  for(int i = 0; i < 8; i++) {
    shiftOut(4,5,MSBFIRST,data[i]);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    delay(1);
  }
}

void test03_desc(void)
{
  Serial.println("\n\rTest 4 Description:");
  Serial.println("  Run test5 on another board before this one.");
  Serial.println("  The second board captures the data");
  Serial.println("  sent by shiftOut() by this board.");
  Serial.println("  The two boards are connected with a 1 to 1 cable");
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
