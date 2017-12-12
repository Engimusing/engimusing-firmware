///
///@file MqttModule.h
///@brief Contains the MqttModule and some related derived classes. 
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
#include "MqttHub.h"

class Device;

///@brief Base class for modules, modules are updated periodically and can handle messages received from a port
class MqttModule
{
    friend class MqttHub;
  
    public:
  
        ///@brief Initialize the module and connect it to the hub
        ///@param [in] hub MqttHub to connect the module to.
        ///@param [in] module Name of the Module
        ///@param [in] subOnHeartbeat If true the module subscription will happen automatically and periodically.
        virtual void begin(MqttHub &hub, const char* module, bool subOnHeartbeat = true);

        ///@brief Called by the MqttHub to update the module
        virtual void update(void);

        ///@brief Called by the MqttHub to give the module a chance to handle a message from the port.
        ///@param [in] topic Topic name for the message
        ///@param [in] payload Payload from the message
        ///@return 0 if the message was not decoded and !0 if it was.
        ///@details Used by the derived classes to handle messages from the MqttHub. This base class always just returns 0.
        virtual uint8_t decode(const char* topic, const char* payload);

    protected:
        ///@brief Checks to see if the topic matches this modules name.
        ///@param [in] topic Topic to compare against the module name.
        ///@return location in the string that is the next location after the module name in the topic.
        virtual uint8_t isTopicThisModule(const char* topic);
        
        ///@brief Checks to see if the topic matches this modules name and processes the "+" wild-card.
        ///@param [in] topic Topic to compare against the module name.
        ///@return location in the string that is the next location after the module name in the topic.
        virtual uint8_t isTopicThisModuleWildcard(const char* topic);

        ///@brief Compares two strings to see if inTok starts with cmpTok
        ///@param [in] inTok String to see if it starts with the cmpTok.
        ///@param [in] cmpTok String to look for in the inTok string.
        ///@return 1 if inTok starts with cmpTok, else 0.
        int8_t compare_token(const char* inTok, const char* cmpTok);

    protected:
        MqttHub *myHub;
        const char* myModule;
        bool mySubOnHeartbeat;
        uint32_t myTick;
        MqttModule* myNextModule;
};

// ------------------------------- Message Input Class -------------------------
///@brief Class for receiving data from MQTT objects. Handles number (float, int, bool) types of data
/// messages that match the module name and control value (like /MODULE/CONTROL) then the payload will be read in and
/// converted to the type T and stored. The data can be retrieved using the getInput() function.
template <typename T>
class MessageInputModule : public MqttModule
{
 public:
  
  ///@brief Initialize the module and connect it to the hub
  ///@param [in] hub MqttHub object to connect the module to.
  ///@param [in] module Name for the module.
  ///@param [in] control Name of the control value.
  virtual void begin(MqttHub &hub, const char* module, const char* control)
  {
      MqttModule::begin(hub, module, true);

      myControl = control;
      myInputValue = 0;
      myNewData = false;
   }
  
  ///@brief Process an MQTT message and see if this module should handle it
  ///@param [in] topic Name of the topic to decode
  ///@param [in] payload Payload associated with the topic
  ///@return 1 if this module processed the message, else 0
  virtual uint8_t decode(const char* topic, const char* payload)
  {
      int8_t j = isTopicThisModule(topic);
      if(j == 0)
      {
        return 0;
      }  
      
      if(compare_token(&topic[j],myControl)) {
          parsePayload(payload, myInputValue);
          myNewData = true;
          return 1;
      }
  }

  
  ///@brief Get the last data sent to this module
  ///@return Last data received.
  ///@details Clears the has new data flag.
  virtual T getInput(void)
  {
    myNewData = false;
    return myInputValue;
  }
  
  ///@brief Check to see if there has been new data since the last time getInput was called.
  ///@return True if there is new data, false if the data is old.
  virtual bool hasNewData()
  {
      return myNewData;
  }
  
  ///@brief Check to see if this topic matches the module name for this module using the + wildcard.
  ///@param [in] topic Topic from the message
  ///@return 1 if it matches else 0
  virtual uint8_t isTopicThisModule(const char* topic)
  {
      return isTopicThisModuleWildcard(topic);
  }


 protected:
 
  ///@brief float payload parsing function.
  virtual void parsePayload(const char* payload, float &output)
  {
      output = atofLocal(payload);   
  }
  
  ///@brief integer payload parsing function.
  virtual void parsePayload(const char* payload, int32_t &output)
  {
      output = atoi(payload);
  }
  
  ///@brief boolean payload parsing function. 0 for false and anything else is true
  virtual void parsePayload(const char* payload, bool &output)
  {
      if(payload[0] == '0')
      {
        output = false;
      }
      else
      {
        output = true;
      }
  }

  T myInputValue;
  const char* myControl;
  bool myNewData;

};

