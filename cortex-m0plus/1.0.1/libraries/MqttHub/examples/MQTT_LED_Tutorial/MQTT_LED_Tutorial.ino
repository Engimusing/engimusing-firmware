
#include <Wire.h>

#include "Arduino.h"

#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>
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
*/

MqttHub HUB;

MqttSerialPort SerialPort;

OnOffCtlModule LEDCtrl0;
OnOffCtlModule LEDCtrl1;
OnOffCtlModule LEDCtrl2;

void setup()
{
  SerialPort.begin(HUB, Serial);

  LEDCtrl0.begin(HUB, ledId[0], "EFM/BOARD/LED0", LOW);
  LEDCtrl1.begin(HUB, ledId[1], "EFM/BOARD/LED1", LOW);
  LEDCtrl2.begin(HUB, ledId[2], "EFM/BOARD/LED2", LOW);
}
//int lastMillisOn = 0;
//int lastMillisOff = 1000;

uint32_t pingTime=0;
void loop()
{
  HUB.update();
   
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
