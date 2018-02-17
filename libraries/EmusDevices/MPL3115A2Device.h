///@file MPL3115A2Device.h
///@brief Contains the MPL3115A2Device class which is a Device derived class for accing the MPL3115A2 Altimeter
///Datasheet link http://engimusing.github.io/Product_Documentation/data_sheets/MPL3115A2.pdf 
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

///@brief Class for accessing an MPL3115A2 Altimeter
///Datasheet link http://engimusing.github.io/Product_Documentation/data_sheets/MPL3115A2.pdf 
class MPL3115A2Device : public Device
{
 
    public:
        ///@brief Initializer function for setting up which TwoWire and enablePin are used to connect to the MPL3115A2
        ///@param [in] wire TwoWire object that is connected to the MPL3115A2
        ///@param [in] enablePin Pin that is connected to the enable pin on the MPL3115A2
        virtual void begin(TwoWire &wire, int32_t enablePin);
         
        ///@brief Read the temperature from the MPL3115A2 in Celsius
        ///@return Temperature reading from the MPL3115A2 in Celsius
        virtual float readTemp();
        
        ///@brief Read the temperature from the MPL3115A2 in Fahrenheit
        ///@return Temperature reading from the MPL3115A2 in Fahrenheit
        virtual float readTempF();
        
        ///@brief Read the altitude from the MPL3115A2 in Meters 
        ///@return Altitude reading from the MPL3115A2 in Meters
        virtual float readAltitude();
        
        ///@brief Read the pressure from the MPL3115A2 in Pascals 
        ///@return Atmospheric pressure in Pascals read from the MPL3115A2
        virtual float readPressure();
        
        ///@brief Read the altitude from the MPL3115A2 in Feet
        ///@return Altitude reading from the MPL3115A2 in Feet
        virtual float readAltitudeFt();

        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = DEG_C (float) 
        ///index 1 = ALT_M (float)   
        ///index 2 = PRESSURE (float)               
        virtual Device::ValueStruct readValue(int index);
       
        ///@brief Number of value types available to read.
        ///@return Always returns 3 for this class.
        virtual uint32_t numValues(); 
        
    protected:   
    
        virtual void setModeBarometer();
        virtual void setModeAltimeter();
        virtual void setModeStandby();
        virtual void setModeActive();
        virtual void setFIFOMode(byte f_Mode);
        virtual void setOversampleRate(byte sampleRate);
        virtual void toggleOneShot();
        virtual void enableEventFlags();
        virtual byte i2cRead(byte regAddr);
        virtual void i2cWrite(byte regAddr, byte value);
        
    protected:
    
        TwoWire *myWire; 

};