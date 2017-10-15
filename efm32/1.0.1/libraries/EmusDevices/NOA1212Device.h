///@file NOA1212Device.h
///@brief Contains the NOA1212Device class which is a Device derived class for accessing an NOA1212 light sensor
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/NOA1212CUTAG_light_sensor.pdf
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

class NOA1212Device : public Device
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
        virtual void begin(int32_t powerPin, int32_t gain1Pin, int32_t gain2Pin, int32_t inputPin, GainSetting gainSetting, uint32_t numSamples);
        virtual void update();
        virtual float averageReflection();
        virtual float instantReflection();
         
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
        
   protected:   
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