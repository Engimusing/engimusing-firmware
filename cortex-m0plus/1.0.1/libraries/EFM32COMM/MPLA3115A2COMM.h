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
#include "EFM32COMM.h"

extern UARTClass Serial;

class TwoWire;

class mpla3115a2Class : public MQTTBaseHandler
{
 public:
  virtual void begin(const char* mod, TwoWire *_wire, int32_t _enablePin, uint32_t _updateDelay);
  virtual void update(void); // publish changes in switch state
  virtual uint8_t decode(void);
  virtual float readTemp();
  virtual float readTempF();
  virtual float readAltitude();
  virtual float readPressure();
  virtual float readAltitudeFt();

 protected:
  virtual void sendMQTTTempData();
  virtual void sendMQTTAltitudeData();
  virtual void sendMQTTPressureData();
  virtual void setModeBarometer();
  
  virtual void setModeAltimeter();
  virtual void setModeStandby();
  virtual void setModeActive();
  virtual void setFIFOMode(byte f_Mode);
  virtual void setOversampleRate(byte sampleRate);
  virtual void toggleOneShot();
  virtual void enableEventFlags();
  virtual byte IIC_Read(byte regAddr);
  virtual void IIC_Write(byte regAddr, byte value);
  
  
  TwoWire *myWire; 
  uint32_t myUpdateDelay;
};

