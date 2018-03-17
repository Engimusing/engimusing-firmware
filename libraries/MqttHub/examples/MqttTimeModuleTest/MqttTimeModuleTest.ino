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
/* Example for how to setup the MQTT Date and Time module
 *  This sketch is an example of how to use the MqttTimeModule which keeps track of time even if the time server stops.
 */
 
#include <MqttHub.h>
#include <MqttPort.h>
#include <MqttModule.h>

#include <MqttTimeModule.h>

/*
  CLOCK Commands:
  {"TOP":"CLOCK/DATE","PLD":"YYYY:MM:DD"}
  {"TOP":"CLOCK/TIME","PLD":"HH:MM"}
  {"TOP":"CLOCK/DAY","PLD":"DDD"}
  {"TOP":"CLOCK/","PLD":"STATUS"}
*/  

MqttTimeModule moduleTest;

MqttHub HUB;
MqttSerialPort serialPort;

int lastPrintout;

void setup() {

  serialPort.begin(HUB, Serial);
  
  moduleTest.begin(HUB, "CLOCK");
  lastPrintout = millis();
}

void loop() {

  //Update the MQTT communication so it
  // can send statuses and receive requests
  HUB.update();

  if(lastPrintout + 5000 < millis())
  {
    lastPrintout = millis();
    //printout the current date and time.
    Serial.print(moduleTest.dateTime().year());
    Serial.print("-");
    Serial.print(moduleTest.dateTime().month());
    Serial.print("-");
    Serial.println(moduleTest.dateTime().day());
    
    Serial.print(moduleTest.dateTime().hour());
    Serial.print(":");
    Serial.print(moduleTest.dateTime().minute());
    Serial.print(":");
    Serial.println(moduleTest.dateTime().second());

    switch(moduleTest.dateTime().dayOfWeek())
    {
      case 0:
      Serial.println("Monday");    
      break;
      case 1:
      Serial.println("Tuesday");    
      break;
      case 2:
      Serial.println("Wednesday");    
      break;
      case 3:
      Serial.println("Thursday");    
      break;
      case 4:
      Serial.println("Friday");    
      break;
      case 5:
      Serial.println("Saturday");    
      break;
      case 6:
      Serial.println("Sunday");    
      break;
    }
    
    
  }
}