// ------------------------------- Message Input Class -------------------------
///@brief Class for receiving data from MQTT objects. Handles string data
/// messages that match the module name and control value (like /MODULE/CONTROL) then the payload will be read in and
/// stored. The data can be retrieved using the getInput() function.
class MessageInputStringModule : public MqttModule
{
    public:
        ///@brief Initialize the module and connect it to the hub
        ///@param [in] hub MqttHub object to connect the module to.
        ///@param [in] module Name for the module.
        ///@param [in] control Name of the control value.
        virtual void begin(MqttHub &hub, const char* module, const char* control);

        ///@brief Process an MQTT message and see if this module should handle it
        ///@param [in] topic Name of the topic to decode
        ///@param [in] payload Payload associated with the topic
        ///@return 1 if this module processed the message, else 0
        virtual uint8_t decode(const char* topic, const char* payload);

        ///@brief Get the last data sent to this module
        ///@return Last data received.
        ///@details Clears the has new data flag.
        virtual const char *getInputString(void);

        ///@brief Check to see if there has been new data since the last time getInput was called.
        ///@return True if there is new data, false if the data is old.
        virtual bool hasNewData();

        ///@brief Check to see if this topic matches the module name for this module using the + wildcard.
        ///@param [in] topic Topic from the message
        ///@return 1 if it matches else 0
        virtual uint8_t isTopicThisModule(const char* topic);

    private:

        static const int maxStringSize = ITEM_PAYLOAD_LENGTH;
        char myInputString[maxStringSize];
        const char* myControl;
        bool myNewData;

};


// ------------------------------- Notification Class -------------------------
///@brief Class for receiving a MQTT notification message
/// messages that match the module name and control value (like /MODULE/CONTROL) and the payload matches what it is looking for
/// then getState will return 1 once. 
class NotificationModule : public MqttModule
{
    public:
  
        ///@brief Initialize the module and connect it to the hub
        ///@param [in] hub MqttHub object to connect the module to.
        ///@param [in] module Name for the module.
        ///@param [in] control Name of the control value.
        ///@param [in] payload Payload string to look for.
        virtual void begin(MqttHub &hub, const char* module, const char* control, const char* payload);

        ///@brief Process an MQTT message and see if this module should handle it
        ///@param [in] topic Name of the topic to decode
        ///@param [in] payload Payload associated with the topic
        ///@return 1 if this module processed the message, else 0
        virtual uint8_t decode(const char* topic, const char* payload);
        
        ///@brief Check to see if this module has received the message it is looking for.
        ///@return 1 if the module has received the message it is looking for, else 0 
        ///@details Will only return 1 once and then it will return 0 again until another message is received that is the event message again
        virtual uint8_t getState(void);

    private:

        uint8_t myState;
        const char* myControl;
        const char* myPayload;
  
};

// ------------------------------- SimpleMqttModule -------------------------
///@brief Main module class for use with the MqttHub. This module can be used with any class that
/// is derived from the Device class. It sends out all Device values periodically and passes the 
/// messages to the device to see if it can handle them as well.
class SimpleMqttModule : public MqttModule
{
    public:
    
     ///@brief Initialize the module and connect it to the hub
        ///@param [in] hub MqttHub object to connect the module to.
        ///@param [in] module Name for the module.
        ///@param [in] control Name of the control value.
        ///@param [in] payload Payload string to look for.
       
       
        ///@brief Initialize the module and connect it to the hub
        ///@param [in] hub MqttHub object to connect the module to.
        ///@param [in] device Object that is a Device derived class. See EmusDevices folder for classes.
        ///@param [in] mod Name for the module.
        ///@param [in] updateDelay Number of milliseconds to wait between sending all the Device values.
        virtual void begin(MqttHub &hub, Device &device, const char* mod, uint32_t updateDelay);
       
        ///@brief Called by the MqttHub update() and periodically sends all the values from the device
        virtual void update(void); 
        
        ///@brief Attempt to decode an MQTT message. Also sends it to the Device for attempted decoding as well.
        ///@param [in] topic Topic from the MQTT message
        ///@param [in] payload Payload from the MQTT message
        ///@return 1 if the message was decoded and 0 if not.
        virtual uint8_t decode(const char* topic, const char* payload);
    protected:
        ///@brief Send all the values from the device as individual MQTT messages.
        virtual void sendMQTTData();
    
    protected:
        Device *myDevice;
        uint32_t myUpdateDelay;
      
};

///@cond DEPRECATED
//Deprecated classes below this point. These should be avoided and simple Mqtt Module with a device should be used instead.

// ------------------------------- On/Off Control Class -------------------------
//This has been replaced by the OnOffCtrlDevice
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
  virtual void  begin(MqttHub &hub, uint8_t pin, const char* module, uint8_t bounceCount, uint32_t updateDelay = 100);
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
  uint32_t myUpdateDelay;
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

///@endcond


