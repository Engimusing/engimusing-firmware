#include "Arduino.h"

#include <EFM32COMM.h>
#include <EFM32ZGUSB.h>
#include <QRE1113.h>

/*
  EFMZGUSB Commands:
  {"TOP":"EFMUSB_CMD/LED/RED","PLD":"ON"}
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

  QRE Commands:
  {"TOP":"QRE1/SENSOR/QRE"}
*/

QRE1113Class QRE1;

void setup()
{
  Serial.begin(115200);
  ZGUSB.begin("EFMUSB");
  ZGUSB.sch_temp_cel(50);
  ZGUSB.sch_temp_far(50);
  ZGUSB.sch_cpu_vdd(50);
  QRE1.begin(2, "QRE1");
}

void loop()
{
  if (COMM.decode()) {
    if(ZGUSB.decode_cmd() == 0) {
      QRE1.decode_cmd();
    }
  }
  ZGUSB.update();
  QRE1.update();
}



