#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test02 - help entry";

void test02_test(void)
{
/*
  pinMode(2, OUTPUT);
  pinMode(6, INPUT);
  pinMode(3, OUTPUT);
  pinMode(7, INPUT);
  pinMode(4, OUTPUT);
  pinMode(8, INPUT);
  pinMode(5, OUTPUT);
  pinMode(10,INPUT);

  print_gpio_regs();

  Serial.println("\n\rPC15:PD4 -> PB11:PC4");
  testPinIn(2,6);
  Serial.println("\n\rPE12:PD8:PC14 ->  PC1:PA1");
  testPinIn(3,7);
  Serial.println("\n\rPB8:PC3  ->  PC0:PA0");
  testPinIn(4,8);
  Serial.println("\n\rPB7:PC2  -> PE13:PD7:PC13");
  testPinIn(5,10);

  pinMode(6, OUTPUT);
  pinMode(2, INPUT);
  pinMode(7, OUTPUT);
  pinMode(3, INPUT);
  pinMode(8, OUTPUT);
  pinMode(4, INPUT);
  pinMode(10,OUTPUT);
  pinMode(5, INPUT);

  print_gpio_regs();

  Serial.println("\n\rPB11:PC4 -> PC15:PD4");
  testPinIn(6,2);
  Serial.println("\n\rPC1:PA1  -> PE12:PD8:PC14");
  testPinIn(7,3);
  Serial.println("\n\rPC0:PA0  ->  PB8:PC3");
  testPinIn(8,4);
  Serial.println("\n\rPE13:PD7:PC13: ->  PB7:PC2");
  testPinIn(10,5);
 */
}

void test02_desc(void)
{
    Serial.println("\n\rTest Description:");
    Serial.println("  Long multi-line description of the test");
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
