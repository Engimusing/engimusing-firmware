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
/* Example for how to setup the MQTT client for the MPLA3115A RS232x2 Engimusing board
 *  There are 3 devices on this board. An LED and an MPLA3115A temperature and altitude sensor. 
 *  See http://www.engimusing.com/products/reedsw-1 for more information about the board.
 */

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif
 
#include <Wire.h>

#include "Arduino.h"

//Include the MqttModule to get the MQTT client classes
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <MPLA3115A2Device.h>
#include <Wire.h>

/*
  EFMZG108 Commands:
  {"TOP":"EFMZG108/BOARD/LED/CTL","PLD":"ON"}
  {"TOP":"EFMZG108/BOARD/LED/CTL","PLD":"OFF"}
  {"TOP":"EFMZG108/BOARD/LED/CTL","PLD":"STATUS"}

  {"TOP":"EFMZG108/BOARD/MPLA3115A2/DEC_C","PLD":"STATUS"}
  {"TOP":"EFMZG108/BOARD/MPLA3115A2/ALT_M","PLD":"STATUS"}
  {"TOP":"EFMZG108/BOARD/MPLA3115A2/PRESSURE","PLD":"STATUS"}
*/

MqttHub HUB;
MqttSerialPort serialPort1;
MqttSerialPort serialPort2;

//MQTT class defintions
// The MqttModule classes are automatically registered with the COMM 
// object when begin() is called so they can be updated 
// whenever HUB.update() is called.
OnOffCtlModule LEDCtrl;

MPLA3115A2Device MPLA3115A2;
SimpleMqttModule MPLA3115A2MqttMod;

void setup()
{
  serialPort1.begin(HUB, Serial);
  serialPort2.begin(HUB, Serial1);
  
  //Initialize the on off control to connect it to
  // the LED that is on the board
  LEDCtrl.begin(HUB, 13, "EFMZG108/BOARD/LED", HIGH);

  //Initialize the Humidity sensor
  MPLA3115A2.begin(Wire0, 3);
  MPLA3115A2MqttMod.begin(HUB, MPLA3115A2, "EFMZG108/BOARD/MPLA3115A2", 5000);
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

  /*
   * example of how to control the LED using one of the Tilt sensors switches
   */
   /*
   //If the led is not in the same state as the swich then 
   // set it to the same as the swich. This check avoids
   // setting the led state every time through the loop
   if(LEDCtrl.pinState() != TiltSwitch1.switchState())
   {
      LEDCtrl.setPinState(TiltSwitch1.switchState());
   }*/
  
  
}