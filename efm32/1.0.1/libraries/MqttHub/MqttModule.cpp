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
  
  if(compare_token(&topic[j],"STATUS")) {
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

// ------------------------------- Momentary Switch Class ------------------------
void DigitalQre1113SwitchModule::begin(MqttHub &hub, uint8_t pin, const char* module, uint8_t bounceCount, uint32_t enablePin, uint32_t onThreshold)
{
  
  myPin = pin;
  myBounceCnt = bounceCount;
  pinMode(pin, INPUT);
  myEventInProgress = 0;
  myOnThreshold = onThreshold;
  
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
  
  
  MqttModule::begin(hub, module, true);
	
}

uint8_t DigitalQre1113SwitchModule::readPin()
{
	//Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  pinMode( myPin, OUTPUT );
  digitalWrite( myPin, HIGH );  
  
  //delay(1);
  delayMicroseconds(10);
  
  pinMode( myPin, INPUT );

  long time = micros();
  
  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (digitalRead(myPin) == HIGH && micros() - time < 3000); 
  
  int diff = micros() - time;
  
  if(diff > myOnThreshold)
  {
	  return 0;
  }else
  {
	  return 1;
  }
  
  
}

void DigitalQre1113SwitchModule::update(void)
{
  if(millis() > myTick + 10) {
    myTick = millis();

	uint8_t currentSwitch = readPin();
		
    if((myEventInProgress == 0) && (currentSwitch == HIGH)) { // switch event happened
      myEventInProgress = 1;
    } else if((myEventInProgress > 0) && (myEventInProgress < myBounceCnt) && (currentSwitch == HIGH)) { // wait until bounce count
      myEventInProgress++;
    } else if(myEventInProgress >= myBounceCnt && (currentSwitch == LOW) ) { // report event	 
			
		myHub->sendMessage((const char*)myModule, "SWITCH", "CLOSED");
	    
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
