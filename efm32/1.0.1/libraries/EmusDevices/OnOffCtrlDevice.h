///@file OnOffCtrlDevice.h
///@brief Contains OnOffCtrlDevice class which is a Device derived class for accessing a pin digitally
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

///@brief Class for controlling a pin using the device interface. Can set the pin to either on or off.
class OnOffCtrlDevice : public Device
{
   public:
        ///@brief Initialize the settings needed to setup an on/off controller
        ///@param [in] pin Pin to control with this on/off controller
        ///@param [in] defaultState Default state for the pin to be in after begin() is called
        ///@param [in] onLevel Voltage level for the pin when this device is considered to be on.
        virtual void begin(int32_t pin, bool defaultState, int32_t onLevel);

        ///@brief Write a value to the state of this pin. It checks for a value name of "CTL" and a value of "ON" or "OFF"
        ///@param [in] valueName Name of the value to set. This class only supports "CTL"
        ///@param [in] value Value to set the CTL state to. Either "ON" or "OFF"
        ///@return Returns true if the value name and value were processed by the device.
        ///@details Send "CTL", "ON" to turn on the device which will set the pin to the onLevel
        ///Send "CTL", "OFF" to turn off the device which will set the pin to the !onLevel
        virtual bool writeValue(const char *valueName, const char *value);
        
        ///@brief Set the current state of the pin
        ///@param [in] state True will turn on the device and set the pin to the onLevel. False sets it to !onLevel
        virtual void setState(bool state);
        
        ///@brief Device interface function for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = SWITCH (string) current state of the device, "ON" or "OFF"
        virtual Device::ValueStruct readValue(int index);
       
        ///@brief Number of value types available to read.
        ///@return Always returns 1 for this class.
        virtual uint32_t numValues(); 
        
   protected:   
        int32_t myPin;
        int32_t myOnLevel; 
        bool myState; 
      
};