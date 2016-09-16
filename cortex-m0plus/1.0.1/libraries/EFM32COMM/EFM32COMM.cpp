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

#include "EFM32COMM.h"
#include "efm_lib/analog.h"


#include <Arduino.h>
#include <Wire.h>

extern UARTClass Serial;
extern UARTClass Serial1;
extern INTRClass INTR;
extern AnalogLP  Analog;

// --------------------------------- Basic JSON Communication Class -------------------------

EFM32COMMClass::EFM32COMMClass()
{
  topic   = &item_topic[0];
  payload = &item_payload[0];
  isCnt = 0;
  charCnt = 0;
  state = Idle;
  subscribe_heartbeat = 30000; //30 second heartbeat
  myHeatbeatTick = 0;
  myRootModule = 0;
  
}

int8_t EFM32COMMClass::decode(void)
{
  if (Serial.available()) {
    char c = (char)Serial.read(); // get the new byte:
    if(isgraph(c)) {
      //Serial.print(c);
      return getInputString(c);
    } else {
      return 0;
    }
  }
  return 0;
}

int8_t EFM32COMMClass::getInputString(char c)
{
  if(c == '{') {
    state = gettingLine;
    isCnt = 0;
    addCharToInputString(c);
    return 0;
  } else if(state != Idle) {
    if(c == '}') {
      state = Idle;
      addCharToInputString(c);
      addCharToInputString('\r');
      addCharToInputString('\n');
      addCharToInputString('\0');
	  
      int8_t r = parseLine();
      inputString[0]  = '\0';
      isCnt = 0;
      return r;
    } else {
      addCharToInputString(c);
      return 0;
    }
  }
  return 0;
}

void EFM32COMMClass::addCharToInputString(char c)
{
  //  Serial.printf("isCnt = %d c = %c\r\n",isCnt,c);
  inputString[isCnt++] = c;
  if(isCnt >= COMM_STRING_LENGTH) {
    isCnt = 0;
    state = Idle;
  }
}


int8_t EFM32COMMClass::parseLine(void)
{
  static uint8_t debug = 0;

  item_topic[0]   = '\0';
  item_payload[0] = '\0';

  int8_t r = 0;

  for(isCnt = 0; inputString[isCnt] != '\0'; isCnt++) {
    uint8_t* c = &inputString[isCnt];
    if( ((c[0] == '{') || (c[0] == ',')) && (c[1] == '\"')) {
      if((c[2] == 'T') && (c[3] == 'O') && (c[4] == 'P')) {
	r = getToken(&c[5], item_topic, MODULE_STRING_LENGTH);
	if(debug) {Serial1.printf("TOP = %s\r\n", item_topic);}
      }
      if((c[2] == 'P') && (c[3] == 'L') && (c[4] == 'D')) {
	r += getToken(&c[5], item_payload, ITEM_PAYLOAD_LENGTH);
	if(debug) {Serial1.printf("PLD = %s\r\n", item_payload);}
      }
    }
  }
  if(debug) {Serial1.printf("topic   = %s\r\n", topic);}
  if(debug) {Serial1.printf("payload = %s\r\n\r\n", payload);}
   if(debug) {Serial1.println(r);}
  return r;
}

int8_t EFM32COMMClass::getToken(uint8_t* str, uint8_t* item, uint8_t tok_length)
{
  uint8_t i;

  if((str[0] == '\"') && (str[1] == ':') && (str[2] == '\"')) {
    for(i = 3; (i < tok_length) && (str[i] != '\"') && (str[i] != '\0'); i++) {
      item[i-3] = str[i];
    }
    item[i-3] = '\0';
    return 1;
  } else {
    return 0;
  }
}

