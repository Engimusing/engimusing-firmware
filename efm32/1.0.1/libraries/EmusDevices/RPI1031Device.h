///@file RPI1031Device.h
///@brief Contains RPI1031Device class which is a Device derived class for accessing an RPI1031 tilt detector
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/RPI-1031_tilt_sensor.pdf
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

///@brief Class for accessing a RPI1031 tilt detector
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/RPI-1031_tilt_sensor.pdf
class RPI1031Device : public Device
{
 
   public:
        ///@brief Initialization function for setting up the settings to connect to an RPI1031
        ///@param [in] switchPin1 Pin connected to the switch pin 1 output on the RPI1031
        ///@param [in] switchPin2 Pin connected to the switch pin 2 output on the RPI1031
        ///@param [in] gndPin1 Pin connected to the ground pin 1 of the RPI1031
        ///@param [in] gndPin2 Pin connected to the ground pin 2 of the RPI1031
        ///@param [in] gndPin3 Pin connected to the ground pin 3 of the RPI1031
        ///@param [in] debounceCount Number of update() calls that a switch much remain constant in order for the device state to be updated
        virtual void begin(int32_t switchPin1, int32_t switchPin2, int32_t gndPin1, int32_t gndPin2, int32_t gndPin3, uint32_t debounceCount);
        
        ///@brief Get the instant state of one of the two switches. Not debounced
        ///@param [in] id Switch id to get the state for. Either 0 or 1.
        ///@return True if the state of the switch is HIGH
        virtual bool switchState(uint8_t id);
         
        ///@brief Check if there has been a rising edge event for a switch since the last time risingEdge has been called.
        ///@param [in] id Switch id to get the rising edge event for.
        ///@return True if there has been a rising edge event.
        virtual bool risingEdge(uint8_t id);
        
        ///@brief Check if there has been a falling edge event for a switch since the last time fallingEdge has been called.
        ///@param [in] id Switch id to get the falling edge event for.
        ///@return True if there has been a falling edge event.
        virtual bool fallingEdge(uint8_t id);
         
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = CURRENT_STATE_0 (string) - either OPEN or CLOSED based on the instant state reading for switch 0
        ///index 1 = RISING_EDGE_0 (bool) - debounced rising edge event has happened for switch 0
        ///index 2 = FALLING_EDGE_0  (bool) - debounced falling edge event has happened for switch 0
        ///index 3 = CURRENT_STATE_1 (string) - either OPEN or CLOSED based on the instant state reading for switch 1
        ///index 4 = RISING_EDGE_1 (bool) - debounced rising edge event has happened for switch 1
        ///index 5 = FALLING_EDGE_1 (bool) - debounced falling edge event has happened for switch 1
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Number of value types available to read.
        ///@return Always returns 3 for this class.
        virtual uint32_t numValues();         
        
        ///@brief Needs to be called periodically in order for the risingEdge and fallingEdge events to be captured.
        virtual void update();
        
   protected:   
        
        bool myFallingEdge[2];
        bool myRisingEdge[2];
        uint32_t mySwitchPin[2];
        uint32_t myDebounceCount;
        bool myLastState[2];
        uint32_t myCurStateCount[2];
      
};