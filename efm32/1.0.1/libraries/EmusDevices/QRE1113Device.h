///@file QRE1113Device.h
///@brief Contains QRE1113Device class which is a Device derived class for accessing a QRE1113 reflective object sensor
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/QRE1113.GR.pdf
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

///@brief Class for connecting to a QRE1113 and using the reflective sensor as a switch
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/QRE1113.GR.pdf
class QRE1113Device : public Device
{
 
   public:
        ///@brief Initialize the settings for connecting to the QRE1113
        ///@param [in] enablePin Pin connected to the enable pin on the QRE1113
        ///@param [in] switchPin Pin connected to the switch pin output of the QRE1113
        ///@param [in] debounceCount Number of consecutive update() calls with the same state read from the QRE1113 before updating the device state
        ///@param [in] onThreshold Compared to the length of time in microseconds that the pin stayed high. If the time it stayed high is less than the onThreashold then the switch is considered pressed.
        virtual void begin(int32_t enablePin, int32_t switchPin, uint32_t debounceCount, uint32_t onThreshold = 400);
        
        ///@brief Reads a value from the QRE1113 to see if it is being pressed or not.
        ///@return Returns true if the QRE1113 is being pressed. This is an instant state result not a debounced result
        virtual bool switchState();
         
        ///@brief Returns true if there has been a debounced press since the last time this function has been called.
        ///@return True if there has been a press.
        virtual bool risingEdge();
        
        ///@brief Returns true if there has been a debounced release since the last time this function has been called.
        ///@return True if there has been a release.
        virtual bool fallingEdge();
         
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = CURRENT_STATE (string) - either OPEN or CLOSED based on the instant state reading
        ///index 1 = RISING_EDGE (bool) - debounced press event has happened
        ///index 2 = FALLING_EDGE (bool) - debounced release event has happened
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Number of value types available to read.
        ///@return Always returns 3 for this class.
        virtual uint32_t numValues();         
        
        ///@brief Needs to be called periodically in order for the risingEdge and fallingEdge events to be captured.
        virtual void update();
        
   protected:   
        
        bool myFallingEdge;
        bool myRisingEdge;
        uint32_t mySwitchPin;
        uint32_t myDebounceCount;
        bool myLastState;
        uint32_t myCurStateCount;
        uint32_t myOnThreshold;
};
