///@file CapSenseDevice.h
///@brief Contains the CapSenseDevice class which is a Device implementation for using the energy micro LESENSE for measuring capacitance.
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

#if NUM_LESENSE_CHANNELS > 0

///@brief Wrapper class for the CapSense class which allows it to be used as a device.
class CapSenseDevice : public Device
{
 
   public:
        ///@brief Function for initialization of the Cap Sense settings
        ///@param [in] channel Specifies the LESENSE channel this object is connected to.
        ///@param [in] sensitivity Sensivity for this channels touch sensor. Set to 0.0 to turn off the channel and 
        ///somewhere between 0.0 and 100.0 to specify what percent of the maximum calibrated value is used to trigger a touch.
        ///@param [in] debounceCount Number of times the threshold must be met to trigger a touch event.
        virtual void begin(uint8_t channel, float sensitivity, uint32_t debounceCount = 1);
        
        ///@brief Current state of the CapSense channel.
        ///@return True if a touch event is currently happening else false
        virtual bool state();
         
        ///@brief Get if there has been a rising edge event since the last time risingEdge() has been called.
        ///@return True if there was a rising edge since the last time this function was called.
        ///@details Used to see if there has been a new touch event started since the last time this function has been called.
        virtual bool risingEdge();
        
        ///@brief Get if there has been a falling edge event since the last time fallingEdge() has been called.
        ///@return True if there was a falling edge since the last time this function was called.
        ///@details Used to see if there has been a new touch event end since the last time this function has been called.
        virtual bool fallingEdge();
         
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = Current state of the touch sensor. Either OPEN or CLOSED (string)
        ///index 1 = RISING_EDGE (bool)
        ///index 2 = FALLING_EDGE (bool)    
        virtual Device::ValueStruct readValue(int index);
        ///@brief Number of value types available to read.
        ///@return Always returns 3 for this class.
        virtual uint32_t numValues(); 
        
        ///@brief Updates the edge states. Should be called periodically to keep the edge state accurate
        virtual void update();
        
   protected:   
        
        bool myFallingEdge;
        bool myRisingEdge;
        uint8_t myChannel;
        float mySenstivity;
        uint32_t myDebounceCount;
        bool myLastState;
        uint32_t myCurStateCount;
};

#endif