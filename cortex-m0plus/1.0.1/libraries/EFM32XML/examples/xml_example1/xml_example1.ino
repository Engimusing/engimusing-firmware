#include "Arduino.h"

#include <EFM32XML.h>

void setup() {
  Serial.begin(115200);
  Serial.printf("\r\n\r\nStart\r\n");
  XML.begin();
}

void loop() {
  XML.decode();
}
