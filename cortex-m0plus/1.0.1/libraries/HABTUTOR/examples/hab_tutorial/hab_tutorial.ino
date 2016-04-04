#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>
#include <HABTUTOR.h>

/*
  Commands:
  {"TOP":"HABTUTOR/LED/1/ON"}
  {"TOP":"HABTUTOR/LED/1/OFF"}
  {"TOP":"HABTUTOR/LED/1/STATUS"}

  {"TOP":"HABTUTOR/SWITCH/RED/STATUS"}

  {"TOP":"HABTUTOR/SWITCH/BLACK/STATUS"}

  {"TOP":"HABTUTOR/SENSOR/QRE/STATUS"}

  {"TOP":"HABTUTOR/SWITCH/REED/STATUS"}

  {"TOP":"HABTUTOR/POT/1/STATUS"}
  {"TOP":"HABTUTOR/POT/1/INTERVAL"}

  {"TOP":"HABTUTOR/BUZZER/1/ON"}
  {"TOP":"HABTUTOR/BUZZER/1/OFF"}
  {"TOP":"HABTUTOR/BUZZER/1/STATUS"}
  {"TOP":"HABTUTOR/BUZZER/1/FREQ","PLD":"500"} // freq in Hz
  {"TOP":"HABTUTOR/BUZZER/1/DURATION","PLD":"200"} // duration in seconds

*/

const char efmusbModule[] = "home/efmusb";
const char habModule[] = "home/habtutor";

uint8_t item_module[] = "testModule";
static uint8_t itemModule[] = "home/habtutor";

uint8_t *ptr_module = item_module;

void setup() {
  Serial.begin(115200);
  COMM.begin();
  ZGUSB.begin(ptr_module);
  HABT.begin(habModule);
  HABT.sch_pot_voltage(50, habModule);
  ZGUSB.sch_temp_cel(50);
  ZGUSB.sch_temp_far(50);
  ZGUSB.sch_cpu_vdd(50);

  Serial.printf("Start Test: \r\n\r\n");
}

void loop() {
  COMM.decode();
}

