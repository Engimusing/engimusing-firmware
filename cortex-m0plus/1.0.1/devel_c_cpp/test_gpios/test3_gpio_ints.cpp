#include "Arduino.h"
#include "test.h"

extern LEUARTClass Serial;
static String test_help = "test03 - GPIO Interrupt test";

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
  Serial.printf("intA_cnt = %d\r\n",intA_cnt);
  Serial.printf("intB_cnt = %d\r\n",intB_cnt);
  Serial.printf("intC_cnt = %d\r\n",intC_cnt);
  Serial.printf("intD_cnt = %d\r\n",intD_cnt);
  Serial.printf("int_cntr = %d\r\n",int_cntr);
  Serial.printf("err_cntr = %d\r\n\r\n",err_cntr);
}

void pulse_pin_low(uint8_t pin)
{
  digitalWrite(pin, LOW);
  delayMicroseconds(10);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
}


void test03_test(void)
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



void test03_desc(void)
{
  Serial.println("\n\rTest 03 Description:");
  Serial.println("  This test performs a GPIO interrupt");
  Serial.println("  loop back test on the 8 connector pins.");
  Serial.println("  It requires a 10 pin connector with 4 wires");
  Serial.println("  Connected Pins:");
  Serial.println("    Pin 2 to Pin  6");
  Serial.println("    Pin 3 to Pin  7");
  Serial.println("    Pin 4 to Pin  8");
  Serial.println("    Pin 5 to Pin 10");
  Serial.println("  The cable assembly is labeled:");
  Serial.println("    GPIO LOOPBACK");
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
