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

#include "MqttModule.h"

#include "efm_lib/analog.h"

#include <Arduino.h>

#include <Device.h>

extern INTRClass INTR;
extern AnalogLP  Analog;
	
void MqttModule::begin(MqttHub &hub, const char* module, bool subOnHeartbeat)
{
  myHub = &hub;
  myModule = module;
  mySubOnHeartbeat = subOnHeartbeat;
  myTick = 0;
  myNextModule = 0;
  hub.registerModule(this);
  hub.subscribe((const char*)myModule);
}

void MqttModule::update(void)
{

}

uint8_t MqttModule::decode(const char* topic, const char* payload)
{
   return 0;
}

uint8_t MqttModule::isTopicThisModule(const char* topic)
{
  int8_t j = 0;
  int8_t mlen = strlen((char*)myModule);
  int8_t tlen = strlen((char*)topic);
  if((tlen < mlen) || (topic[mlen] != '/')) {
    return 0;
  }
  
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(topic[j] != myModule[i]) {
      return 0;
    }
  }
  return j+1;
}

int8_t MqttModule::compare_token(const char* inTok, const char* cmpTok)
{
  int8_t iLen = strlen((char*)inTok);
  int8_t cLen = strlen((char*) cmpTok);
  if(iLen < cLen) {
    return 0;
  }
  for(int i = 0; i < cLen; i++) {
    if(inTok[i] != cmpTok[i]) {
      return 0;
    }
  }
  return 1;
}
uint8_t MqttModule::isTopicThisModuleWildcard(const char* topic)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t mlen = strlen((char*)myModule);
    uint8_t tlen = strlen((char*)topic);
        
    bool wildCardActive = false;
    bool lastCharWasDelim = false;
    
    if(myModule[i] == '+')
    {
        wildCardActive = true;
        i++;
    }
    
    // compare module
    for(j = 0; i < mlen && j < tlen; j++) {
      if(!wildCardActive)
      {
          if(myModule[i] == '+' && lastCharWasDelim)
          {
              wildCardActive = true;
          }
          else if(topic[j] != myModule[i]) 
          {
            return 0;
          }
          
          if(topic[j] == '/')
          {
              lastCharWasDelim = true;
          }
          else
          {
              lastCharWasDelim = false;
          }
          
          i++;
      }
      else
      {
          if(myModule[i] != '/') 
          {
              //Invaild use of '+' character in module name
              return 0;
          }
          else
          {
            if(topic[j] == '/' && myModule[i] == '/')
            {
              wildCardActive = false;
              lastCharWasDelim = true;
               i++;
            }
          }
      }
    }
    if(wildCardActive)
    {
        return 0;
    }

    return j+1;
}

// ------------------------------- Simple Module Class ------------------------
void SimpleMqttModule::begin(MqttHub &hub, Device &device, const char* mod, uint32_t updateDelay)
{    
    myDevice = &device;
    myUpdateDelay = updateDelay;

    MqttModule::begin(hub, mod, true);

    sendMQTTData();
}

void SimpleMqttModule::update(void)
{
  myDevice->update();
  if(millis() > myTick + myUpdateDelay) {
    myTick = millis();
    sendMQTTData();
  }
}

uint8_t SimpleMqttModule::decode(const char* topic, const char* payload)
{
  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
	  return 0;
  }
  
  if(myDevice->writeValue(&topic[j], payload))
  {
     return 1; 
  }
  
  if(compare_token(&topic[j],"CTL") && compare_token(payload,"STATUS")) {
    sendMQTTData();
    return 1;
  }
}

void SimpleMqttModule::sendMQTTData()
{
    for(int i = 0; i < myDevice->numValues(); i++)
    {
        Device::ValueStruct valueStruct = myDevice->readValue(i);
        switch(valueStruct.type)
        {
            case Device::TypeFloat:
                myHub->sendMessage((const char*)myModule, (const char*)valueStruct.name, valueStruct.value.decimal);
                break;
            case Device::TypeInt:
                myHub->sendMessage((const char*)myModule, (const char*)valueStruct.name, valueStruct.value.integer);
                break;
            case Device::TypeBool:
                myHub->sendMessage((const char*)myModule, (const char*)valueStruct.name, valueStruct.value.boolean);
                break;
            case Device::TypeCharArray:
                myHub->sendMessage((const char*)myModule, (const char*)valueStruct.name, valueStruct.value.charArray);
                break;
        }  
    }
}

void MessageInputStringModule::begin(MqttHub &hub, const char* module, const char* control)
{
    MqttModule::begin(hub, module, true);

    myControl = control;
    myInputString[0] = '\0';
    myNewData = false;
}

