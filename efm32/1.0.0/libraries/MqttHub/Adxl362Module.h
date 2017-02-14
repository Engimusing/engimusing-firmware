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
#include "MqttModule.h"

#include "ADXL362.h"

extern UARTClass Serial;

class ADXL362;

class Adxl362Module : public MqttModule
{
 public:
  virtual void begin(MqttHub &hub, const char* mod, uint32_t accel_VIO, uint32_t accel_VS, uint32_t accel_CS, SPIClass &spi, uint32_t updateDelay);
  virtual void update(void); // publish changes in switch state
  virtual uint8_t decode(const char* topic, const char* payload);
  
 protected:
  virtual void sendMQTTAdxlData();

  ADXL362 myAdxl; 
  uint32_t myUpdateDelay;
  
};

