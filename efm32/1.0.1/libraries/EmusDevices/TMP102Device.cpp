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

#include <TMP102Device.h>
#include <Arduino.h>
#include <Wire.h>

void TMP102Device::begin(TwoWire &wire, int32_t enablePin, bool extendedMode)
{    
    if(enablePin > 0)
    {
        pinMode(enablePin, OUTPUT);
        digitalWrite(enablePin, HIGH);
    }
      
    myAddress = 0x48;
    myDataSize = 2;
    myWire = &wire;
    if(myWire)
    {
     myWire->begin();
    }
    myReadRegister = 0x00;

    //give the slave a slight delay so it can turn on.
    delay(50);
    
    myExtendedMode = extendedMode;
    
    if(myExtendedMode)
    {
        //turn on 13-bit exteneded mode
        if(myWire)
        {
            myWire->beginTransmission(myAddress);
            myWire->write(0x01);//register address
            myWire->write(0x60); //write 2 byte configuration to turn on extended mode
            myWire->write(0xB0); //write 2 byte configuration to turn on extended mode
            myWire->endTransmission();
        }
    }     
}

float TMP102Device::temperature()
{
    //read register 0 from the I2C slave
    if(myWire)
    {
        myWire->beginTransmission(myAddress);
        myWire->write(myReadRegister);//register address
        myWire->requestFrom(myAddress, myDataSize); //read 2 bytes
        myWire->endTransmission();

        byte msb = myWire->read(); 
        byte lsb = myWire->read(); 
        int temp = 0.0;
        if(myExtendedMode)
        {
            //calculate based on 13-bit input
            temp = ((msb << 8) | lsb) >> 3;
            if(temp & 0x1000) 
            {
                temp = ~(0xFFF) | (temp & 0xFFF); //sign extend the temp
            }
        }
        else
        {
            //calculate based on 12-bit input
            temp = ((msb << 8) | lsb) >> 4;
            if(temp & 0x800) 
            {
                temp = ~(0x8FF) | (temp & 0x8FF); //sign extend the temp
            }
        }
        float degc = temp/16.0f;

        return degc;
    }
    return 0.0;
}


Device::ValueStruct TMP102Device::readValue(int index)
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

uint32_t TMP102Device::numValues()
{
    return 1; 
}



