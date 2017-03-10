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

#include <ACS716Device.h>
#include <Arduino.h>

void ACS716Device::begin(ACS716MODEL model, int32_t powerPin, int32_t analogPowerFeedbackPin, int32_t analogInputPin, uint32_t numSamples)
{    
    myPowerPin = powerPin;
    myAnalogPowerFeedbackPin = analogPowerFeedbackPin;
    myAnalogInputPin = analogInputPin;
    if(numSamples == 0)
    {
       numSamples = 1;
    }
    myNumSamples = numSamples;
    myCurrentSampleCount = 0;

    myCurrentAveragedValue = 0;
    myCurrentRunningAverage = 0;

    if(myPowerPin > 0)
    {
       pinMode(myPowerPin, OUTPUT_HIGH_DRIVE); //power
    }

    pinMode(myAnalogInputPin, INPUT); //Gain1

    myModel = model;

    //turn on the ACS716
    digitalWrite(myPowerPin, HIGH); //power

    if(model == ACS716_6BB)
    {
        my3_3Sensitivity = .1;
    }
    else if(model == ACS716_12CB)
    {
        my3_3Sensitivity = .037;
    }
    else if(model == ACS716_25CB)
    {
        my3_3Sensitivity = .0185;
    }

    delay(50);
}

void ACS716Device::update(void)
{
    float current =  instantCurrent();
   
    myCurrentRunningAverage += current/myNumSamples;
    myCurrentSampleCount++;
    
    if(myCurrentSampleCount == myNumSamples)
    {
        myCurrentAveragedValue = myCurrentRunningAverage;
        myCurrentSampleCount = 0;
        myCurrentRunningAverage = 0;
    }
}


float ACS716Device::instantCurrent()
{
     //setup default values for if there is not a power feedback pin
    float sensitivity = my3_3Sensitivity;
    float zeroAmpVoltage = 3.3 / 2.0;
    
    if(myAnalogPowerFeedbackPin > 0)
   {   
        //read the power pin so we can calculate the sensitivity and midpoint
        float vddVoltage = (((float)analogRead(myAnalogPowerFeedbackPin)) / 1024.0 * 3.3);

        sensitivity = my3_3Sensitivity * vddVoltage / 3.3;
        zeroAmpVoltage = vddVoltage / 2.0;
   }
   
    float inputVoltage = (((float)analogRead(myAnalogInputPin)) / 1024.0 * 3.3);
      
    float current =  (inputVoltage - zeroAmpVoltage) / sensitivity;
   
    return current;
}


float ACS716Device::averageCurrent()
{
    return myCurrentAveragedValue;
}


Device::ValueStruct ACS716Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = averageCurrent();
        output.name = "CURRENT";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

float ACS716Device::numValues()
{
    return 1; 
}


