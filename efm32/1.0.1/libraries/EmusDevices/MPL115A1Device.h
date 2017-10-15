///@file MPL115A1Device.h
///@brief Contains the MPL115A1Device class which is a Device derived class for accessing an MPL115A1 Digital Barometer
///Datasheet link http://engimusing.github.io/Product_Documentation/data_sheets/MPL115A1.pdf
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
#pragma once

#include "Arduino.h"

#include "Device.h"

class SPIClass;

class MPL115A1Device : public Device
{
 
    public:
        virtual void begin(int32_t enablePin, int32_t powerPin, int32_t csPin, SPIClass &spi);
         
        virtual float calculateTemperatureC();
        virtual float calculatePressurekPa();
         
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
        
    protected:   
    
        virtual unsigned int readRegister(byte thisRegister);
        virtual void writeRegister(byte thisRegister, byte thisValue);
        
    protected:
    
        SPIClass *mySpi;
        uint32_t myCsPin;


};