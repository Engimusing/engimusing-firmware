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

class ACS716Module : public MqttModule
{
  public:
    enum ACS716MODEL
    {
        ACS716_6BB = 0,
        ACS716_12CB,
        ACS716_25CB
    };
    
 public:
  
  virtual void begin(MqttHub &hub, const char* mod, int32_t powerPin, int32_t analogPowerFeedbackPin, int32_t analogInputPin, ACS716MODEL model,  uint32_t updateDelay = 60000, uint32_t numSamples = 100);
  virtual void update(void); // publish changes in switch state
  virtual uint8_t decode(const char* topic, const char* payload);
    
    
 protected:
  virtual void sendCurrentValue();

  int32_t myPowerPin;
  int32_t myAnalogPowerFeedbackPin;
  int32_t myAnalogInputPin;

  uint32_t myUpdateDelay;
  
  float my3_3Sensitivity;
  
  uint32_t myNumSamples;
  uint32_t myCurrentSampleCount;
  float myCurrentAveragedValue;
  float myCurrentRunningAverage;
  
  ACS716MODEL myModel;
};

