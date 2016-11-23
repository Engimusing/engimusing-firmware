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
#include "MqttHub.h"

class TwoWire;

//Base class for modules, modules are updated periotically and can handle messages recieved from a port
class MqttModule
{
   
  friend class MqttHub;
  
 public:
  
  virtual void begin(MqttHub &hub, const char* module, bool subOnHeartbeat = true);
  virtual void update(void);
  virtual uint8_t decode(const char* topic, const char* payload);
 
 protected:
  uint8_t isTopicThisModule(const char* topic);
  int8_t compare_token(const char* inTok, const char* cmpTok);

 protected:
  MqttHub *myHub;
  const char* myModule;
  bool mySubOnHeartbeat;
  uint32_t myTick;
  MqttModule* myNextModule;
};

   
// ------------------------------- On/Off Control Class -------------------------

class OnOffCtlModule : public MqttModule
{
 public:
  
  virtual void begin(MqttHub &hub, uint8_t pin, const char* module, uint8_t active);
  virtual uint8_t decode(const char* topic, const char* payload);
  
  virtual void setPinState(uint8_t on);
  virtual uint8_t pinState();
 
 private:
  
  uint32_t myPin;
  uint8_t myActive;
  uint8_t myOn;
  uint8_t myOff;
  
};

// --------------------------------- Detector Switch Class -------------------------

class DetectorSwitchModule : public MqttModule
{
 
 public:
  virtual void  begin(MqttHub &hub, uint8_t pin, const char* module, uint8_t bounceCount);
  virtual void  update(void); // publish changes in switch state
  virtual uint8_t decode(const char* topic, const char* payload);
  virtual uint32_t switchState(void);
 
 protected:
 
  void switchMsg(uint8_t currentSwitch);
  
 protected:
  uint32_t myPin;  // connector pin connected to switch
  uint8_t myEventInProgress; // switch event in progress
  uint32_t mySwitchState;
  uint8_t myBounceCnt; // bounce filter value, 0 = no filter, 0xff = momentary
  
};


// ------------------------------- Momentary Switch Class -------------------------

class MomentarySwitchModule : public MqttModule
{
 
 public:
  virtual void begin(MqttHub &hub, uint8_t pin, const char* module, uint8_t bounceCount);
  virtual void update(void); // publish changes in switch state
 
 private:
  uint32_t myPin;  // connector pin connected to switch
  uint8_t myEventInProgress; // switch event in progress
  uint8_t myBounceCnt; // bounce filter value, 0 = no filter, 0xff = momentary

};

class DigitalQre1113SwitchModule : public MqttModule
{

 public:
  virtual void begin(MqttHub &hub, uint8_t pin, const char* module, uint8_t bounceCount, uint32_t onThreshold = 400);
  virtual uint8_t readPin();
  virtual void update(void); // publish changes in switch state
 
 private:
  uint32_t myOnThreshold;
  uint32_t myPin;  // connector pin connected to switch
  uint8_t myEventInProgress; // switch event in progress
  uint8_t myBounceCnt; // bounce filter value, 0 = no filter, 0xff = momentary

};




// ------------------------------- I2cSingleRegisterModule -------------------------

class I2cSingleRegisterModule : public MqttModule
{
 
 public:
  virtual void begin(MqttHub &hub, const char* mod, TwoWire *wire, int32_t enablePin, uint8_t address, uint8_t registerToRead, uint32_t dataSize, uint32_t updateDelay);
  virtual void update(void); // publish changes in switch state
  virtual uint8_t decode(const char* topic, const char* payload);
 
 protected: 
  virtual void requestI2CData();
  virtual void sendMQTTData();
  
 protected:
  TwoWire *myWire;
  uint8_t myAddress; 
  uint8_t myDataSize; 
  uint8_t myReadRegister;
  uint32_t myUpdateDelay;

};

class Tmp102Module : public I2cSingleRegisterModule
{
 
   public:
      virtual void begin(MqttHub &hub, const char* mode, TwoWire *wire, int32_t enablePin, uint32_t updateDelay);
 
   protected:
      virtual void sendMQTTData();
      
};

class Mlx90616Module : public I2cSingleRegisterModule
{
   public:
      virtual void begin(MqttHub &hub, const char* mode, TwoWire *wire, int32_t enablePin, uint32_t updateDelay);
   
   protected:
      virtual void sendMQTTData();
   
};

// ------------------------------- CPU VDD ADC Class -------------------------

class CpuVddModule : public MqttModule
{
 public:
  virtual void begin(MqttHub &hub, const char* module, uint32_t interval);
  virtual void update(void);
  virtual uint8_t decode(const char* topic, const char* payload);
 
 private:
  void publishCPUvoltage(void);
 
 private: 
  uint32_t myCurrent;
  uint32_t myInterval;
  
};

// ------------------------------- CPU Temperature Class -------------------------

class CpuTempModule : public MqttModule
{
 public:
  virtual void begin(MqttHub &hub, const char* module, uint32_t Finterval, uint32_t Cinterval);
  virtual void update(void);
  virtual uint8_t decode(const char* topic, const char* payload);
 
 private:
  void publishCPUtempC(void);
  void publishCPUtempF(void);
 
 private:
  uint32_t myCurrentF;
  uint32_t myCurrentC;
  uint32_t myIntervalF;
  uint32_t myIntervalC;

};

// ------------------------------- ADC Pin Class -------------------------

class AdcCtlModule : public MqttModule
{
 public:
  virtual void begin(MqttHub &hub, uint8_t pin, const char* module, uint32_t interval);
  virtual void update(void);
  virtual uint8_t decode(const char* topic, const char* payload);
 
 private:
  void publishADCvoltage(void);
  
 private:
  uint32_t myCurrent;
  uint32_t myInterval;
  uint32_t myAdcPin;
  
};


// ------------------------------- Tone Control Class -------------------------

class ToneCtlModule : public MqttModule
{
 public:
 
   virtual void begin(MqttHub &hub, uint8_t pin, const char* module);
   virtual uint8_t decode(const char* topic, const char* payload);
 
 private:
 
  uint32_t myPin;
  uint32_t myToneFreq;
  uint32_t myToneDuration;
  uint32_t myToneState;
  TimersLP myTimer;

};