uint8_t MessageInputStringModule::decode(const char* topic, const char* payload)
{
      int8_t j = isTopicThisModule(topic);
      if(j == 0)
      {
        return 0;
      }  
      
      if(compare_token(&topic[j],myControl)) {
          int i = 0;
          for(i = 0; i < maxStringSize - 1 && payload[i] != '\0'; i++)
          {
              myInputString[i] = payload[i];
          }
          myInputString[i] = '\0';
          myNewData = true;
          return 1;
      }
}

const char *MessageInputStringModule::getInputString(void)
{
    myNewData = false;
    return myInputString;
}

bool MessageInputStringModule::hasNewData()
{
    return myNewData;
}

uint8_t MessageInputStringModule::isTopicThisModule(const char* topic)
{
    return isTopicThisModuleWildcard(topic);
}

// ------------------------------- Notification Class --------------------------
void NotificationModule::begin(MqttHub &hub, const char* mod, const char* control, const char* payload)
{
  MqttModule::begin(hub, mod, true);

  myControl = control;
  myPayload = payload;
  myState = 0;
}

uint8_t NotificationModule::decode(const char* topic, const char* payload)
{
  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
    return 0;
  }  
  
  if(compare_token(&topic[j],myControl)) {
    if(compare_token(payload,myPayload)) {
      myState = 1;
    } else {return 0;}
    return 1;
  }
}

uint8_t NotificationModule::getState(void)
{
  if(myState) {
    myState = 0;
    return 1;
  } else {
    return 0;
  }
}


// ------------------------------- On/Off Control Class --------------------------
void OnOffCtlModule::begin(MqttHub &hub, uint8_t pin, const char* mod, uint8_t act)
{
	
  static const char *onoff[]   = {"OFF","ON"};

  myPin = pin;
  myActive = act;
  if(myActive == HIGH) {
    myOn = HIGH;
    myOff = LOW;
  } else {
    myOn = LOW;
    myOff = HIGH;
  }

  pinMode(myPin, OUTPUT);       // LED

  MqttModule::begin(hub, mod, true);
  
  uint8_t val = (myActive == HIGH) ? digitalRead(myPin) : ~digitalRead(myPin);
  myHub->sendMessage((const char*)myModule, "SWITCH", onoff[val & 0x01]);
	  
}

uint8_t OnOffCtlModule::decode(const char* topic, const char* payload)
{
  static const char *onoff[] = {"OFF","ON"};

  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
    return 0;
  }  
  
  if(compare_token(&topic[j],"CTL")) {
    if(compare_token(payload,"ON")) {
      setPinState(HIGH);
    } else if(compare_token(payload,"OFF")) {
      setPinState(LOW);
    } else if(compare_token(payload,"STATUS")) {
      uint8_t val = (myActive == HIGH) ? digitalRead(myPin) : ~digitalRead(myPin);
      myHub->sendMessage((const char*)myModule, "SWITCH", onoff[val & 0x01]);
    } else {return 0;}
    return 1;
  }
}

void OnOffCtlModule::setPinState(uint8_t on)
{
	static const char *onoff[]   = {"OFF","ON"};
	
	//Set the state of the pin
	if(on == HIGH)
	{
		digitalWrite(myPin, myOn);
	}
	else
	{
		digitalWrite(myPin, myOff);
	}
	
	//send the current state to any subscribers
	uint8_t val = (myActive == HIGH) ? digitalRead(myPin) : !digitalRead(myPin);
   myHub->sendMessage((const char*)myModule, "SWITCH", onoff[val & 0x01]);
}

uint8_t OnOffCtlModule::pinState()
{
	uint8_t val = (myActive == HIGH) ? digitalRead(myPin) : !digitalRead(myPin);
	return val;
}



// ------------------------------- Detector Switch Class -------------------------
void DetectorSwitchModule::begin(MqttHub &hub, uint8_t pin, const char* mod, uint8_t bounceCount)
{
	
  myPin = pin;
  myBounceCnt = bounceCount;
  pinMode(pin, INPUT_PU_FILTER);
  mySwitchState = (~digitalRead(pin) & 0x01);
  myEventInProgress = 0;
  
  MqttModule::begin(hub, mod, true);
  
  switchMsg(mySwitchState);
  
}

void DetectorSwitchModule::update(void)
{
  if(millis() > myTick + 100) {
    myTick = millis();
    uint8_t currentSwitch = (~digitalRead(myPin) & 0x01);

    if((myEventInProgress == 0) && (mySwitchState != currentSwitch) ) { // switch event happened
        myEventInProgress = 1;
	} else if(mySwitchState == currentSwitch)// not really an event
	{
		myEventInProgress = 0;
    } else if((myEventInProgress > 0) && (myEventInProgress < myBounceCnt)) { // wait until bounce count
      myEventInProgress++;
    } else if(myEventInProgress >= myBounceCnt) { // report event
		mySwitchState = currentSwitch;
		switchMsg(currentSwitch);
    }
  }
}

