#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>
#include <QRE1113.h>

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

 {"TOP":"home/qre1113/SENSOR/1/STATUS"}
*/

const char efmusbModule[] = "home/efmusb";
const char qreModule[] = "home/qre1113";

void setup() {
  Serial.begin(115200);
  COMM.begin();
  ZGUSB.begin();
  ZGUSB.addModule(efmusbModule);
  ZGUSB.sch_temp_cel(50, efmusbModule);
  ZGUSB.sch_temp_far(50, efmusbModule);
  ZGUSB.sch_cpu_vdd(50, efmusbModule);

  QRE1113Class QRE;
  QRE.addModule(qreModule);
  QRE.begin(2, qreModule);
}

void loop() {
  COMM.decode();
}

