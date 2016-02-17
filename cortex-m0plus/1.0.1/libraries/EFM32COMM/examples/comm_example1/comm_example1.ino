#include "Arduino.h"

#include <EFM32COMM.h>

void setup() {
  Serial.begin(115200);
  COMM.begin();
}

void loop() {
  COMM.decode();
}
