#include "Arduino.h"

#include <EFM32XML.h>
#include <EFM32ZGUSB.h>

void setup() {
  Serial.begin(115200);
  Serial.printf("\r\n\r\nStart\r\n");
  XML.begin();
  ZGUSB.begin();
}

void loop() {
  XML.decode();
}

