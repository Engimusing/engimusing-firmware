
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

  {"TOP":"EFMUSB/CPU/TMPC"}
  {"TOP":"EFMUSB/CPU/TMPF"}
  {"TOP":"EFMUSB/CPU/VDD"}
*/

MqttHub HUB;

MqttSerialPort SerialPort;

// Instantiate classes for each the LEDs on the EFMUSB CPU board
// The onOffCtlClass allows for turning the LEDs on and off and
// requesting their status

OnOffCtlModule LEDCtrl0;
OnOffCtlModule LEDCtrl1;
OnOffCtlModule LEDCtrl2;

// Instantiate classes for the CPU temperature and supply voltage
// These classes can be used to read the values or can be set up
// to periodically report the values

CpuVddModule EFMCPUVDD;
CpuTempModule EFMCPUTMP;

void setup()
{
  SerialPort.begin(HUB, Serial);

  // Start each of the LED services
  // The first parameter is the LED pin
  // The second parameter is the module name
  // The third parameter is the on state for the LEDs
  LEDCtrl0.begin(HUB, ledId[0], "EFM/BOARD/LED0", LOW);
  LEDCtrl1.begin(HUB, ledId[1], "EFM/BOARD/LED1", LOW);
  LEDCtrl2.begin(HUB, ledId[2], "EFM/BOARD/LED2", LOW);

  // Start each of the CPU services
  // The first parameter is the module name
  // The other parameters are time values in tenths of seconds
  // The CPUVDD will send a status every 10 seconds
  EFMCPUVDD.begin(HUB, "EFM/CPU/VDD", 50);

  // The CPUTEMP has two possible status options
  // The first number is 5 seconds for a Farenheit reading
  // The second number is 5 seconds for a Celcius reading
  EFMCPUTMP.begin(HUB, "EFM/CPU/TEMP", 50, 50);
}
//int lastMillisOn = 0;
//int lastMillisOff = 1000;

void loop()
{
  HUB.update();
}
