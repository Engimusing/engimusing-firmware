#include "Arduino.h"

void setup(void)
{
  pinMode(13, OUTPUT);
}

void loop(void)
{
  digitalWrite(13,HIGH);
  //delay(1000);
  //delayMicroseconds(1000000);
  uint32_t start = micros();
  while (micros() - start < 1000000);
  digitalWrite(13,LOW);
  delay(1000);
}

