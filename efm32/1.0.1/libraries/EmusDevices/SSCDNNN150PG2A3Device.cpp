/*
  Copyright (c) 2017 Engimusing LLC.  All right reserved.

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

#include <Arduino.h>

#include <SSCDNNN150PG2A3Device.h>
#include <Wire.h>

#define BRIDGE_DATA_H   0x00
#define BRIDGE_DATA_L   0x01
#define SSCDNNN150PG2A3_ADDRESS 0x28 // 7-bit I2C address

void  SSCDNNN150PG2A3Device::begin(TwoWire &wire, int32_t enablePin)
{    
   if(enablePin > 0)
  {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);
  }
  
  myWire = &wire;
   // Initialize the 'Wire' class for the I2C-bus.
  myWire->begin();

  //give the slave a slight delay so it can turn on.
  delay(50);
  
}


//Reads the current pressure in PSI
float SSCDNNN150PG2A3Device::readPressure()
{
  // Read pressure registers
  myWire->requestFrom(SSCDNNN150PG2A3_ADDRESS, 2); // Request two bytes

  //Wait for data to become available
  int counter = 0;
  while(myWire->available() < 2)
  {
    if(counter++ > 100) return(-999); //Error out
    delay(10);
  }

  byte msb, lsb;
  msb = myWire->read();
  lsb = myWire->read();

  uint32_t p = 0;
  if((msb & 0xC0) == 0) {
    p = (msb << 8) | lsb;
  }
  float pressure = ((p-1638) * 150) / (14745-1638);

  return(pressure);
}


Device::ValueStruct SSCDNNN150PG2A3Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readPressure();
        output.name = "PRESSURE";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

uint32_t SSCDNNN150PG2A3Device::numValues()
{
    return 1; 
}

