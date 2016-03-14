#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>

/*
 {"TOP":"EFMUSB/LED/RED/ON"}
 {"TOP":"EFMUSB/LED/RED/OFF"}
 {"TOP":"EFMUSB/LED/RED/STATUS"}

 {"TOP":"EFMUSB/LED/GREEN/ON"}
 {"TOP":"EFMUSB/LED/GREEN/OFF"}
 {"TOP":"EFMUSB/LED/GREEN/STATUS"}

 {"TOP":"EFMUSB/LED/BLUE/ON"}
 {"TOP":"EFMUSB/LED/BLUE/OFF"}
 {"TOP":"EFMUSB/LED/BLUE/STATUS"}

 {"TOP":"EFMUSB/LED/ALL/ON"}
 {"TOP":"EFMUSB/LED/ALL/OFF"}
 {"TOP":"EFMUSB/LED/ALL/STATUS"}

 {"TOP":"EFMUSB/CPUTEMP/CEL/STATUS"}
 {"TOP":"EFMUSB/CPUTEMP/CEL/INTERVAL","PLD":"time"} // seconds, zero means off

 {"TOP":"EFMUSB/CPUTEMP/FAR/STATUS"}
 {"TOP":"EFMUSB/CPUTEMP/FAR/INTERVAL","PLD":"time"} // seconds, zero means off
 
 {"TOP":"EFMUSB/CPUVDD/1/STATUS"}
 {"TOP":"EFMUSB/CPUVDD/1/INTERVAL","PLD":"time"} // seconds, zero means off

 {"TOP":"EFMUSB/BRDINFO"}
*/

void setup() {
  Serial.begin(115200);
  COMM.begin();
  ZGUSB.begin();
}

void loop() {
  COMM.decode();
}

