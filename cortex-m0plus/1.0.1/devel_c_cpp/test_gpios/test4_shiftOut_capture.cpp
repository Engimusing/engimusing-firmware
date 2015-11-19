#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test05 - shiftOut() data capture";

// shiftIn test:
// (SI DATA) Pin 4 to Pin  8 (US1_TX)
// (US1_CK)  Pin 5 to Pin 10 (SI CLK)

void test04_test(void)
{
  static int pins[8] = {2,3,4,5,6,7,8,10};
  static uint8_t data[8] = {0xAA,0x55,0x33,0xCC,0x77,0x88,0xF0,0x0F};
  static uint8_t indata[8] = {0xAA,0x55,0x33,0xCC,0x77,0x88,0xF0,0x0F};
  static int err_count = 0;

  // Read 8 bytes sent from test04 using shiftOut()
  for(int i = 0; i < 8; i++) {
    pinMode(pins[i], INPUT_PULLDOWN);
  }
  for(int w = 0; w < 8; w++) {
    uint8_t sftdata = 0;
    for(int i = 0; i < 8; i++) {
      while(digitalRead(5) == LOW);
      sftdata |= digitalRead(4) << (7-i);
      while(digitalRead(5) == HIGH);
    }
    indata[w] = sftdata;
  }
  for(int w = 0; w < 8; w++) {
    delay(2); Serial.print("data = "); Serial.println(indata[w],HEX);
    if(indata[w] != data[w]) {
      err_count++;
    }
  }
  delay(2); Serial.print("err_count = "); Serial.println(err_count);
}

void test04_desc(void)
{
  delay(2); Serial.println("\n\rTest 5 Description:");
  delay(2); Serial.println("  Companion to Test 4 - Run this on first then Test 5.");
  delay(2); Serial.println("  This runs on a second board and captures the data");
  delay(2); Serial.println("  sent by shiftOut() on the first board.");
  delay(2); Serial.println("  The two boards are connected with a 1 to 1 cable");
}

void test04(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
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
