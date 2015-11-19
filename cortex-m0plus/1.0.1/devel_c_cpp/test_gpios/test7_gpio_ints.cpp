#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test07 - GPIO Interrupt test";

static int intA_cnt = 0;
static int intB_cnt = 0;
static int intC_cnt = 0;
static int intD_cnt = 0;
static int int_cntr = 0;
static int err_cntr = 0;

void isrA(void)
{
  intA_cnt++;
  int_cntr++;
}

void isrB(void)
{
  intB_cnt++;
  int_cntr++;
}

void isrC(void)
{
  intC_cnt++;  
  int_cntr++;
}

void isrD(void)
{
  intD_cnt++;  
  int_cntr++;
}

void print_int_cnts(void) {
  delay(2); Serial.print("intA_cnt = "); Serial.println(intA_cnt);
  delay(2); Serial.print("intB_cnt = "); Serial.println(intB_cnt);
  delay(2); Serial.print("intC_cnt = "); Serial.println(intC_cnt);
  delay(2); Serial.print("intD_cnt = "); Serial.println(intD_cnt);
  delay(2); Serial.print("int_cntr = "); Serial.println(int_cntr);
  delay(2); Serial.print("err_cntr = "); Serial.println(err_cntr); Serial.println();
}

void pulse_pin_low(uint8_t pin)
{
  digitalWrite(pin, LOW);
  delayMicroseconds(10);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
}


void test07_test(void)
{
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  attachInterrupt( 6, isrA, FALLING);  // B11
  attachInterrupt( 7, isrB, RISING);   // A1
  attachInterrupt( 8, isrC, CHANGE);   // A0
  attachInterrupt(10, isrD, FALLING);  // C13
  if(int_cntr != 0) { err_cntr++;}

  pulse_pin_low(2);
  if(int_cntr != 1) { err_cntr++;}

  pulse_pin_low(3);
  if(int_cntr != 2) { err_cntr++;}

  pulse_pin_low(4);
  if(int_cntr != 4) { err_cntr++;}

  pulse_pin_low(5);
  if(int_cntr != 5) { err_cntr++;}

  detachInterrupt(2);
  pulse_pin_low(2);
  if(int_cntr != 5) { err_cntr++;}

  detachInterrupt(3);
  pulse_pin_low(3);
  if(int_cntr != 5) { err_cntr++;}

  detachInterrupt(4);
  pulse_pin_low(4);
  if(int_cntr != 5) { err_cntr++;}

  detachInterrupt(5);
  pulse_pin_low(5);
  if(int_cntr != 5) { err_cntr++;}

  print_int_cnts();

  //---------------------------------------------
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(10,HIGH);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  pinMode( 6, OUTPUT);
  pinMode( 7, OUTPUT);
  pinMode( 8, OUTPUT);
  pinMode(10, OUTPUT);

  int_cntr = 0;
  intA_cnt = 0;
  intB_cnt = 0;
  intC_cnt = 0;
  intD_cnt = 0;

  attachInterrupt(2, isrA, FALLING);  // C15
  attachInterrupt(3, isrB, RISING);   // E12
  attachInterrupt(4, isrC, CHANGE);   // C3
  attachInterrupt(5, isrD, FALLING);  // C2

  if(int_cntr != 0) { err_cntr++;}

  pulse_pin_low(6);
   if(int_cntr != 1) { err_cntr++;}

  pulse_pin_low(7);
  if(int_cntr != 2) { err_cntr++;}

  pulse_pin_low(8);
  if(int_cntr != 4) { err_cntr++;}

  pulse_pin_low(10);
  if(int_cntr != 5) { err_cntr++;}

  detachInterrupt(6);
  pulse_pin_low(6);
  if(int_cntr != 5) { err_cntr++;}

  detachInterrupt(7);
  pulse_pin_low(7);
  if(int_cntr != 5) { err_cntr++;}

  detachInterrupt(8);
  pulse_pin_low(8);
  if(int_cntr != 5) { err_cntr++;}

  pulse_pin_low(10);
  if(int_cntr != 5) { err_cntr++;}

  print_int_cnts();

  //-----------------------------------------------------
}



void test07_desc(void)
{
  delay(2); Serial.println("\n\rTest 07 Description:");
  delay(2); Serial.println("  This test performs a GPIO interrupt");
  delay(2); Serial.println("  loop back test on the 8 connector pins.");
  delay(2); Serial.println("  It requires a 10 pin connector with 4 wires");
  delay(2); Serial.println("  Connected Pins:");
  delay(2); Serial.println("    Pin 2 to Pin  6");
  delay(2); Serial.println("    Pin 3 to Pin  7");
  delay(2); Serial.println("    Pin 4 to Pin  8");
  delay(2); Serial.println("    Pin 5 to Pin 10");
  delay(2); Serial.println("  The cable assembly is labeled:");
  delay(2); Serial.println("    GPIO LOOPBACK");
}

void test07(uint8_t function)
{
  switch(function) {
  case TESTHELP:
    delay(2); Serial.print(test_help);
    break;
  case DESCRIPTION:
    test07_desc();
    break;
  case RUNTEST:
    Serial.println("\n\rRun test07");
    test07_test();
    break;
  default:
    Serial.println("\n\rBad Test Function");
    break;
  }
}