uint8_t DetectorSwitchModule::decode(const char* topic, const char* payload)
{
  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
	  return 0;
  }
  
  if(compare_token(&topic[j],"STATUS")) {
    switchMsg(mySwitchState);
    return 1;
  }
}

void DetectorSwitchModule::switchMsg(uint8_t currentSwitch)
{
	
   if(currentSwitch)
   {
	   myHub->sendMessage((const char*)myModule, "SWITCH", "CLOSED");
   }
   else
   {
	   myHub->sendMessage((const char*)myModule, "SWITCH", "OPEN");
   }
	   
}

uint32_t DetectorSwitchModule::switchState(void)
{
	return mySwitchState;
}

// ------------------------------- Momentary Switch Class ------------------------
void MomentarySwitchModule::begin(MqttHub &hub, uint8_t pin, const char* mod, uint8_t bounceCount)
{
	
  myPin = pin;
  myBounceCnt = bounceCount;
  pinMode(pin, INPUT_PU_FILTER);
  myEventInProgress = 0;
  
  INTR.attachIntrCounter(pin, RISING);
  
  MqttModule::begin(hub, mod, true);
	
}

void MomentarySwitchModule::update(void)
{
  if(millis() > myTick + 10) {
    myTick = millis();
    uint8_t swInt = INTR.read_clr_nints(myPin);

	uint8_t currentSwitch = (digitalRead(myPin) & 0x01);
		
    if((myEventInProgress == 0) && (swInt > 0)) { // switch event happened
      myEventInProgress = 1;
    } else if((myEventInProgress > 0) && (myEventInProgress < myBounceCnt)) { // wait until bounce count
      myEventInProgress++;
    } else if(myEventInProgress >= myBounceCnt) { // report event	 
		if(currentSwitch == HIGH) //Check to see if the pin is still high, debounces the signal
		{	
			myHub->sendMessage((const char*)myModule, "SWITCH", "CLOSED");
	    }
		myEventInProgress = 0;
	}
     
  }
}

// ------------------------------- ADC Pin Class ---------------------------------

void AdcCtlModule::begin(MqttHub &hub, uint8_t adcPin, const char* mod, uint32_t interval)
{
  myAdcPin = adcPin;
  myInterval = interval;
  myCurrent = 0;
  
  MqttModule::begin(hub, mod, true);
}

void AdcCtlModule::update(void)
{
  if(millis() > myTick + 100) {
    myTick = millis();
    if(myInterval != 0) {
      if(myCurrent <= 0) {
         myCurrent = myInterval;
         publishADCvoltage();
      } else {
         myCurrent--;
      }
    }
  }
}

void AdcCtlModule::publishADCvoltage(void)
{
#if defined(ADC_COUNT)
  uint32_t r = Analog.analogReadVDDsample();
  Analog.analogReference(INTERNALVDD);
  Analog.analogReadResolution(RES_12BITS);
  uint32_t v = Analog.analogReadPin(myAdcPin);
  uint32_t mV =  ((v * r)/4096);
  myHub->sendMessage((const char*)myModule, "ADC", ((float)mV / 1000.0f));
#endif 

}

uint8_t AdcCtlModule::decode(const char* topic, const char* payload)
{
  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
	  return 0;
  }
  
  if(compare_token(&topic[j],"ADC")) {
    publishADCvoltage();
    return 1;
  }
  
}




// ------------------------------- Tone Control Class ----------------------------

void ToneCtlModule::begin(MqttHub &hub, uint8_t pin, const char* mod)
{
  myPin = pin;
  
  pinMode(myPin, OUTPUT);       // LED

  myToneFreq     = 1000;
  myToneDuration = 0;
  myToneState    = 0;

  MqttModule::begin(hub, mod, true);
    
}


uint8_t ToneCtlModule::decode(const char* topic, const char* payload)
{

  static const char *onoff[]   = {"OFF","ON"};

  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
    return 0;
  }  
  
  if(compare_token(&topic[j],"TONE")) {
    if(compare_token(payload,"ON")) {
	  myTimer.noTone(myPin);
      myTimer.tone(myPin, myToneFreq, myToneDuration);
      myToneState = 1;
    } else if(compare_token(payload,"OFF")) {
      myTimer.noTone(myPin);
      myToneState = 0;
    } else if(compare_token(payload,"F")) {
      uint32_t f = atoi((char*)&payload[1]);
      if(f < 20000) {
         myToneFreq = f;
      }
    } else if(compare_token(payload,"D")) {
      myToneDuration = atoi((char*)&payload[1]);
    } else if(compare_token(payload,"STATUS")) {
      myHub->sendMessage((const char*)myModule, "TONE", onoff[myToneState]);
    } else {return 0;}
    return 1;
  }
	
}
