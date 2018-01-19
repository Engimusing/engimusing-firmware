///
///@file ACS716Device.h
///@brief Contains ACS716Device class which is a Device implementation for the ACS716
/// Link to datasheet: http://www.allegromicro.com/~/media/Files/Datasheets/ACS716-Datasheet.pdf
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
///

#pragma once

#include "Arduino.h"

#include "Device.h"

///@brief Device implementation for the ACS716. It supports the 6,12, and 25 Amp models of the ACS716 current sensor.
/// Link to datasheet: http://www.allegromicro.com/~/media/Files/Datasheets/ACS716-Datasheet.pdf
class ACS716Device : public Device
{
    public:
    
        ///@brief Model type for the ACS716. The last number is the Amperage it can sense
        enum ACS716MODEL
        {
             ///@brief 6 AMP version of the ACS716
            ACS716_6BB = 0,
            ///@brief 12 AMP version of the ACS716
            ACS716_12CB,
            ///@brief 25 AMP version of the ACS716
            ACS716_25CB
        };
        
   public:
        ///@brief Begin function for the device. Sets up the configuration.
        ///@param [in] model Model number of the device. See ACS716MODEL enum.
        ///@param [in] powerPin Pin that is connected to the device's power pin.
        ///@param [in] analogPowerFeedbackPin Pin that reads back the power pin to find out the exact VDD for the device.
        ///@param [in] analogInputPin Pin that is connected to the Devices VOUT pin.
        ///@param [in] numSamples Number of samples to average out when calculating the current.
        ///@param [in] useMinMaxForRMS set to true the RMS calculation will only take into account the min/max values of current
        /// This removes the inaccuracy of the center value for the current.
        virtual void begin(ACS716MODEL model, int32_t powerPin, int32_t analogPowerFeedbackPin, int32_t analogInputPin, uint32_t numSamples, bool useMinMaxForRMS = true);
        
        ///@brief Update the device. Should be run periodically since it takes a measurement of the current and updates the current running average.
        virtual void update();
        
        ///@brief Averaged current value for the last numSamples current measurements.
        ///@return Current in RMS Amps
        virtual float averageCurrent();
        
        ///@brief Single read of the current from the ACS716
        ///@return Current in Amps
        virtual float instantCurrent();
         
        ///@brief Device overridden function which reads one of the values from the device.
        ///@param [in] index Value index to read
        ///@return ValueStruct which contains the name and value for the requested index.
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Gets the number of values this device has (1 in this case)
        ///@return Number of different values this device has (always 1 for the ACS716)
        virtual uint32_t numValues(); 
        
   protected:   
        int32_t myPowerPin;
        int32_t myAnalogPowerFeedbackPin;
        int32_t myAnalogInputPin;
        float my3_3Sensitivity;

        uint32_t myNumSamples;
        uint32_t myCurrentSampleCount;
        float myCurrentRmsCurrentValue;
        float myCurrentRunningAverageSquared;

        bool myUseMinMaxForRMS;
        float myCurrentRunningMax;
        float myCurrentRunningMin;
        
        ACS716MODEL myModel;
      
};