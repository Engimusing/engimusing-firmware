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

#include <TMD26721Device.h>

#include <Arduino.h>
#include <Wire.h>

#define TMD26721_ADDRESS 0x39  //Unshifted 7-bit I2C address for the sensor

#define WRITE_COMMAND  0x80

#define ENABLE_REGISTER  0x00
#define ENABLE_COMMAND 0x0D //Set power on, procimity and wait

#define PROXIMITY_TIME_CONTROL_REGISTER 0x02

#define PULSE_COUNT_REGISTER 0x0E

#define CONTROL_REGISTER 0x0F

#define PROXIMITY_LOW_DATA_REGISTER 0x18


void TMD26721Device::begin(TwoWire &wire, int32_t enablePin, uint8_t pulseCount)
{    
    if(enablePin > 0)
    {
        pinMode(enablePin, OUTPUT);
        digitalWrite(enablePin, HIGH);
    }

    myWire = &wire;
    myWire->begin();

    myPulseCount = pulseCount;

    delay(50);

    // Start I2C Transmission
    myWire->beginTransmission(TMD26721_ADDRESS);
    // Select enable register
    myWire->write(ENABLE_REGISTER | WRITE_COMMAND);
    // Set power on, proximity and wait enabled
    myWire->write(ENABLE_COMMAND);
    // Stop I2C Transmission
    myWire->endTransmission();
    delay(50);

    // Start I2C Transmission
    myWire->beginTransmission(TMD26721_ADDRESS);
    // Select proximity time control register
    myWire->write(PROXIMITY_TIME_CONTROL_REGISTER | WRITE_COMMAND);
    // time = 2.73 ms
    myWire->write(0xFF);
    // Stop I2C Transmission
    myWire->endTransmission();

    // Start I2C Transmission
    myWire->beginTransmission(TMD26721_ADDRESS);
    // Select pulse count register
    myWire->write(PULSE_COUNT_REGISTER | WRITE_COMMAND);
    // Pulse count = 4
    myWire->write(pulseCount);
    // Stop I2C Transmission
    myWire->endTransmission();

    // Start I2C Transmission
    myWire->beginTransmission(TMD26721_ADDRESS);
    // Select proximity control register
    myWire->write(CONTROL_REGISTER | WRITE_COMMAND);
    // Proximity uses Ch1 diode
    myWire->write(0x20);
    // Stop I2C Transmission
    myWire->endTransmission();

    //give the slave a slight delay so it can turn on.
    delay(50);
}

int TMD26721Device::proximityData()
{
    unsigned int data[2];
  
    // Start I2C Transmission
    myWire->beginTransmission(TMD26721_ADDRESS);
    // Select data register
    myWire->write(PROXIMITY_LOW_DATA_REGISTER | WRITE_COMMAND);
    // Stop I2C Transmission
    myWire->endTransmission();

    // Request 2 bytes of data
    myWire->requestFrom(TMD26721_ADDRESS, 2);

    // Read 2 bytes of data
    // proximity lsb, proximity msb
    if(myWire->available() == 2)
    {
        data[0] = myWire->read();
        data[1] = myWire->read();
    }

    // Convert the data
    int proximity = data[1] * 256 + data[0];
    
    return proximity;
}


Device::ValueStruct TMD26721Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        output.type = Device::TypeInt;
        output.value.integer = proximityData();
        
        output.name = "PROXIMITY";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

float TMD26721Device::numValues()
{
    return 1; 
}