int8_t EFM32COMMClass::compare_token(uint8_t* inTok, const char* cmpTok)
{
  int8_t iLen = strlen((char*) inTok);
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

template <typename T> 
void EFM32COMMClass::sendMessage(const char* mod, const char* subTop, T payload)
{
    Serial.print("{\"TOP\":\"");
	Serial.print(mod);
	Serial.print("?/");
	Serial.print(subTop);
	Serial.print("\",\"PLD\":\"");
	Serial.print(payload);
	Serial.print("\"}\r\n");
}

void EFM32COMMClass::subscribe(const char* mod)
{
	
	Serial.print("{\"TOP\":\"");
	Serial.print((const char*)mod);
	Serial.print("/#\",\"PLD\":\"SUB\"}\r\n");
}

void EFM32COMMClass::registerModule(MQTTBaseHandler *module)
{
	module->myNextHandler = myRootModule;
	myRootModule = module;
}

void EFM32COMMClass::update()
{
	MQTTBaseHandler *curHandler;
	if(decode())
	{
		curHandler = myRootModule;
		while(curHandler)
		{
			if(curHandler->decode())
			{
				curHandler = 0;
			}else
			{
				curHandler = curHandler->myNextHandler;
			}
		}
	}
	
	curHandler = myRootModule;
	while(curHandler)
	{
		curHandler->update();
		
		curHandler = curHandler->myNextHandler;
	}
		
		
	if(millis() > myHeatbeatTick + subscribe_heartbeat)
	{
		myHeatbeatTick = millis();
		curHandler = myRootModule;
		while(curHandler)
		{
			if(curHandler->mySubOnHeartbeat)
			{
				subscribe(curHandler->myModule);	
			}
			curHandler = curHandler->myNextHandler;
		}
	}
		
		
	
}


EFM32COMMClass COMM;


	
void MQTTBaseHandler::begin(const char* module, bool subOnHeartbeat)
{
  myModule = module;
  COMM.registerModule(this);
  COMM.subscribe((const char*)myModule);
  mySubOnHeartbeat  = subOnHeartbeat;
  myTick = 0;
}

void MQTTBaseHandler::update(void)
{

}

uint8_t MQTTBaseHandler::decode(void)
{
		return 0;
}

uint8_t MQTTBaseHandler::isTopicThisModule()
{
  int8_t j = 0;
  int8_t mlen = strlen((char*)myModule);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return 0;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != myModule[i]) {
      return 0;
    }
  }
  return j+1;
}

// ------------------------------- On/Off Control Class --------------------------

void onOffCtlClass::begin(uint8_t _pin, const char* mod, uint8_t act)
{
	
   static const char *onoff[]   = {"OFF","ON"};

  myPin = _pin;
  myActive = act;
  if(myActive == HIGH) {
    myOn = HIGH;
    myOff = LOW;
  } else {
    myOn = LOW;
    myOff = HIGH;
  }

  pinMode(myPin, OUTPUT);       // LED

  MQTTBaseHandler::begin(mod, true);
  
  uint8_t val = (myActive == HIGH) ? digitalRead(myPin) : ~digitalRead(myPin);
  COMM.sendMessage((const char*)myModule, "LED", onoff[val & 0x01]);
	  
}

uint8_t onOffCtlClass::decode(void)
{
  static const char *onoff[]   = {"OFF","ON"};

  int8_t j = isTopicThisModule();
  if(j == 0)
    {
      return 0;
    }  
  
  if(COMM.compare_token(&COMM.topic[j],"CTL")) {
    if(COMM.compare_token(COMM.payload,"ON")) {
      setPinState(HIGH);
    } else if(COMM.compare_token(COMM.payload,"OFF")) {
      setPinState(LOW);
    } else if(COMM.compare_token(COMM.payload,"STATUS")) {
      uint8_t val = (myActive == HIGH) ? digitalRead(myPin) : ~digitalRead(myPin);
      COMM.sendMessage((const char*)myModule, "LED", onoff[val & 0x01]);
    } else {return 0;}
    return 1;
  }
}

