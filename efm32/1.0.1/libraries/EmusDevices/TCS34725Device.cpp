/*
  Copyright (c) 2016-2017 Engimusing LLC.  All right reserved.

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
  
  original attribution
    @author   KTOWN (Adafruit Industries)
    @license  BSD (see license.txt)

    Driver for the TCS34725 digital color sensors.

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/

#include <TCS34725Device.h>
#include <Arduino.h>

#include <Wire.h>

/*========================================================================*/
/*                          PRIVATE FUNCTIONS                             */
/*========================================================================*/

/**************************************************************************/
/*!
    @brief  Writes a register and an 8 bit value over I2C
*/
/**************************************************************************/
void TCS34725Device::write8 (uint8_t reg, uint32_t value)
{
  myWire->beginTransmission(TCS34725_ADDRESS);

  myWire->write(TCS34725_COMMAND_BIT | reg);
  myWire->write(value & 0xFF);

  myWire->endTransmission();
}

/**************************************************************************/
/*!
    @brief  Reads an 8 bit value over I2C
*/
/**************************************************************************/
uint8_t TCS34725Device::read8(uint8_t reg)
{
  myWire->beginTransmission(TCS34725_ADDRESS);
  myWire->write(TCS34725_COMMAND_BIT | reg);
  myWire->endTransmission();

  myWire->requestFrom(TCS34725_ADDRESS, 1);
  
  return myWire->read();
}

/**************************************************************************/
/*!
    @brief  Reads a 16 bit values over I2C
*/
/**************************************************************************/
uint16_t TCS34725Device::read16(uint8_t reg)
{
  uint16_t x; uint16_t t;

  myWire->beginTransmission(TCS34725_ADDRESS);
  myWire->write(TCS34725_COMMAND_BIT | reg);
  myWire->endTransmission();

  myWire->requestFrom(TCS34725_ADDRESS, 2);

  t = myWire->read();
  x = myWire->read();

  x <<= 8;
  x |= t;
  return x;
}

/**************************************************************************/
/*!
    Enables the device
*/
/**************************************************************************/
void TCS34725Device::enable(void)
{
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
  delay(3);
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);  
}

/**************************************************************************/
/*!
    Disables the device (putting it in lower power sleep mode)
*/
/**************************************************************************/
void TCS34725Device::disable(void)
{
  /* Turn the device off to save power */
  uint8_t reg = 0;
  reg = read8(TCS34725_ENABLE);
  write8(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
}

/*========================================================================*/
/*                            CONSTRUCTORS                                */
/*========================================================================*/

/*========================================================================*/
/*                           PUBLIC FUNCTIONS                             */
/*========================================================================*/

/**************************************************************************/
/*!
    Initializes I2C and configures the sensor (call this function before
    doing anything else)
*/
/**************************************************************************/
bool TCS34725Device::begin(TwoWire &wire, uint8_t enablePin, tcs34725IntegrationTime_t it, tcs34725Gain_t gain) 
{
  myTcs34725Initialised = false;
  myTcs34725IntegrationTime = it;
  myTcs34725Gain = gain;

     if(enablePin > 0)
    {
        pinMode(enablePin, OUTPUT);
        digitalWrite(enablePin, HIGH);
    }
  delay(100);
  
  myWire = &wire;
  
  myWire->begin();
  
  /* Make sure we're actually connected */
  uint8_t x = read8(TCS34725_ID);
  if ((x != 0x44) && (x != 0x10))
  {
    return false;
  }
  myTcs34725Initialised = true;

  /* Set default integration time and gain */
  setIntegrationTime(myTcs34725IntegrationTime);
  setGain(myTcs34725Gain);

  /* Note: by default, the device is in power down mode on bootup */
  enable();

  return true;
}
  
/**************************************************************************/
/*!
    Sets the integration time for the TC34725
*/
/**************************************************************************/
void TCS34725Device::setIntegrationTime(tcs34725IntegrationTime_t it)
{
  /* Update value placeholders */
  myTcs34725IntegrationTime = it;
  
  if (!myTcs34725Initialised) return;

  /* Update the timing register */
  write8(TCS34725_ATIME, it);

  
}

/**************************************************************************/
/*!
    Adjusts the gain on the TCS34725 (adjusts the sensitivity to light)
*/
/**************************************************************************/
void TCS34725Device::setGain(tcs34725Gain_t gain)
{
   /* Update value placeholders */
  myTcs34725Gain = gain;
  
  if (!myTcs34725Initialised) return;
  
  /* Update the timing register */
  write8(TCS34725_CONTROL, gain);


}

void TCS34725Device::sampleData()
{
  if (!myTcs34725Initialised) return;

   /* Set a delay for the integration time */
  switch (myTcs34725IntegrationTime)
  {
    case TCS34725_INTEGRATIONTIME_2_4MS:
      delay(3);
      break;
    case TCS34725_INTEGRATIONTIME_24MS:
      delay(24);
      break;
    case TCS34725_INTEGRATIONTIME_50MS:
      delay(50);
      break;
    case TCS34725_INTEGRATIONTIME_101MS:
      delay(101);
      break;
    case TCS34725_INTEGRATIONTIME_154MS:
      delay(154);
      break;
    case TCS34725_INTEGRATIONTIME_700MS:
      delay(700);
      break;
  }
  
  mySampleC = read16(TCS34725_CDATAL);
  mySampleR = read16(TCS34725_RDATAL);
  mySampleG = read16(TCS34725_GDATAL);
  mySampleB = read16(TCS34725_BDATAL);
  
 
}
/**************************************************************************/
/*!
    @brief  Reads the raw red, green, blue and clear channel values
*/
/**************************************************************************/
void TCS34725Device::getRawData (uint16_t &r, uint16_t &g, uint16_t &b, uint16_t &c)
{
  if (!myTcs34725Initialised) return;

  c = mySampleC;
  r = mySampleR;
  g = mySampleG;
  b = mySampleB;
}

/**************************************************************************/
/*!
    @brief  Converts the raw R/G/B values to color temperature in degrees
            Kelvin
*/
/**************************************************************************/
float TCS34725Device::calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b)
{
  float X, Y, Z;      /* RGB to XYZ correlation      */
  float xc, yc;       /* Chromaticity co-ordinates   */
  float n;            /* McCamy's formula            */
  float cct;

  /* 1. Map RGB values to their XYZ counterparts.    */
  /* Based on 6500K fluorescent, 3000K fluorescent   */
  /* and 60W incandescent values for a wide range.   */
  /* Note: Y = Illuminance or lux                    */
  X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
  Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  Z = (-0.68202F * r) + (0.77073F * g) + ( 0.56332F * b);

  /* 2. Calculate the chromaticity co-ordinates      */
  xc = (X) / (X + Y + Z);
  yc = (Y) / (X + Y + Z);

  /* 3. Use McCamy's formula to determine the CCT    */
  n = (xc - 0.3320F) / (0.1858F - yc);

  /* Calculate the final CCT */
  cct = (449.0F * n * n * n) + (3525.0F * n * n) + (6823.3F * n) + 5520.33F;

  /* Return the results in degrees Kelvin */
  return cct;
}

