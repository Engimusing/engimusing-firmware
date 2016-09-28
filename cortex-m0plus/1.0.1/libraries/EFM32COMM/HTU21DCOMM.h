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

class htu21dClass : public MQTTBaseHandler
{
 public:
  virtual void begin(const char* mod, TwoWire *_wire, int32_t _enablePin, uint32_t _updateDelay);
  virtual void update(void); // publish changes in switch state
  virtual uint8_t decode(void);
  
 protected:
  virtual void sendMQTTTempData(float degc);
  virtual void sendMQTTHumidityData(float hum);
  virtual unsigned int htdu21d_readTemp();
  virtual unsigned int htdu21d_readHumidity();
  virtual float calc_temp(int SigTemp);
  virtual float calc_humidity(int SigRH);
   
  TwoWire *myWire; 
  uint32_t myUpdateDelay;
};