void onOffCtlClass::setPinState(uint8_t on)
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
	uint8_t val = (myActive == HIGH) ? digitalRead(myPin) : ~digitalRead(myPin);
    COMM.sendMessage((const char*)myModule, "LED", onoff[val & 0x01]);
}

uint8_t onOffCtlClass::pinState()
{
	uint8_t val = (myActive == HIGH) ? digitalRead(myPin) : ~digitalRead(myPin);
	return val;
}



// ------------------------------- Detector Switch Class -------------------------
void detectorSwitchClass::begin(uint8_t _pin, const char* mod, uint8_t bounceCount)
{
	
  myPin = _pin;
  myBounceCnt = bounceCount;
  pinMode(_pin, INPUT_PU_FILTER);
  mySwitchState = (~digitalRead(_pin) & 0x01);
  myEventInProgress = 0;
  
  MQTTBaseHandler::begin(mod, true);
  
  switchMsg(mySwitchState);
  
}

void detectorSwitchClass::update(void)
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

uint8_t detectorSwitchClass::decode(void)
{
  int8_t j = isTopicThisModule();
  if(j == 0)
  {
	  return 0;
  }
  
  if(COMM.compare_token(&COMM.topic[j],"SWITCH")) {
    switchMsg(mySwitchState);
    return 1;
  }
}

void detectorSwitchClass::switchMsg(uint8_t currentSwitch)
{
	
   if(currentSwitch)
   {
	   COMM.sendMessage((const char*)myModule, "SWITCH", "CLOSED");
   }
   else
   {
	   COMM.sendMessage((const char*)myModule, "SWITCH", "OPEN");
   }
	   
}

uint32_t detectorSwitchClass::switchState(void)
{
	return mySwitchState;
}

// ------------------------------- Momentary Switch Class ------------------------
void momentarySwitchClass::begin(uint8_t _pin, const char* mod, uint8_t bounceCount)
{
	
  myPin = _pin;
  myBounceCnt = bounceCount;
  pinMode(_pin, INPUT_PU_FILTER);
  myEventInProgress = 0;
  
  INTR.attachIntrCounter(_pin, RISING);
  
  MQTTBaseHandler::begin(mod, true);
	
}

void momentarySwitchClass::update(void)
{
  if(millis() > myTick + 10) {
    myTick = millis();
    uint8_t sw_int = INTR.read_clr_nints(myPin);

	uint8_t currentSwitch = (digitalRead(myPin) & 0x01);
		
    if((myEventInProgress == 0) && (sw_int > 0)) { // switch event happened
      myEventInProgress = 1;
    } else if((myEventInProgress > 0) && (myEventInProgress < myBounceCnt)) { // wait until bounce count
      myEventInProgress++;
    } else if(myEventInProgress >= myBounceCnt) { // report event	 
		if(currentSwitch == HIGH) //Check to see if the pin is still high, debounces the signal
		{	
			COMM.sendMessage((const char*)myModule, "SWITCH", "CLOSED");
	    }
		myEventInProgress = 0;
	}
     
  }
}

// ------------------------------- i2cSingleRegisterClass -------------------------
void i2cSingleRegisterClass::begin(const char* mod, TwoWire *_wire, int32_t _enablePin, uint8_t _address, uint8_t _registerToRead, uint32_t _dataSize, uint32_t _updateDelay)
{
  if(_enablePin > 0)
  {
	pinMode(_enablePin, OUTPUT);
	digitalWrite(_enablePin, HIGH);
  }
  
  myAddress = _address;
  myDataSize = _dataSize;
  myUpdateDelay = _updateDelay;
  myWire = _wire;
  _wire->begin();
  myReadRegister = _registerToRead;
  
  MQTTBaseHandler::begin(mod, true);
  
  //give the slave a slight delay so it can turn on.
  delay(50);
  requestI2CData();
  sendMQTTData();
  
}

void i2cSingleRegisterClass::update(void)
{
  if(millis() > myTick + myUpdateDelay) {
    myTick = millis();
    requestI2CData();
    sendMQTTData();
  }
}

