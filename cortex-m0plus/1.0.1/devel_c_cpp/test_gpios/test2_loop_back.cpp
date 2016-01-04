#include "test.h"


extern LEUARTClass Serial;
static String test_help = "test02 - Loop back test to verify inputs";
static int err_count = 0;

void testPinIn(uint8_t outPin, uint8_t inPin)
{
  digitalWrite(outPin,LOW);
  delay(1);
  if(digitalRead(inPin) != LOW) {
    Serial.println("LOW Error");
    err_count++;
  }
  delay(5);  
  digitalWrite(outPin,HIGH);
  delay(1);
  if(digitalRead(inPin) != HIGH) {
    Serial.println("HIGH Error");
    err_count++;
  }
  digitalWrite(outPin,LOW);
  delay(5);  
}


void test02_test(void)
{
  err_count = 0;

  pinMode(2, OUTPUT);
  pinMode(6, INPUT);
  pinMode(3, OUTPUT);
  pinMode(7, INPUT);
  pinMode(4, OUTPUT);
  pinMode(8, INPUT);
  pinMode(5, OUTPUT);
  pinMode(10,INPUT);

  //  print_gpio_regs();

  Serial.println("PC15:PD4 -> PB11:PC4");
  testPinIn(2,6);
  Serial.println("PE12:PD8:PC14 ->  PC1:PA1");
  testPinIn(3,7);
  Serial.println("PB8:PC3  ->  PC0:PA0");
  testPinIn(4,8);
  Serial.println("PB7:PC2  -> PE13:PD7:PC13");
  testPinIn(5,10);

  pinMode(6, OUTPUT);
  pinMode(2, INPUT);
  pinMode(7, OUTPUT);
  pinMode(3, INPUT);
  pinMode(8, OUTPUT);
  pinMode(4, INPUT);
  pinMode(10,OUTPUT);
  pinMode(5, INPUT);

  //  print_gpio_regs();

  Serial.println("PB11:PC4 -> PC15:PD4");
  testPinIn(6,2);
  Serial.println("PC1:PA1  -> PE12:PD8:PC14");
  testPinIn(7,3);
  Serial.println("PC0:PA0  ->  PB8:PC3");
  testPinIn(8,4);
  Serial.println("PE13:PD7:PC13: ->  PB7:PC2");
  testPinIn(10,5);
  Serial.print("Error Count = "); Serial.println(err_count);
}

void test02_desc(void)
{
  Serial.println("\n\rTest02 Description:");
  Serial.println("  This test performs a loop back test");
  Serial.println("  on the 8 connector pins. It requires");
  Serial.println("  a 10 pin connector with 4 wires");
  Serial.println("  Connected Pins:");
  Serial.println("    Pin 2 to Pin  6");
  Serial.println("    Pin 3 to Pin  7");
  Serial.println("    Pin 4 to Pin  8");
  Serial.println("    Pin 5 to Pin 10");
  Serial.println("  The cable assembly is labeled:");
  Serial.println("    GPIO LOOPBACK");
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

