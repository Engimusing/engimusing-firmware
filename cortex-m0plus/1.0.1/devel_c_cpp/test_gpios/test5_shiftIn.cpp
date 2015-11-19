#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test06 - shiftIn() test";

void test05_test(void)
{
  static uint8_t data[8] = {0xAA,0x55,0x33,0xCC,0x77,0x88,0xF0,0x0F};
  static uint8_t indata[8] = {0,0,0,0,0,0,0,0};
  uint32_t datain = 0;
  static int err_count = 0;
  static int pins[8] = {2,3,4,5,6,7,8,10};

  int idata = 4;
  int sclk = 5;
  int gate = 2;

  Serial.println("shiftIn Test");

  for(int i = 0; i < 8; i++) {
    pinMode(pins[i], INPUT_PULLDOWN);
  }
  digitalWrite(gate,LOW);
  pinMode(gate, OUTPUT);
  digitalWrite(sclk,LOW);
  pinMode(sclk, OUTPUT);
  delayMicroseconds(20);

  for(int w = 0; w < 8; w++) {
    digitalWrite(gate,HIGH);
    delayMicroseconds(10);
    datain = shiftIn(idata,sclk,MSBFIRST);
    indata[w] = datain;
    digitalWrite(gate,LOW);
    delayMicroseconds(50);
  }
  for(int w = 0; w < 8; w++) {
    delay(2); Serial.print("data = "); Serial.println(indata[w],HEX);
    delay(2); Serial.print("cdata = "); Serial.println(data[w],HEX);
    if(indata[w] != data[w]) {
      err_count++;
    }
  }
  delay(2); Serial.print("err_count = "); Serial.println(err_count);
}

void test05_desc(void)
{
  delay(2); Serial.println("\n\rTest 6 Description:");
  delay(2); Serial.println("  This tests the shiftIn() function.");
  delay(2); Serial.println("  It requires a second board to generate the data.");
  delay(2); Serial.println("  The second board should be started before this board.");
  delay(2); Serial.println("  The boards are connected with a 1 to 1 cable.");
}

void test05(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test05_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test05");
    test05_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