uint8_t i2cSingleRegisterClass::decode(void)
{
  int8_t j = isTopicThisModule();
  if(j == 0)
  {
	  return 0;
  }
  
  if(COMM.compare_token(&COMM.topic[j],"STATUS")) {
    requestI2CData();
    sendMQTTData();
    return 1;
  }
}

void i2cSingleRegisterClass::requestI2CData()
{
	 //read register 0 from the I2C slave
  myWire->beginTransmission(myAddress);
  myWire->write(myReadRegister);//register address
  myWire->requestFrom(myAddress, myDataSize); //read 2 bytes
  myWire->endTransmission();
}

void i2cSingleRegisterClass::sendMQTTData()
{
	//by default don't send anything but read the wire result
	for(int i = 0; i < myDataSize; i++)
	{
		byte b = myWire->read();
	}
}

void tmp102Class::begin(const char* mod, TwoWire *_wire, int32_t _enablePin, uint32_t _updateDelay)
{
	i2cSingleRegisterClass::begin(mod, _wire, _enablePin, 0x48, 0x00, 2, _updateDelay);
}
	
void tmp102Class::sendMQTTData()
{
	byte msb = myWire->read(); 
	byte lsb = myWire->read(); 
	int temp = ((msb << 8) | lsb) >> 4;
	float degc = temp/16.0f;
	COMM.sendMessage((const char*)myModule, "DEG_C", degc);
	
}

// ------------------------------- CPU VDD ADC Class -----------------------------

void cpuVDDClass::begin(const char* mod, uint32_t intrval)
{
  module = (uint8_t*)mod;
  interval = intrval;

  MQTTBaseHandler::begin(mod, true);

  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
}

void cpuVDDClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    if(interval != 0) {
      if(current <= 0) {
	current = interval;
	publishCPUvoltage();
      } else {
	current--;
      }
    }
  }
}

void cpuVDDClass::publishCPUvoltage(void)
{
  uPvdd vddval = Analog.analogReadVDD();
  Serial.printf("{\"TOP\":\"%s?/ADC\",\"PLD\":\"%d.%d\"}\r\n",module, vddval.wholeVDD, vddval.fracVDD);
}

uint8_t cpuVDDClass::decode(void)
{
  int8_t j = isTopicThisModule();
  if(j == 0) {
    return 0;
  }

  if(COMM.compare_token(&COMM.topic[j],"VDD")) {
    publishCPUvoltage();
  } else {return 0;}
  return 1;
}



// ------------------------------- CPU Temperature Class -------------------------


void cpuTempClass::begin(const char* mod, uint32_t Fintrval, uint32_t Cintrval)
{
  module = (uint8_t*)mod;
  intervalF = Fintrval;
  intervalC = Cintrval;

  MQTTBaseHandler::begin(mod, true);

  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
}

void cpuTempClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    if(intervalC != 0) {
      if(currentC <= 0) {
	currentC = intervalC;
	publishCPUtempC();
      } else {
	currentC--;
      }
    }
    if(intervalF != 0) {
      if(currentF <= 0) {
	currentF = intervalF;
	publishCPUtempF();
      } else {
	currentF--;
      }
    }
  }
}

void cpuTempClass::publishCPUtempC(void)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("{\"TOP\":\"%s?/TMPC\",\"PLD\":\"%d.%d\"}\r\n",module, tempval.wholeC, tempval.fracC);
}

void cpuTempClass::publishCPUtempF(void)
{
  temperature tempval = Analog.analogReadTemp();
  Serial.printf("{\"TOP\":\"%s?/TMPF\",\"PLD\":\"%d.%d\"}\r\n",module, tempval.wholeF, tempval.fracF);
}

