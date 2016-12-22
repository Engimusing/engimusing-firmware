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
#include "MqttModule.h"

extern UARTClass Serial;

class Mq7Module : public MqttModule
{
 public:
  virtual void begin(MqttHub &hub, const char* mod, int32_t pwmCtlPin, int32_t gasSensorPin,uint32_t updateDelay);
  virtual void update(void); // publish changes in switch state
  virtual uint8_t decode(const char* topic, const char* payload);
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
    
 protected:
  virtual void sendCurCo2State();

  int32_t myPwmCtlPin;
  int32_t myGasSensorPin;
  uint32_t myUpdateDelay;
  
  int8_t myAlertState;
  int8_t myState;
  uint32_t mySwitchStateDelay;
  uint32_t myAlertInitialTime;
};

