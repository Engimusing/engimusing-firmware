#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>

/*
{"TOP":"24353a02522fa331/MOD/ID/SET","PLD":"module topic string"}

{"TOP":"module/LED/RED/ON"}
{"TOP":"module/LED/RED/OFF"}
{"TOP":"module/LED/RED/STAT"}
{"TOP":"module/LED/RED/PFRQ","PLD":"time in seconds, zero means once"}

{"TOP":"module/LED/GREEN/ON"}
{"TOP":"module/LED/GREEN/OFF"}
{"TOP":"module/LED/GREEN/STAT"}
{"TOP":"module/LED/GREEN/PFRQ","PLD":"time in seconds, zero means once"}

{"TOP":"module/LED/BLUE/ON"}
{"TOP":"module/LED/BLUE/OFF"}
{"TOP":"module/LED/BLUE/STAT"}
{"TOP":"module/LED/BLUE/PFRQ","PLD":"time in seconds, zero means once"}

{"TOP":"module/CPUTEMP/CEL/STAT"}
{"TOP":"module/CPUTEMP/CEL/PFRQ","PLD":"time in seconds, zero means once"}
{"TOP":"module/CPUTEMP/FAR/STAT"}
{"TOP":"module/CPUTEMP/FAR/PFRQ","PLD":"time in seconds, zero means once"}

{"TOP":"module/CPUVDD/1/STAT"}
{"TOP":"module/CPUVDD/1/PFRQ","PLD":"time in seconds, zero means once"}

{"TOP":"module/BRDNAME/1/STAT"}
{"TOP":"module/BRDNAME/1/PFRQ","PLD":"time in seconds, zero means once"}
{"TOP":"module/BLVER/1/STAT"}
{"TOP":"module/BLVER/1/PFRQ","PLD":"time in seconds, zero means once"}
{"TOP":"module/CHIPID/1/STAT"}
{"TOP":"module/CHIPID/1/PFRQ","PLD":"time in seconds, zero means once"}
{"TOP":"module/FLASHSIZE/1/STAT"}
{"TOP":"module/FLASHSIZE/1/PFRQ","PLD":"time in seconds, zero means once"}
{"TOP":"module/SRAMSIZE/1/STAT"}
{"TOP":"module/SRAMSIZE/1/PFRQ","PLD":"time in seconds, zero means once"}
*/

void setup() {
  Serial.begin(115200);
  COMM.begin();
  ZGUSB.begin();
}

void loop() {
  COMM.decode();
}

