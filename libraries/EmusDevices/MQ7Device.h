///@file MQ7Device.h
///@brief Contains MQ7Device class which is a Device derived class for accessing an MQ7 CO detector
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/MQ-7_carbon_monoxide_sensor.pdf
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

///@brief Class for accessing an MQ-7 CO detector.
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/MQ-7_carbon_monoxide_sensor.pdf
///Warning: this has not been fully tested against real high level CO conditions so it should be used in conjunction with a
/// CO detector with a local alarm to ensure safety. 
class MQ7Device : public Device
{
   public:
        enum
        {
            NO_PROBLEM = 0,
            POTENTIAL_PROBLEM,
            PROBLEM,
            POTENTIAL_RECOVERY
        };

        enum
        {
            LOW_HEAT = 0,
            HIGH_HEAT
        };
        
    public:
        ///@brief Initialization of the settings for the pins connected to the MQ-7
        ///@param [in] pwmCtlPin Pin connected to the PWM controller that is connected to the MQ-7
        ///@param [in] gasSensorPin Pin connected to the output sensor pin from the MQ-7
        virtual void begin(int32_t pwmCtlPin, int32_t gasSensorPin);
        ///@brief Updates the current state of the MQ-7. Should be called periodically in order to correctly control the MQ-7 and read the current state.
        ///@details This update() contains a state machine for controlling the current temperature of the MQ-7. 
        ///It also checks the current reading from the MQ-7 to see if there is a CO event.
        virtual void update(void);
        
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = COLEVEL (integer) raw COLEVEL last read from the MQ-7 
        ///index 1 = COALERT (string) either HIGH or LOW 
        virtual Device::ValueStruct readValue(int index);
       
        ///@brief Number of value types available to read.
        ///@return Always returns 2 for this class.
        virtual uint32_t numValues(); 
        
        ///@brief Get the last read raw reading (last update()) from the MQ-7
        ///@return Raw CO reading from the MQ-7
        virtual uint32_t currentAlertValue();
        
        ///@brief Current alert text based on the state of how much CO is detected by the MQ-7
        ///@return "HIGH" if there has been an excess of CO detected and "LOW" if there has not.
        virtual const char *currentAlertText();
        
    protected:   

        int32_t myPwmCtlPin;
        int32_t myGasSensorPin;

        int8_t myAlertState;
        int8_t myState;
        uint32_t mySwitchStateDelay;
        uint32_t myAlertInitialTime;
        uint32_t myAlertValue;
      
};