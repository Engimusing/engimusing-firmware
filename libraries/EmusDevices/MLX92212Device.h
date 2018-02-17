///@file MLX92212Device.h
///@brief Contains the MLX92212Device class which is a Device derived class for accessing the MLX92212 3-wire hall effect switch 
///Datasheet link http://engimusing.github.io/Product_Documentation/data_sheets/MLX92212LSE.pdf
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

///@brief Class for connecting to a MLX92212 hall effect switch.
///Datasheet link http://engimusing.github.io/Product_Documentation/data_sheets/MLX92212LSE.pdf
class MLX92212Device : public Device
{
 
   public:
        ///@brief Initialization function which specifies the pins and other settings for connecting to an MLX92212
        ///@param [in] enablePin Pin that is connected to the MLX92212 enable pin
        ///@param [in] switchPin Pin that is connected to the MLX92212 switch pin
        ///@param [in] debounceCount Number of update() calls that the state must be stable before triggering an edge event.
        virtual void begin(int32_t enablePin, int32_t switchPin, uint32_t debounceCount);
        
        ///@brief Current state of the hall effect switch
        ///@return True if the switch is closed.
        virtual bool switchState();
         
        ///@brief Get if there has been a rising edge event since the last time risingEdge() has been called.
        ///@return True if there was a rising edge since the last time this function was called.
        ///@details Used to see if there has been a new hall effect switch event started since the last time this function has been called.
        virtual bool risingEdge();
        
        ///@brief Get if there has been a falling edge event since the last time fallingEdge() has been called.
        ///@return True if there was a falling edge since the last time this function was called.
        ///@details Used to see if there has been a new hall effect switch event end since the last time this function has been called.
        virtual bool fallingEdge();
         
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = CURRENT_STATE (string) - either OPEN or CLOSED
        ///index 1 = RISING_EDGE (bool)
        ///index 2 = FALLING_EDGE (bool)    
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Number of value types available to read.
        ///@return Always returns 3 for this class.
        virtual uint32_t numValues(); 
        
        ///@brief Call periodically so that the hall effect switch edge events can be received.
        virtual void update();
        
   protected:   
        
        bool myFallingEdge;
        bool myRisingEdge;
        uint32_t mySwitchPin;
        uint32_t myDebounceCount;
        bool myLastState;
        uint32_t myCurStateCount;
      
};