/**************************************************************************/
/*!
    @brief  Converts the raw R/G/B values to lux
*/
/**************************************************************************/
float TCS34725Device::calculateLux(uint16_t r, uint16_t g, uint16_t b)
{
  float illuminance;

  /* This only uses RGB ... how can we integrate clear or calculate lux */
  /* based exclusively on clear since this might be more reliable?      */
  illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

  return illuminance;
}


void TCS34725Device::setInterrupt(bool i) {
  uint8_t r = read8(TCS34725_ENABLE);
  if (i) {
    r |= TCS34725_ENABLE_AIEN;
  } else {
    r &= ~TCS34725_ENABLE_AIEN;
  }
  write8(TCS34725_ENABLE, r);
}

void TCS34725Device::clearInterrupt(void) {
  myWire->beginTransmission(TCS34725_ADDRESS);
  myWire->write(TCS34725_COMMAND_BIT | 0x66);
  myWire->endTransmission();
}


void TCS34725Device::setIntLimits(uint16_t low, uint16_t high) {
   write8(0x04, low & 0xFF);
   write8(0x05, low >> 8);
   write8(0x06, high & 0xFF);
   write8(0x07, high >> 8);
}

Device::ValueStruct TCS34725Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        sampleData();
        output.type = Device::TypeInt;
        output.value.integer = mySampleR;
        output.name = "RAW_R";
    }
    else if(index == 1)
    {
        output.type = Device::TypeInt;
        output.value.integer = mySampleG;
        output.name = "RAW_G";
    }
    else if(index == 2)
    {
        output.type = Device::TypeInt;
        output.value.integer = mySampleB;
        output.name = "RAW_B";
    }    
    else if(index == 3)
    {
        output.type = Device::TypeInt;
        output.value.integer = mySampleC;
        output.name = "RAW_C";
    }

    else if(index == 4)
    {
        output.type = Device::TypeInt;
        output.value.decimal = calculateColorTemperature(mySampleR,mySampleG,mySampleB);
        output.name = "COLOR_K";
    }
    else if(index == 5)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = calculateLux(mySampleR,mySampleG,mySampleB);
        output.name = "LUM_LUX";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

float TCS34725Device::numValues()
{
    return 6; 
}

