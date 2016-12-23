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

 #include "Mq7Module.h"

#include <Arduino.h>

#define HIGH_TIME 60000
#define LOW_TIME 90000

//This value causes the Garage Door PWM controlled relay to output 1.4V
#define LOW_PWM_VALUE 127 

//This value causes the Garage Door PWM controlled relay to output 5V
#define HIGH_PWM_VALUE 255

//If the sensor is higher than this for more than TIME_THRESHOLD then there is a CO2 problem
#define ALERT_THRESHOLD 800

//For now require 10 seconds above the alert threshold before it reports a CO2 problem
#define TIME_THRESHOLD 10000

// ------------------------------- Mq7Module -------------------------
void Mq7Module::begin(MqttHub &hub, const char* mod, int32_t pwmCtlPin, int32_t gasSensorPin,uint32_t updateDelay)
{
   pinMode(pwmCtlPin, INPUT);
   
   myPwmCtlPin = pwmCtlPin;
   pinMode(pwmCtlPin, OUTPUT);
   analogWrite(pwmCtlPin, 255);//turn off the heater for now
  
  myGasSensorPin = gasSensorPin;
 
  myUpdateDelay = updateDelay;
  
  MqttModule::begin(hub, mod, true);
  
  myAlertState = NO_PROBLEM;
  
  myState = LOW_HEAT;
  mySwitchStateDelay = millis() + LOW_TIME;
  analogWrite(myPwmCtlPin, LOW_PWM_VALUE); //set to 1.4V
}

void Mq7Module::update(void)
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

  
    if(millis() > myTick + myUpdateDelay) {
        myTick = millis();
        sendCurCo2State();
    }
}

void Mq7Module::sendCurCo2State()
{
    if(myAlertState == NO_PROBLEM || myAlertState == POTENTIAL_PROBLEM)
    {
        myHub->sendMessage((const char*)myModule, "CO2LEVEL", "LOW");	
    }else if(myAlertState == PROBLEM || myAlertState == POTENTIAL_RECOVERY)
    {
        myHub->sendMessage((const char*)myModule, "CO2LEVEL", "HIGH");	
    }
}

uint8_t Mq7Module::decode(const char* topic, const char* payload)
{
  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
	  return 0;
  }
  
  if(compare_token(&topic[j],"STATUS")) {
    sendCurCo2State();
    return 1;
  }
}