uint8_t cpuTempClass::decode(void)
{
  int8_t j = isTopicThisModule();
  if(j == 0) {
    return 0;
  }

  if(COMM.compare_token(&COMM.topic[j],"TMPC")) {
    publishCPUtempC();
  } else if(COMM.compare_token(&COMM.topic[j],"TMPF")) {
    publishCPUtempF();
  } else {return 0;}
  return 1;
}







#if 0

// ------------------------------- Tone Control Class ----------------------------

void toneCtlClass::begin(uint8_t _pin, const char* mod)
{
  pin = _pin;
  module = (uint8_t*)mod;

  pinMode(pin, OUTPUT);       // LED

  tone_freq     = 1000;
  tone_duration = 0;
  tone_state    = 0;

  TimersLP Timer;

  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
  tick_5s = 0;
}

void toneCtlClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    if(tick_5s++ >= COMM.subscribe_heartbeat) { // subscribe every 5s for a heartbeat
      tick_5s = 0;
      Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
    }
  }
}

void toneCtlClass::decode(void)
{
  if(COMM.decode_done) {return;}
  static const char *onoff[]   = {"OFF","ON"};

  int8_t j = 0;
  int8_t mlen = strlen((char*)module);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != module[i]) {
      return;
    }
  }
  j++;
  if(COMM.compare_token(&COMM.topic[j],"TONE")) {
    if(COMM.compare_token(COMM.payload,"ON")) {
      Timer.noTone(pin);
      Timer.tone(pin, tone_freq, tone_duration);
      tone_state = 1;
    } else if(COMM.compare_token(COMM.payload,"OFF")) {
      Timer.noTone(pin);
      tone_state = 0;
    } else if(COMM.compare_token(COMM.payload,"F")) {
      uint32_t f = atoi((char*)&COMM.payload[1]);
      if(f < 20000) {
	tone_freq = f;
      }
    } else if(COMM.compare_token(COMM.payload,"D")) {
      tone_duration = atoi((char*)&COMM.payload[1]);
    } else if(COMM.compare_token(COMM.payload,"STATUS")) {
      Serial.printf("{\"TOP\":\"%s?/TONE\",\"PLD\":\"%s\"}\r\n",module, onoff[tone_state]);
    } else {return;}
    COMM.decode_done = 1;
    return;
  }
}

// ------------------------------- ADC Pin Class ---------------------------------

void adcCtlClass::begin(uint8_t _pin, const char* mod, uint32_t intrval)
{
  pin = _pin;
  module = (uint8_t*)mod;
  interval = intrval;

  Serial.printf("{\"TOP\":\"%s/#\",\"PLD\":\"SUB\"}\r\n",module);
  tick = 0;
}

void adcCtlClass::update(void)
{
  if(millis() > tick + 100) {
    tick = millis();
    if(interval != 0) {
      if(current <= 0) {
	current = interval;
	publishADCvoltage();
      } else {
	current--;
      }
    }
  }
}

void adcCtlClass::publishADCvoltage(void)
{
  uint32_t r = Analog.analogReadVDDsample();
  Analog.analogReference(INTERNALVDD);
  Analog.analogReadResolution(RES_12BITS);
  uint32_t v = Analog.analogReadPin(pin);
  uint32_t mV =  ((v * r)/4096);
  Serial.printf("{\"TOP\":\"%s?/ADC\",\"PLD\":\"%d.%d\"}\n\r",module, mV/1000, mV%1000);
}

void adcCtlClass::decode(void)
{
  if(COMM.decode_done) {return;}

  int8_t j = 0;
  int8_t mlen = strlen((char*)module);
  int8_t tlen = strlen((char*)COMM.topic);
  if((tlen < mlen) || (COMM.topic[mlen] != '/')) {
    return;
  }
  // compare module
  for(int i = 0; i < mlen; i++, j++) {
    if(COMM.topic[j] != module[i]) {
      return;
    }
  }
  j++;
  if(COMM.compare_token(&COMM.topic[j],"ADC")) {
    publishADCvoltage();
    COMM.decode_done = 1;
    return;
  }
}



#endif





