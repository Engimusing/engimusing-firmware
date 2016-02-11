#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>
#include <HABTUTOR.h>

/*
Commands:
<DEV><MOD>HABTUTOR</MOD><TYPE>LED</TYPE><ACT>ON</ACT></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>LED</TYPE><ACT>OFF</ACT></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>SWITCH</TYPE><ID>RED</ID></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>SWITCH</TYPE><ID>BLACK</ID></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>SENSOR</TYPE></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>REED</TYPE></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>POT</TYPE></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>BUZZER</TYPE><ACT>ON</ACT></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>BUZZER</TYPE><ACT>OFF</ACT></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>BUZZER</TYPE><ACT>ON</ACT><PARAM1>500</PARAM1></DEV>
<DEV><MOD>HABTUTOR</MOD><TYPE>BUZZER</TYPE><ACT>ON</ACT><PARAM1>500</PARAM1><PARAM2>2000</PARAM2></DEV>
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
