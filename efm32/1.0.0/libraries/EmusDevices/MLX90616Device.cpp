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

#include <MLX90616Device.h>
#include <Arduino.h>
#include <Wire.h>

void MLX90616Device::begin(TwoWire *wire, int32_t enablePin, bool extendedMode)
{    
    if(enablePin > 0)
    {
        pinMode(enablePin, OUTPUT);
        digitalWrite(enablePin, HIGH);
    }
      
    myAddress = 0x5A;
    myDataSize = 2;
    myWire = wire;
    if(myWire)
    {
     myWire->begin();
    }
    myReadRegister = 0x07;

    //give the slave a slight delay so it can turn on.
    delay(50);
}

float MLX90616Device::temperature()
{
    //read register 0 from the I2C slave
    if(myWire)
    {
        myWire->beginTransmission(myAddress);
        myWire->write(myReadRegister);//register address
        myWire->requestFrom(myAddress, myDataSize); //read 2 bytes
        myWire->endTransmission();

        byte data_low = myWire->read(); 
        byte data_high = myWire->read(); 
        double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
        double tempData = 0x0000; // zero out the data
        int frac; // data past the decimal point

        // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
        tempData = (double)(((data_high & 0x007F) << 8) + data_low);
        tempData = (tempData * tempFactor)-0.01;

        float celcius = tempData - 273.15;

        return celcius;
    }
    return 0.0;
}


Device::ValueStruct MLX90616Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        if(myWire)
        {
            output.type = Device::TypeFloat;
            output.value.decimal = temperature();
        }
        else
        {
            output.type = Device::TypeCharArray;
            output.value.charArray = "NOREADING";
        }    
        output.name = "DEG_C";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

float MLX90616Device::numValues()
{
    return 1; 
}


