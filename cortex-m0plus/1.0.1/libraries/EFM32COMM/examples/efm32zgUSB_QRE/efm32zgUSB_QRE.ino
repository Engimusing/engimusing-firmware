#include "Arduino.h"

#include <EFM32COMM.h>

/*
  EFMUSB Commands:
  {"TOP":"EFMUSB/RED/LED/CTL","PLD":"ON"}
  {"TOP":"EFMUSB/RED/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMUSB/RED/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMUSB/GREEN/LED/CTL","PLD":"ON"}
  {"TOP":"EFMUSB/GREEN/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMUSB/GREEN/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMUSB/BLUE/LED/CTL","PLD":"ON"}
  {"TOP":"EFMUSB/BLUE/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMUSB/BLUE/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMUSB/CPU/TMPC"}
  {"TOP":"EFMUSB/CPU/TMPF"}
  {"TOP":"EFMUSB/CPU/VDD"}

  QRE Commands:
  {"TOP":"QRE1/SENSOR/QRE"}
*/

#define LTSENS_PIN    2
#define GREEN_LED    13
#define BLUE_LED     14
#define RED_LED      15

onOffCtlClass EFMREDLED;
onOffCtlClass EFMBLUELED;
onOffCtlClass EFMGREENLED;
cpuVDDClass EFMCPUVDD;
cpuTempClass EFMCPUTMP;
momentarySwitchClass QRELTS;

void setup()
{
  Serial.begin(115200);

  EFMREDLED.begin(RED_LED, "EFMUSB/RED/LED", LOW);
  EFMBLUELED.begin(BLUE_LED, "EFMUSB/BLUE/LED", LOW);
  EFMGREENLED.begin(GREEN_LED, "EFMUSB/GREEN/LED", LOW);
  EFMCPUVDD.begin("EFMUSB/CPU/VDD", 50);
  EFMCPUTMP.begin("EFMUSB/CPU/TEMP", 50, 50);
  QRELTS.begin(LTSENS_PIN, "HAB/LTSENSOR", 2);
}

void loop()
{
  if (COMM.decode()) {
    EFMREDLED.decode();
    EFMBLUELED.decode();
    EFMGREENLED.decode();
    EFMCPUVDD.decode();
    EFMCPUTMP.decode();
  }
  EFMREDLED.update();
  EFMBLUELED.update();
  EFMGREENLED.update();
  EFMCPUVDD.update();
  EFMCPUTMP.update();
  QRELTS.update();
}

