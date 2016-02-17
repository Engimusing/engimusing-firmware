#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>
#include <HABTUTOR.h>

/*
Commands:
{"MOD":"HABTUTOR","TYP":"LED","ACT":"ON"}
{"MOD":"HABTUTOR","TYP":"LED","ACT":"OFF"}
{"MOD":"HABTUTOR","TYP":"SWITCH","IID":"RED"}
{"MOD":"HABTUTOR","TYP":"SWITCH","IID":"BLACK"}
{"MOD":"HABTUTOR","TYP":"SENSOR"}
{"MOD":"HABTUTOR","TYP":"REED"}
{"MOD":"HABTUTOR","TYP":"POT"}
{"MOD":"HABTUTOR","TYP":"BUZZER","ACT":"ON"}
{"MOD":"HABTUTOR","TYP":"BUZZER","ACT":"OFF"}
{"MOD":"HABTUTOR","TYP":"BUZZER","ACT":"ON","PM1":"500"}
{"MOD":"HABTUTOR","TYP":"BUZZER","ACT":"ON","PM1":"500","PM2":"2000"}
*/

void setup() {
  Serial.begin(115200);
  COMM.begin();
  ZGUSB.begin();
  HABT.begin();
}

void loop() {
  COMM.decode();
}

