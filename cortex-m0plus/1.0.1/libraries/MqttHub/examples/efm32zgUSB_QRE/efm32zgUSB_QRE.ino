#include "Arduino.h"

#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

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

MqttHub HUB;
MqttSerialPort serialPort;

#define LTSENS_PIN    2
#define GREEN_LED    13
#define BLUE_LED     14
#define RED_LED      15

OnOffCtlModule EFMREDLED;
OnOffCtlModule EFMBLUELED;
OnOffCtlModule EFMGREENLED;
CpuVddModule EFMCPUVDD;
CpuTempModule EFMCPUTMP;
MomentarySwitchModule QRELTS;

void setup()
{
  serialPort.begin(HUB, Serial);

  EFMREDLED.begin(HUB, RED_LED, "EFMUSB/RED/LED", LOW);
  EFMBLUELED.begin(HUB, BLUE_LED, "EFMUSB/BLUE/LED", LOW);
  EFMGREENLED.begin(HUB, GREEN_LED, "EFMUSB/GREEN/LED", LOW);
  EFMCPUVDD.begin(HUB, "EFMUSB/CPU/VDD", 50);
  EFMCPUTMP.begin(HUB, "EFMUSB/CPU/TEMP", 50, 50);
  QRELTS.begin(HUB, LTSENS_PIN, "HAB/LTSENSOR", 2);
}

void loop()
{
  HUB.update();
}

