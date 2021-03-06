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

#include <MQ7Device.h>
#include <Arduino.h>

#define HIGH_TIME 60000
#define LOW_TIME 90000

//This value causes the Garage Door PWM controlled relay to output 1.4V
#define LOW_PWM_VALUE 127 

//This value causes the Garage Door PWM controlled relay to output 5V
#define HIGH_PWM_VALUE 255

//If the sensor is higher than this for more than TIME_THRESHOLD then there is a CO problem
#define ALERT_THRESHOLD 950

//For now require 10 seconds above the alert threshold before it reports a CO problem
#define TIME_THRESHOLD 10000


void MQ7Device::begin(int32_t pwmCtlPin, int32_t gasSensorPin)
{    
    pinMode(pwmCtlPin, INPUT);

    myPwmCtlPin = pwmCtlPin;
    pinMode(pwmCtlPin, OUTPUT);
    analogWrite(pwmCtlPin, 255);//turn off the heater for now

    myGasSensorPin = gasSensorPin;

    myAlertState = NO_PROBLEM;

    myState = LOW_HEAT;
    mySwitchStateDelay = millis() + LOW_TIME;
    analogWrite(myPwmCtlPin, LOW_PWM_VALUE); //set to 1.4V
}

void MQ7Device::update(void)
{
    if(millis() > mySwitchStateDelay)
    {
        if(myState == LOW_HEAT)
        {
            myState = HIGH_HEAT;
            mySwitchStateDelay = millis() + HIGH_TIME;
            analogWrite(myPwmCtlPin, HIGH_PWM_VALUE);
        }
        else
        {
            myState = LOW_HEAT;
            mySwitchStateDelay = millis() + LOW_TIME;
            analogWrite(myPwmCtlPin, LOW_PWM_VALUE);
        }
    }
  
    //Check for a change in the current state of the CO level
    int val = analogRead(myGasSensorPin);

    if(myAlertState == NO_PROBLEM && val > ALERT_THRESHOLD)
    {
        myAlertState = POTENTIAL_PROBLEM;
        myAlertInitialTime = millis();
    }
    if(myAlertState == POTENTIAL_PROBLEM && val < ALERT_THRESHOLD)
    {
        myAlertState = NO_PROBLEM;
    }
    if(myAlertState == POTENTIAL_PROBLEM && myAlertInitialTime + TIME_THRESHOLD < millis())
    {
        myAlertState = PROBLEM;
    }
  
    if(myAlertState == PROBLEM  && val < ALERT_THRESHOLD)
    {
        myAlertState = POTENTIAL_RECOVERY;
        myAlertInitialTime = millis();
    }
    if(myAlertState == POTENTIAL_RECOVERY && val > ALERT_THRESHOLD)
    {
        myAlertState = PROBLEM;
    }
    if(myAlertState == POTENTIAL_RECOVERY && myAlertInitialTime + TIME_THRESHOLD < millis())
    {
        myAlertState = NO_PROBLEM;
    }
    myAlertValue = val;

}

uint32_t MQ7Device::currentAlertValue()
{
    return myAlertValue;
}

const char *MQ7Device::currentAlertText()
{
    if(myAlertState == NO_PROBLEM || myAlertState == POTENTIAL_PROBLEM)
    {
        return "LOW";	
    }else if(myAlertState == PROBLEM || myAlertState == POTENTIAL_RECOVERY)
    {
        return "HIGH";	
    }    
    return "LOW";
}

Device::ValueStruct MQ7Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        output.type = Device::TypeInt;
        output.value.integer = myAlertValue;
            
        output.name = "COLEVEL";
    }
    else if(index == 1)
    {
        output.type = Device::TypeCharArray;
        output.value.charArray = currentAlertText();	
        output.name = "COALERT";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

uint32_t MQ7Device::numValues()
{
    return 2; 
}



