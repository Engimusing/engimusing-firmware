#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test07 - shiftIn() data generation";

// shiftIn test:
// (SI DATA) Pin 4 to Pin  8 (US1_TX)
// (US1_CK)  Pin 5 to Pin 10 (SI CLK)

void test06_test(void)
{
  static int pins[8] = {2,3,4,5,6,7,8,10};
  static uint8_t data[8] = {0xAA,0x55,0x33,0xCC,0x77,0x88,0xF0,0x0F};
  static uint8_t indata[8] = {0xAA,0x55,0x33,0xCC,0x77,0x88,0xF0,0x0F};
  static int err_count = 0;

  for(int i = 0; i < 8; i++) {
    pinMode(pins[i], INPUT_PULLDOWN);
  }
  delay(25);
  // Send 8 bytes to test06 in response to shiftIn()
  err_count = 0;
  pinMode(4, OUTPUT);
  digitalWrite(4,LOW);
  
  while((GPIO->P[PORTC].DIN & 0x8000) == 0x8000);

  for(int w = 0; w < 8; w++) {

    while((GPIO->P[PORTC].DIN & 0x8000) == 0x00);

    if(data[w] & 0x80) {
      GPIO->P[PORTB].DOUTSET = 0x100;
    } else {
      GPIO->P[PORTB].DOUTCLR = 0x100;
    }
    while((GPIO->P[PORTB].DIN & 0x80) == 0x00);
    for(int i = 1; i < 8; i++) {
      while((GPIO->P[PORTB].DIN & 0x80) == 0x80);
      if(data[w] & (1 << (7-i))) {
	GPIO->P[PORTB].DOUTSET = 0x100;
      } else {
	GPIO->P[PORTB].DOUTCLR = 0x100;
      }
      while((GPIO->P[PORTB].DIN & 0x80) == 0x00);
    }

    while((GPIO->P[PORTC].DIN & 0x8000) == 0x8000);

  }
  digitalWrite(4,LOW);
  Serial.println("shiftIn done");
}

void test06_desc(void)
{
  Serial.println("\n\rTest 7 Description:");
  Serial.println("  This test generates data for the shiftIn() function");
  Serial.println("  It needs to be run on a second board connected with");
  Serial.println("  a 1 to 1 cable.");
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
