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

class mpu9150Class : public MQTTBaseHandler
{
 public:
  virtual void begin(const char* mod, TwoWire *_wire, int32_t _standbyPin, uint32_t _updateDelay);
  virtual void update(void); // publish changes in switch state
  virtual uint8_t decode(void);
  virtual void getTemp(float& temp);
  virtual void getCompassData(int& x, int& y, int& z);
  virtual void getGyroData(int& x, int& y, int& z);
  virtual void getAccelData(int& x, int& y, int& z);
  
 protected:
  virtual void sendMQTTTempData();
  virtual void sendMQTTCompassData();
  virtual void sendMQTTGyroData();
  virtual void sendMQTTAccelData();
  virtual void setupCompass();
  virtual int readSensor(int addrL, int addrH);
  virtual int readSensor(int addr);
  virtual int writeSensor(int addr,int data);
   
  TwoWire *myWire; 
  uint32_t myUpdateDelay;
};

