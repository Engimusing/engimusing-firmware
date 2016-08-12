#include "Arduino.h"

#include <EFM32COMM.h>
/*
  EFMUSB Commands:
  {"TOP":"EFM/BOARD/LED0/CTL","PLD":"ON"}
  {"TOP":"EFM/BOARD/LED0/CTL","PLD":"OFF"}
  {"TOP":"EFM/BOARD/LED0/CTL","PLD":"STATUS"}

  {"TOP":"EFM/BOARD/LED1/CTL","PLD":"ON"}
  {"TOP":"EFM/BOARD/LED1/CTL","PLD":"OFF"}
  {"TOP":"EFM/BOARD/LED1/CTL","PLD":"STATUS"}

  {"TOP":"EFM/BOARD/LED2/CTL","PLD":"ON"}
  {"TOP":"EFM/BOARD/LED2/CTL","PLD":"OFF"}
  {"TOP":"EFM/BOARD/LED2/CTL","PLD":"STATUS"}

  {"TOP":"EFM/BOARD/SWITCH1/SWITCH","PLD":""}
*/

onOffCtlClass LEDCtrl0;
onOffCtlClass LEDCtrl1;
onOffCtlClass LEDCtrl2;
detectorSwitchClass Switch1;

void setup()
{
  Serial.begin(115200);
  LEDCtrl0.begin(ledId[0], "EFM/BOARD/LED0", LOW);
  LEDCtrl1.begin(ledId[1], "EFM/BOARD/LED1", LOW);
  LEDCtrl2.begin(ledId[2], "EFM/BOARD/LED2", LOW);
  Switch1.begin(51, "EFM/BOARD/SWITCH1", 10);
}
//int lastMillisOn = 0;
//int lastMillisOff = 1000;
void loop()
{
  COMM.update();
  
  /* //example of how to turn on and off a light using the onOffCtlClass
     //status of the pin will be sent to the MQTT broker.
  if(millis() > lastMillisOff + 2000)
  {
    LEDCtrl2.setPinState(LOW);
    lastMillisOff = millis();
  }
  if(millis() > lastMillisOn + 2000)
  {
    LEDCtrl2.setPinState(HIGH);
    lastMillisOn = millis();
  }*/

}

