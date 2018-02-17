///@file TMP102Device.h
///@brief Contains TMP102Device class which is a Device derived class for accessing a TMP102 temperature sensor
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/TMP102.pdf
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

class TwoWire;

///@brief Class for accessing a TMP102 temperature sensor.
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/TMP102.pdf
class TMP102Device : public Device
{
 
   public:
        
        ///@brief Initializer function for setting up the connection to the TMP102
        ///@param [in] wire TwoWire object to use when connecting to the TMP102
        ///@param [in] enablePin Pin connected to the enable pin on the TMP 102
        ///@param [in] extendedMode True to turn on 13-bit extended temperature reading
        virtual void begin(TwoWire &wire, int32_t enablePin, bool extendedMode);
        
        ///@brief Get the current temperature in Celsius
        ///@return Temperature in Celsius
        virtual float temperature();
        
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = DEG_C (float or string) - Temperature in Celsius or string that is "NOREADING" if the device is not initialized
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Number of value types available to read.
        ///@return Always returns 1 for this class.
        virtual uint32_t numValues();   
        
   protected:   
        bool myExtendedMode;
        TwoWire *myWire;
        uint8_t myAddress; 
        uint8_t myDataSize; 
        uint8_t myReadRegister;
      
};