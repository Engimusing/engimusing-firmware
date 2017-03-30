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

#include "Device.h"

class TCS3200Device : public Device
{
   public:
        enum Color
        {
            WHITE,
            RED,
            BLUE,
            GREEN
        };
        
   public:
        virtual void begin(uint8_t s0Pin, uint8_t s1Pin, uint8_t s2Pin, uint8_t s3Pin, uint8_t taosOutPin, uint8_t mode = 1);
        virtual float readColorHertz(Color color);
        

        virtual Device::ValueStruct readValue(int index);
        virtual float numValues(); 
   protected:   
   
        // Operation modes area, controlled by hi/lo settings on S0 and S1 pins.
        //setting mode to zero will put taos into low power mode. taosMode(0);
        virtual void setTaosMode(uint8_t mode);
        
        uint8_t myS0Pin;
        uint8_t myS1Pin;
        uint8_t myS2Pin;
        uint8_t myS3Pin;
        uint8_t myTaosOutPin;
        uint8_t myMode;
      
};