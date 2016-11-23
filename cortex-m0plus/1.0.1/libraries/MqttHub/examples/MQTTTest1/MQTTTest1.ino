
#include <Wire.h>

#include "Arduino.h"

#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>
#include <Mpu9150Module.h>
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

MqttHub HUB;

//PINS FOR WG840
//#define ADAFRUIT_CC3000_IRQ   33  // MUST be an interrupt pin!
//#define ADAFRUIT_CC3000_VBAT  46  // VBAT & CS can be any digital pins.
//#define ADAFRUIT_CC3000_CS    12

Cc3000PinConfig pinConfig = {
  12, //CS
  60, //IRQ
  52, //VBAT
  SPI //SPI
};

Cc3000WlanConfig wlanConfig = {
  "NETGEAR_ASDF5", //ssid to connect to
  "TimothyDGeorgeLedaMShurtleff", // passcode for the wlan
  WLAN_SEC_WPA2 //security type for the wlan
};

MqttServerConfig mqttServerConfig = {
  "192.168.1.14", //mqtt server address to connect to
  1883, //mqtt port to connect to 
  "EFM32WG842", //name for this device to send to the server
  "username", // username to access the mqtt server
  "password" // password to access the mqtt server
};
 
// pass the three configuration structs from
// above to the wifi port in order to configure it.
MqttCC3000Port WiFiPort(
  pinConfig,
  wlanConfig,
  mqttServerConfig
  );

OnOffCtlModule LEDCtrl0;
OnOffCtlModule LEDCtrl1;
OnOffCtlModule LEDCtrl2;
//detectorSwitchClass Switch1;
//momentarySwitchClass Switch2;
Tmp102Module TMP102;
Mpu9150Module htu21d;
void setup()
{
  
  Serial.begin(115200);

  WiFiPort.begin(HUB);
  
  LEDCtrl0.begin(HUB, ledId[0], "EFM/BOARD/LED0", LOW);
  LEDCtrl1.begin(HUB, ledId[1], "EFM/BOARD/LED1", LOW);
  LEDCtrl2.begin(HUB, ledId[2], "EFM/BOARD/LED2", LOW);

  //pick one or the other since they use the same pin.
  //Switch1.begin(51, "EFM/BOARD/SWITCH1", 10);
  //Switch2.begin(51, "EFM/BOARD/SWITCH2", 10);
  TMP102.begin(HUB, "EFM/BOARD/TMP102", &Wire0, 0, 10000);
  htu21d.begin(HUB, "EFM/BOARD/TMP102", &Wire0, 0, 6, 10000);
  
  //other 3 DF11 slots on the Wonder Gecko board
  //TMP102.begin("EFM/BOARD/TMP102", &Wire1, 24, 10000);
  //TMP102.begin("EFM/BOARD/TMP102", &Wire2, 60, 10000);
  //TMP102.begin("EFM/BOARD/TMP102", &Wire3, 42, 10000);
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
