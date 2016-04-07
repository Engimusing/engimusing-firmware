#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>
#include <HABTUTOR.h>

/*
  EFMUSB Commands:
  {"TOP":"EFMUSB/LED/RED","PLD":"ON"}
  {"TOP":"EFMUSB/LED/RED","PLD":"OFF"}
  {"TOP":"EFMUSB/LED/RED","PLD":"STATUS"}

  {"TOP":"EFMUSB/LED/GREEN","PLD":"ON"}
  {"TOP":"EFMUSB/LED/GREEN","PLD":"OFF"}
  {"TOP":"EFMUSB/LED/GREEN","PLD":"STATUS"}

  {"TOP":"EFMUSB/LED/BLUE","PLD":"ON"}
  {"TOP":"EFMUSB/LED/BLUE","PLD":"OFF"}
  {"TOP":"EFMUSB/LED/BLUE","PLD":"STATUS"}

  {"TOP":"EFMUSB/CPU/TMPC"}
  {"TOP":"EFMUSB/CPU/TMPF"}
  {"TOP":"EFMUSB/CPU/VDD"}

  HAB Commands:
  {"TOP":"HABTUTOR/LED","PLD":"ON"}
  {"TOP":"HABTUTOR/LED","PLD":"OFF"}
  {"TOP":"HABTUTOR/LED","PLD":"STATUS"}

  {"TOP":"HABTUTOR/SWITCH/RED"}

  {"TOP":"HABTUTOR/SWITCH/BLACK"}

  {"TOP":"HABTUTOR/SENSOR/QRE"}

  {"TOP":"HABTUTOR/SWITCH/REED"}

  {"TOP":"HABTUTOR/POT"}

  {"TOP":"HABTUTOR/BUZZER","PLD":"ON"}
  {"TOP":"HABTUTOR/BUZZER","PLD":"OFF"}
  {"TOP":"HABTUTOR/BUZZER","PLD":"STATUS"}
  {"TOP":"HABTUTOR/BUZZER","PLD":"F500"} // freq in Hz
  {"TOP":"HABTUTOR/BUZZER","PLD":"D200"} // duration in seconds
*/

// need HABT instantiation and pin selection
HABTUTORClass HABT;

void setup()
{
  Serial.begin(115200);
  ZGUSB.begin("EFMUSB");
  ZGUSB.sch_temp_cel(50);
  ZGUSB.sch_temp_far(50);
  ZGUSB.sch_cpu_vdd(50);
  HABT.begin(BLKSW_PIN,"HABTUTOR");
  HABT.sch_pot_voltage(50);
}

void loop()
{
  if (COMM.decode()) {
    if(ZGUSB.decode_cmd() == 0) {
      HABT.decode_cmd();
    }
  }
  ZGUSB.update();
  HABT.update();
}

