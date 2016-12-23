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

class Noa1212Module : public MqttModule
{
  public:
    enum GainSetting
    {
        POWER_DOWN = 0,
        LOW_GAIN,
        MEDIUM_GAIN,
        HIGH_GAIN
    };
    
 public:
  virtual void begin(MqttHub &hub, const char* mod, int32_t powerPin, int32_t gain1Pin, int32_t gain2Pin, int32_t inputPin, GainSetting gainSetting = HIGH_GAIN, uint32_t updateDelay = 60000, uint32_t numSamples = 1000);
  virtual void update(void); // publish changes in switch state
  virtual uint8_t decode(const char* topic, const char* payload);
    
    
 protected:
  virtual void sendReflectivityValue();

  int32_t myPowerPin;
  int32_t myGain1Pin;
  int32_t myGain2Pin;
  int32_t myInputPin;
  uint32_t myUpdateDelay;
  
  
  uint32_t myNumSamples;
  uint32_t myCurrentSampleCount;
  float myCurrentAveragedValue;
  float myCurrentRunningAverage;
  GainSetting myGainSetting;
};

