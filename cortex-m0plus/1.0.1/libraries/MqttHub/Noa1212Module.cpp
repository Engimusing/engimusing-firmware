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

#include "Noa1212Module.h"

#include <Arduino.h>

// ------------------------------- Noa1212Module -------------------------
void Noa1212Module::begin(MqttHub &hub, const char* mod, int32_t powerPin, int32_t gain1Pin, int32_t gain2Pin, int32_t inputPin, GainSetting gainSetting, uint32_t updateDelay, uint32_t numSamples)
{
   myPowerPin = powerPin;
   myGain1Pin = gain1Pin;
   myGain2Pin = gain2Pin;
   myInputPin = inputPin;
   myUpdateDelay = updateDelay;
   if(numSamples == 0)
   {
       numSamples = 1;
   }
   myNumSamples = numSamples;
   myCurrentSampleCount = 0;
   
   myCurrentAveragedValue = 0;
   myCurrentRunningAverage = 0;
   
   pinMode(myPowerPin, OUTPUT); //power
   pinMode(myGain1Pin, OUTPUT); //Gain1
   pinMode(myGain2Pin, OUTPUT); //Gain2

   myGainSetting = gainSetting;
   if(gainSetting == POWER_DOWN)
   {
        //G1 Low G2 Low sets the NOA1212 to Power Down.
        digitalWrite(myGain1Pin, LOW); //Gain1
        digitalWrite(myGain2Pin, LOW); //Gain2     
   }
   else if(gainSetting == LOW_GAIN)
   {
       //G1 High G2 High sets the NOA1212 to low gain.
        digitalWrite(myGain1Pin, HIGH); //Gain1
        digitalWrite(myGain2Pin, HIGH); //Gain2     
   }
   else if(gainSetting == MEDIUM_GAIN)
   {
       //G1 Low G2 High sets the NOA1212 to medium gain.
        digitalWrite(myGain1Pin, LOW); //Gain1
        digitalWrite(myGain2Pin, HIGH); //Gain2     
   }
   else if(gainSetting == HIGH_GAIN)
   {
        //G1 High G2 Low sets the NOA1212 to high gain.
        digitalWrite(myGain1Pin, HIGH); //Gain1
        digitalWrite(myGain2Pin, LOW); //Gain2
   }
   
    //turn on the NOA1212
    digitalWrite(myPowerPin, HIGH); //power
   
    //need the 10kohm pulldown on the ADC so the NOA1212's output current is converted to a resonable voltage
    pinMode(myInputPin, INPUT_PULLDOWN);

   MqttModule::begin(hub, mod, true);
}

void Noa1212Module::update(void)
{
    float sample = analogRead(myInputPin);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.3V):
    float voltage = sample / 1024.0 * 3.3;
    //convert from voltage to lux
    float lux = voltage;
    if(myGainSetting == HIGH_GAIN)
    {
        lux *= (10000.0 / 51.0);
    }
    else if(myGainSetting == MEDIUM_GAIN)
    {
        lux *= (10000.0 / 4.9);
    }
    else if(myGainSetting == LOW_GAIN)
    {
        lux *= (10000.0 / .54);
    }
    else if(myGainSetting == POWER_DOWN)
    {
        lux = 0.0;
    }
        
    myCurrentRunningAverage += lux/myNumSamples;
    myCurrentSampleCount++;
    
    if(myCurrentSampleCount == myNumSamples)
    {
        myCurrentAveragedValue = myCurrentRunningAverage;
        myCurrentSampleCount = 0;
        myCurrentRunningAverage = 0;
    }
  
    if(millis() > myTick + myUpdateDelay) {
        myTick = millis();
        sendReflectivityValue();
    }
}

void Noa1212Module::sendReflectivityValue()
{
    myHub->sendMessage((const char*)myModule, "LIGHT", myCurrentAveragedValue);	
}

uint8_t Noa1212Module::decode(const char* topic, const char* payload)
{
  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
	  return 0;
  }
  
  if(compare_token(&topic[j],"STATUS")) {
    sendReflectivityValue();
    return 1;
  }
}



