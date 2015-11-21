#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test06 - PWM Test";
extern TimersLP Timers;

void test06_test(void)
{
  digitalWrite(4,HIGH);
  pinMode(4,OUTPUT);
  delay(1);

  Timers.analogWrite(2,32);
  delay(20);
  digitalWrite(4,LOW);

  Timers.analogWrite(2,64);
  delay(20);
  digitalWrite(4,HIGH);

  Timers.analogWrite(2,128);
  delay(20);
  digitalWrite(4,LOW);

  Timers.analogWrite(2,255);
  delay(20);
  digitalWrite(4,HIGH);

  Timers.analogWrite(2,0);
  delay(20);
  digitalWrite(4,LOW);

  Timers.analogWrite(2,128);
  delay(20);
  digitalWrite(4,HIGH);

  Timers.noPWM(2);
}

void test06_desc(void)
{
  Serial.println("\n\rTest 06 Description:");
  Serial.println("  ");
  Serial.println("  ");
  Serial.println("  ");
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
