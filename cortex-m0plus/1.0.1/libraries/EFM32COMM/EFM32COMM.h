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

//extern INTRClass INTR;
extern UARTClass Serial;
//extern AnalogLP Analog;

class TwoWire;

// --------------------------------- Basic JSON Communication Class -------------------------

#define MODULE_TABLE_ENTRIES    8
#define MODULE_STRING_LENGTH   40
#define COMM_STRING_LENGTH    253
#define ITEM_TOKEN_LENGTH      24
#define ITEM_PAYLOAD_LENGTH    32
#define NUMBER_ELEMENTS         3
#define ITEM_TYPE               0
#define ITEM_ID                 1
#define ITEM_ACTION             2

enum giState {
  Idle,
  gettingLine,
};

class MQTTBaseHandler;

class EFM32COMMClass
{
 public:
  uint8_t* topic;
  uint8_t* payload;
  EFM32COMMClass();
  int8_t decode(void);
  int8_t add_module(uint8_t*, void (*cmd)(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*));
  int8_t compare_token(uint8_t* inTok, const char* cmpTok);
  
  template <typename T> 
  void  sendMessage(const char* mod, const char* subTop, T payload);
  void  subscribe(const char* mod);
  
  void registerModule(MQTTBaseHandler *module);
  
  void update();
  
  uint32_t subscribe_heartbeat;
  
  
  
 private:
  int8_t getInputString(char);
  int8_t substrcmp(uint8_t* str, uint8_t* sub, uint8_t start);
  int8_t parseLine(void);
  uint8_t inputString[COMM_STRING_LENGTH+3];
  void addCharToInputString(char c);
  int8_t getToken(uint8_t* str, uint8_t* item, uint8_t tok_length);
  uint8_t item_topic[MODULE_STRING_LENGTH];
  uint8_t item_payload[ITEM_PAYLOAD_LENGTH];
  uint8_t isCnt;
  uint8_t charCnt;
  giState state;
  uint32_t myHeatbeatTick;
  MQTTBaseHandler *myRootModule;
  
  
};

extern EFM32COMMClass COMM;

	
class MQTTBaseHandler
{
	
  friend class EFM32COMMClass;
  
 public:
  
  virtual void begin(const char* module, bool subOnHeartbeat = true);
  virtual void update(void);
  virtual uint8_t decode(void);
 protected:
  virtual uint8_t isTopicThisModule();
  const char* myModule;
  bool mySubOnHeartbeat;
  uint32_t myTick;
  MQTTBaseHandler* myNextHandler;
};

	
// ------------------------------- On/Off Control Class -------------------------

class onOffCtlClass : public MQTTBaseHandler
{
 public:
  virtual void begin(uint8_t _pin, const char* module, uint8_t active);
  virtual uint8_t decode(void);
  virtual void setPinState(uint8_t _on);
 private:
  uint32_t myPin;
  uint8_t myActive;
  uint8_t myOn;
  uint8_t myOff;
};

// --------------------------------- Detector Switch Class -------------------------

class detectorSwitchClass : public MQTTBaseHandler
{
 public:
  virtual void  begin(uint8_t _pin, const char* module, uint8_t bounceCount);
  virtual void  update(void); // publish changes in switch state
  virtual uint8_t decode(void);
 protected:
  void switchMsg(uint8_t currentSwitch);
  uint32_t myPin;  // connector pin connected to switch
  uint8_t myEventInProgress; // switch event in progress
  uint32_t mySwitchState;
  uint8_t myBounceCnt; // bounce filter value, 0 = no filter, 0xff = momentary
  
};


// ------------------------------- Momentary Switch Class -------------------------

class momentarySwitchClass : public MQTTBaseHandler
{
 public:
  virtual void begin(uint8_t _pin, const char* module, uint8_t bounceCount);
  virtual void update(void); // publish changes in switch state
 private:
  uint32_t myPin;  // connector pin connected to switch
  uint8_t myEventInProgress; // switch event in progress
  uint8_t myBounceCnt; // bounce filter value, 0 = no filter, 0xff = momentary
};




// ------------------------------- i2cSingleRegisterClass -------------------------

class i2cSingleRegisterClass : public MQTTBaseHandler
{
 public:
  virtual void begin(const char* mod, TwoWire *_wire, uint32_t _enablePin, uint8_t _address, uint8_t _registerToRead, uint32_t _dataSize, uint32_t _updateDelay);
  virtual void update(void); // publish changes in switch state
  virtual uint8_t decode(void);
  
 protected:
  
  virtual void requestI2CData();
  virtual void sendMQTTData();
  
  TwoWire *myWire;
  uint8_t myAddress; 
  uint8_t myDataSize; 
  uint8_t myReadRegister;
  uint32_t myUpdateDelay;
};

class tmp102Class : public i2cSingleRegisterClass
{
	public:
		virtual void begin(const char* mode, TwoWire *_wire, uint32_t _enablePin, uint32_t _updateDelay);
	protected:
		virtual void sendMQTTData();
	
};




#if 0





// ------------------------------- Tone Control Class -------------------------

class toneCtlClass
{
 public:
  void begin(uint8_t _pin, const char* module);
  void update(void);
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t tick_5s;
  uint32_t pin;
  uint32_t tone_freq;
  uint32_t tone_duration;
  uint32_t tone_state;
  TimersLP Timer;
};

// ------------------------------- ADC Pin Class -------------------------

class adcCtlClass
{
 public:
  void begin(uint8_t _pin, const char* module, uint32_t interval);
  void update(void);
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t current;
  uint32_t interval;
  uint32_t pin;
  void publishADCvoltage(void);
};

// ------------------------------- CPU VDD ADC Class -------------------------

class cpuVDDClass
{
 public:
  void begin(const char* module, uint32_t interval);
  void update(void);
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t current;
  uint32_t interval;
  void publishCPUvoltage(void);
};

// ------------------------------- CPU Temperature Class -------------------------

class cpuTempClass
{
 public:
  void begin(const char* module, uint32_t Finterval, uint32_t Cinterval);
  void update(void);
  void decode(void);
 private:
  uint8_t* module;
  uint32_t tick;
  uint32_t currentF;
  uint32_t currentC;
  uint32_t intervalF;
  uint32_t intervalC;
  void publishCPUtempC(void);
  void publishCPUtempF(void);
};



#endif