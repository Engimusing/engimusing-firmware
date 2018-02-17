///@file CPUInfoDevice.h
///@brief Contains the CPUInfoDevice class which is a Device implementation for accessing the CPU information of an energy micro.
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

///@brief Class for accessing the energy micro's CPU temperature and voltage.
class CPUInfoDevice : public Device
{
 
   public:
        ///@brief Does nothing but defined to keep Device classes consistent.
        virtual void begin();
        ///@brief Get the current temperature of the energy micro CPU in Celsius 
        ///@return Floating point value containing the current temperature of the energy micro CPU in Celsius
        virtual float getTemperatureC();
        ///@brief Get the current temperature of the energy micro CPU in Fahrenheit 
        ///@return Floating point value containing the current temperature of the energy micro CPU in Fahrenheit
        virtual float getTemperatureF();
        ///@brief Get the current Voltage level of the energy micro CPU in Volts.
        ///@return Current voltage level of the energy micro CPU in Volts.
        virtual float voltage();
        
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = DEG_C (float)
        ///index 1 = ADC (float) - current Voltage level of the CPU
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Number of value types available to read.
        ///@return Always returns 2 for this class.
        virtual uint32_t numValues(); 
        
   protected:   

      
};
