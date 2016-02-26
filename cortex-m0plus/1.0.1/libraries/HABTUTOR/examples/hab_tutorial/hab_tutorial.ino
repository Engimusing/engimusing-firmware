#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>
#include <HABTUTOR.h>

/*
  Commands:
  {"TOP":"module/LED/1/ON"}
  {"TOP":"module/LED/1/OFF"}
  {"TOP":"module/LED/1/STATE"}
  {"TOP":"module/LED/1/PFRQ","PLD":"time in seconds, zero means once"}

  {"TOP":"module/SWITCH/RED/STATE"}
  {"TOP":"module/SWITCH/RED/PFRQ","PLD":"time in seconds, zero means once"}
  {"TOP":"module/SWITCH/BLACK/STATE"}
  {"TOP":"module/SWITCH/BLACK/PFRQ","PLD":"time in seconds, zero means once"}
  {"TOP":"module/SENSOR/QRE/STATE"}
  {"TOP":"module/SENSOR/QRE/PFRQ","PLD":"time in seconds, zero means once"}
  {"TOP":"module/SWITCH/REED/STATE"}
  {"TOP":"module/SWITCH/REED/PFRQ","PLD":"time in seconds, zero means once"}
  {"TOP":"module/POT/1/STATE"}
  {"TOP":"module/POT/1/PFRQ","PLD":"time in seconds, zero means once"}

  {"TOP":"module/BUZZER/1/ON"}
  {"TOP":"module/BUZZER/1/OFF"}
  {"TOP":"module/BUZZER/1/STATE"}
  {"TOP":"module/BUZZER/1/FREQ","PLD":"frequency in HZ"}
  {"TOP":"module/BUZZER/1/DURATION","PLD":"time in seconds"}
*/

const char efmusbModule[] = "home/efmusb";
const char habModule[] = "home/habtutor";

void setup() {
  Serial.begin(115200);
  COMM.begin();
  ZGUSB.begin();
  ZGUSB.addModule(efmusbModule);
  HABT.begin();
  HABT.addModule(habModule);
  HABT.sch_pot_voltage(50, habModule);
  ZGUSB.sch_temp_cel(50, efmusbModule);
}

void loop() {
  COMM.decode();
}

