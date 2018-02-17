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

///@brief Class for connecting to an MPL115A1 Digital Barometer
///Datasheet link http://engimusing.github.io/Product_Documentation/data_sheets/MPL115A1.pdf
class MPL115A1Device : public Device
{
 
    public:
        ///@brief Initialize the settings for which pins are connected to the MPL115A1  
        ///@param [in] enablePin Pin that is connected to the enable pin on the MPL115A1    
        ///@param [in] powerPin Pin that is connected to the power pin on the MPL115A1
        ///@param [in] csPin Pin that is connected to the chip select pin on the MPL115A1
        ///@param [in] spi SPI object that is connected to the MPL115A1
        virtual void begin(int32_t enablePin, int32_t powerPin, int32_t csPin, SPIClass &spi);
         
        ///@brief Get the current temperature in Celsius from the MPL115A1
        ///@return Current temperature in Celsius
        virtual float calculateTemperatureC();
        
        ///@brief Get the current atmospheric pressure in Kilo Pascals
        ///@return Current atmospheric pressure in Kilo Pascals
        virtual float calculatePressurekPa();
         
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = DEG_C (float) 
        ///index 1 = KPA (float)       
        virtual Device::ValueStruct readValue(int index);
       
        ///@brief Number of value types available to read.
        ///@return Always returns 2 for this class.
        virtual uint32_t numValues(); 
        
    protected:   
    
        virtual unsigned int readRegister(byte thisRegister);
        virtual void writeRegister(byte thisRegister, byte thisValue);
        
    protected:
    
        SPIClass *mySpi;
        uint32_t myCsPin;


};