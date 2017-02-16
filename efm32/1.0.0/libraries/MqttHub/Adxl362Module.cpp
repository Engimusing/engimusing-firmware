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
/* 
 Get Acceleration data from ADXL362 sensor.
 */

#include "Adxl362Module.h"

#include <Arduino.h>


// ------------------------------- Adxl362Module -------------------------
void Adxl362Module::begin(MqttHub &hub, const char* mod, uint32_t accel_VIO, uint32_t accel_VS, uint32_t accel_CS, SPIClass &spi, uint32_t updateDelay)
{
  myUpdateDelay = updateDelay;
  
  MqttModule::begin(hub, mod, true);
  
  myAdxl.begin(accel_VIO, accel_VS, accel_CS, &spi);
   
  //give the slave a slight delay so it can turn on.
  delay(500);
  int x = myAdxl.SPIreadTwoRegisters(0);
  myAdxl.beginMeasure();                      // DO LAST! enable measurement mode   
  delay(100);
}

void Adxl362Module::update(void)
{
  if(millis() > myTick + myUpdateDelay) {
    myTick = millis();
	
    sendMQTTAdxlData();
	
  }
}

uint8_t Adxl362Module::decode(const char* topic, const char* payload)
{
  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
	  return 0;
  }
  
  if(compare_token(&topic[j],"STATUS")) {
        sendMQTTAdxlData();
    return 1;
  }
}


void Adxl362Module::sendMQTTAdxlData()
{
    myAdxl.sampleXYZT();    // needs to go into a timer ISR at some point
    
    long x = myAdxl.get_sampleX();
    long y = myAdxl.get_sampleY();
    long z = myAdxl.get_sampleZ();
    
    myHub->sendMessage((const char*)myModule, "X_ACCEL", (int16_t)x);	
    myHub->sendMessage((const char*)myModule, "Y_ACCEL", (int16_t)y);	
	myHub->sendMessage((const char*)myModule, "Z_ACCEL", (int16_t)z);	
}

