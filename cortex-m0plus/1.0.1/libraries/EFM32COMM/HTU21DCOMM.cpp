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
/* 
 HTU21D Humidity Sensor Example Code
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 15th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Get humidity and temperature from the HTU21D sensor.
 */

 #include "HTU21DCOMM.h"

#include <Arduino.h>
#include <Wire.h>

#define WIRE (*myWire)
#define HTDU21D_ADDRESS 0x40  //Unshifted 7-bit I2C address for the sensor

#define TRIGGER_TEMP_MEASURE_HOLD  0xE3
#define TRIGGER_HUMD_MEASURE_HOLD  0xE5
#define TRIGGER_TEMP_MEASURE_NOHOLD  0xF3
#define TRIGGER_HUMD_MEASURE_NOHOLD  0xF5
#define WRITE_USER_REG  0xE6
#define READ_USER_REG  0xE7
#define SOFT_RESET  0xFE



// ------------------------------- i2cSingleRegisterClass -------------------------
void htu21dClass::begin(const char* mod, TwoWire *_wire, int32_t _enablePin, uint32_t _updateDelay)
{
   if(_enablePin > 0)
  {
	pinMode(_enablePin, OUTPUT);
	digitalWrite(_enablePin, HIGH);
  }
  
  myWire = _wire;
  _wire->begin();
  myUpdateDelay = _updateDelay;
  
  MQTTBaseHandler::begin(mod, true);
  
  //give the slave a slight delay so it can turn on.
  delay(50);
  
}

void htu21dClass::update(void)
{
  if(millis() > myTick + myUpdateDelay) {
    myTick = millis();
    float temp = calc_temp(htdu21d_readTemp());
	float humidity = calc_humidity(htdu21d_readHumidity());
	
    sendMQTTTempData(temp);
	sendMQTTHumidityData(humidity);
	
  }
}

uint8_t htu21dClass::decode(void)
{
  int8_t j = isTopicThisModule();
  if(j == 0)
  {
	  return 0;
  }
  
  if(COMM.compare_token(&COMM.topic[j],"STATUS")) {
    float temp = calc_temp(htdu21d_readTemp());
	float humidity = calc_humidity(htdu21d_readHumidity());
	
    sendMQTTTempData(temp);
	sendMQTTHumidityData(humidity);
    return 1;
  }
}


void htu21dClass::sendMQTTTempData(float degc)
{
	COMM.sendMessage((const char*)myModule, "DEG_C", degc);	
}

void htu21dClass::sendMQTTHumidityData(float hum)
{
	COMM.sendMessage((const char*)myModule, "HUM", hum);	
}



//Read the uncompensated temperature value
unsigned int htu21dClass::htdu21d_readTemp()
{
  //Request the temperature
  WIRE.beginTransmission(HTDU21D_ADDRESS);
  WIRE.write(TRIGGER_TEMP_MEASURE_NOHOLD);
  WIRE.endTransmission();

  //Wait for sensor to complete measurement
  delay(60); //44-50 ms max - we could also poll the sensor

  //Comes back in three bytes, data(MSB) / data(LSB) / CRC
  WIRE.requestFrom(HTDU21D_ADDRESS, 3);

  //Wait for data to become available
  int counter = 0;
  while(WIRE.available() < 3)
  {
    counter++;
    delay(1);
    if(counter > 100) return 998; //Error out
  }

  unsigned char msb, lsb, crc;
  msb = WIRE.read();
  lsb = WIRE.read();
  crc = WIRE.read(); //We don't do anything with CRC for now

  unsigned int temperature = ((unsigned int)msb << 8) | lsb;
  temperature &= 0xFFFC; //Zero out the status bits but keep them in place

  return temperature;
}

//Read the humidity
unsigned int htu21dClass::htdu21d_readHumidity()
{
  byte msb, lsb, checksum;

  //Request a humidity reading
  WIRE.beginTransmission(HTDU21D_ADDRESS);
  WIRE.write(TRIGGER_HUMD_MEASURE_NOHOLD); //Measure humidity with no bus holding
  WIRE.endTransmission();

  //Hang out while measurement is taken. 50mS max, page 4 of datasheet.
  delay(55);

  //Read result
  WIRE.requestFrom(HTDU21D_ADDRESS, 3);

  //Wait for data to become available
  int counter = 0;
  while(WIRE.available() < 3)
  {
    counter++;
    delay(1);
    if(counter > 100) return 0; //Error out
  }

  msb = WIRE.read();
  lsb = WIRE.read();
  checksum = WIRE.read();

  unsigned int rawHumidity = ((unsigned int) msb << 8) | (unsigned int) lsb;
  rawHumidity &= 0xFFFC; //Zero out the status bits but keep them in place

  return(rawHumidity);
}

//Given the raw temperature data, calculate the actual temperature
float htu21dClass::calc_temp(int SigTemp)
{
  float tempSigTemp = SigTemp / (float)65536; //2^16 = 65536
  float realTemperature = -46.85 + (175.72 * tempSigTemp); //From page 14

  return(realTemperature);  
}

//Given the raw humidity data, calculate the actual relative humidity
float htu21dClass::calc_humidity(int SigRH)
{
  float tempSigRH = SigRH / (float)65536; //2^16 = 65536
  float rh = -6 + (125 * tempSigRH); //From page 14

  return(rh);  
}

