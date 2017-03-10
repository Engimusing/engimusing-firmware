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

class ACS716Device : public Device
{
    public:
        enum ACS716MODEL
        {
            ACS716_6BB = 0,
            ACS716_12CB,
            ACS716_25CB
        };
   public:
        virtual void begin(ACS716MODEL model, int32_t powerPin, int32_t analogPowerFeedbackPin, int32_t analogInputPin, uint32_t numSamples);
        virtual void update();
        virtual float averageCurrent();
        virtual float instantCurrent();
         
        virtual Device::ValueStruct readValue(int index);
        virtual float numValues(); 
        
   protected:   
        int32_t myPowerPin;
        int32_t myAnalogPowerFeedbackPin;
        int32_t myAnalogInputPin;
        float my3_3Sensitivity;

        uint32_t myNumSamples;
        uint32_t myCurrentSampleCount;
        float myCurrentAveragedValue;
        float myCurrentRunningAverage;

        ACS716MODEL myModel;
      
};