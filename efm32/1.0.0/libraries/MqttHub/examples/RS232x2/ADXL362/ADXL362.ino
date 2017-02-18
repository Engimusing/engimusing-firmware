/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/* Example for how to setup the MQTT client for the ADXL362 RS232x2 Engimusing board
 *  There are 2 devices on this board. An LED and an ADXL362 Accelerometer. 
 *  See http://www.engimusing.com/products/adxl-4 for more information about the board.
 */

#include "Arduino.h"

//Include the EFM32COMM to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>
#include <Adxl362Module.h>

/*
  EFMTG110 Commands:
  {"TOP":"EFMTG110/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFMTG110/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMTG110/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMTG110/BOARD/ADXL/CTL","PLD":"STATUS"}  
*/

MqttHub HUB;
MqttSerialPort serialPort1;
MqttSerialPort serialPort2;

//MQTT class defintions
// The EFM32COMM classes are automatically registered with the COMM 
// object when begin() is called so they can be updated 
// whenever COMM.update() is called.
OnOffCtlModule LEDCtrl;

Adxl362Module adxl362;

void setup()
{
  serialPort1.begin(HUB, Serial);
  serialPort2.begin(HUB, Serial1);
  
  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, ledId[0], "EFMTG110/BOARD/LED", HIGH);

  pinMode(ledId[0], OUTPUT);
  digitalWrite(ledId[0], HIGH);
  
  int accel_VIO = 2;
  int accel_VS = 3;
  int accel_CS = 4;
  //Initialize the Humidity sensor
  adxl362.begin(HUB, "EFMTG110/BOARD/ADXL", accel_VIO, accel_VS, accel_CS, SPI, 1000);

  
  
}

//Part of light on off example
//int lastMillisOn = 0;
//int lastMillisOff = 1000;

void loop()
{
  //Update the MQTT communication so it
  // can send statuses and recieve requests
  HUB.update();

  /*
  //example of how to turn on and off a light using the OnOffCtlModule
  //status of the pin will be sent to the MQTT broker.
  if(millis() > lastMillisOff + 2000)
  {
    LEDCtrl.setPinState(LOW);
    lastMillisOff = millis();
  }
  if(millis() > lastMillisOn + 2000)
  {
    LEDCtrl.setPinState(HIGH);
    lastMillisOn = millis();
  }
  */


  
}
