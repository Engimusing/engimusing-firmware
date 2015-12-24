#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test04 - pulseIn() receive pulses";
extern TimersLP Timers;

void test04_test(void)
{
  uint32_t a, b, c, d, e, f, dly1, dly2, dly3;

  digitalWrite(2,HIGH);
  digitalWrite(10,INPUT);
  pinMode(2,OUTPUT);
  pinMode(10,INPUT);

  if(digitalRead(10) == LOW) {
    Serial.println("\n\rTransmitter already triggered");
  }
  digitalWrite(2,LOW);
  while(digitalRead(10) == HIGH);

  a = micros();
  dly1 = Timers.pulseIn(3, LOW, 10000);
  b = micros();

  digitalWrite(2,HIGH);
  while(digitalRead(10) == LOW);
  c = micros();
  dly2 = Timers.pulseIn(5, HIGH, 3000);
  d = micros();

  digitalWrite(2,LOW);
  while(digitalRead(10) == HIGH);
  e = micros();
  dly3 = Timers.pulseIn(8, HIGH, 4000000);
  f = micros();

  digitalWrite(2,HIGH);
  Serial.print("delta-micros = "); Serial.println(b-a);
  Serial.print("pulse width 1 = "); Serial.println(dly1); Serial.println("");

  Serial.print("delta-micros = "); Serial.println(d-c);
  Serial.print("pulse width 2 = "); Serial.println(dly2); Serial.println("");

  Serial.print("delta-micros = "); Serial.println(f-e);
  Serial.print("pulse width 3 = "); Serial.println(dly3); Serial.println("");
}

void test04_desc(void)
{
  Serial.println("\n\rTest 04 Description:");
  Serial.println("  This tests pulseIn() for various pulses received");
  Serial.println("  from a board running test03. It asserts pin 2 low");
  Serial.println("  when it is ready for the first pulse and then toggles");
  Serial.println("  pin 2 when it is ready for subsequent pulses.");
}

void test04(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    Serial.print(test_help);
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
