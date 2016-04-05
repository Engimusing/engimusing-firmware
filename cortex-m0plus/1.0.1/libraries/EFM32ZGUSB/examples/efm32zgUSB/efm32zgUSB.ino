#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>

/*
  {"TOP":"home/efmusb/LED/RED","PLD":"ON"}
  {"TOP":"home/efmusb/LED/RED","PLD":"OFF"}
  {"TOP":"home/efmusb/LED/RED/STATUS"}

  {"TOP":"home/efmusb/LED/GREEN","PLD":"ON"}
  {"TOP":"home/efmusb/LED/GREEN","PLD":"OFF"}
  {"TOP":"home/efmusb/LED/GREEN/STATUS"}

  {"TOP":"home/efmusb/LED/BLUE","PLD":"ON"}
  {"TOP":"home/efmusb/LED/BLUE","PLD":"OFF"}
  {"TOP":"home/efmusb/LED/BLUE/STATUS"}

  {"TOP":"home/efmusb/CPUTEMP/CEL/STATUS"}
  {"TOP":"home/efmusb/CPUTEMP/FAR/STATUS"}
  {"TOP":"home/efmusb/CPUVDD/1/STATUS"}
*/

static uint8_t efmusbModule[] = "home/efmusb";
uint8_t* module = efmusbModule;

void setup() {
  Serial.begin(115200);
  ZGUSB.begin(module);
  ZGUSB.sch_temp_cel(50, module);
  ZGUSB.sch_temp_far(50, module);
  ZGUSB.sch_cpu_vdd(50, module);
}

void loop() {
  COMM.decode();
  ZGUSB.update();
}

