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

#if SPI_INTERFACES_COUNT > 0

#include "MqttModule.h"
#include <SPI.h>

// Get your current altimiter setting from from the National
// Weather Service - http://www.weather.gov
// This value is often labeled "Barometer" or "Barometric Pressure" or just "Pressure"
#define NWS_BARO 29.92 

// Pin definitions
#define MPL115A1_ENABLE_PIN 30
#define MPL115A1_SELECT_PIN 41
#define MPL115A1_POWER_PIN 45

// Masks for MPL115A1 SPI i/o
#define MPL115A1_READ_MASK  0x80
#define MPL115A1_WRITE_MASK 0x7F 

// MPL115A1 register address map
#define PRESH   0x00    // 80
#define PRESL   0x02    // 82
#define TEMPH   0x04    // 84
#define TEMPL   0x06    // 86

#define A0MSB   0x08    // 88
#define A0LSB   0x0A    // 8A
#define B1MSB   0x0C    // 8C
#define B1LSB   0x0E    // 8E
#define B2MSB   0x10    // 90
#define B2LSB   0x12    // 92
#define C12MSB  0x14    // 94
#define C12LSB  0x16    // 96
#define C11MSB  0x18    // 98
#define C11LSB  0x1A    // 9A
#define C22MSB  0x1C    // 9C
#define C22LSB  0x1E    // 9E

// Unit conversion macros
#define FT_TO_M(x) ((long)((x)*(0.3048)))
#define KPA_TO_INHG(x) ((x)*(0.295333727))
#define KPA_TO_MMHG(x) ((x)*(7.50061683))
#define KPA_TO_PSIA(x) ((x)*(0.145037738))
#define KPA_TO_KGCM2(x) ((x)*(0.0102))
#define INHG_TO_PSIA(x) ((x)*(0.49109778))
#define DEGC_TO_DEGF(x) ((x)*(9.0/5.0)+32)


class Mpl115a1Module : public MqttModule
{
 public:
    virtual void begin(MqttHub &hub, const char* mod, uint32_t enablePin, uint32_t powerPin, uint32_t csPin, SPIClass &spi, uint32_t updateDelay);
    virtual void update(void); // publish changes in switch state
    virtual uint8_t decode(const char* topic, const char* payload);
  
 protected:
    //virtual void sendMQTTAltData();
    virtual void sendMQTTTempData();
    virtual void sendMQTTPressureData();

    //virtual long calculateAltitudeFt(float pressure_kPa);

    virtual float calculateTemperatureC();

    virtual float calculatePressurekPa();

    virtual unsigned int readRegister(byte thisRegister);

    virtual void writeRegister(byte thisRegister, byte thisValue);

  
    SPIClass *mySpi;
    uint32_t myCsPin;
    uint32_t myUpdateDelay;
  
};

#endif
