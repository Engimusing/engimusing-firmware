/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include "Arduino.h"

#include "Device.h"

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
        virtual void begin(int32_t pwmCtlPin, int32_t gasSensorPin);
        virtual void update(void);
        
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
        
        virtual uint32_t currentAlertValue();
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