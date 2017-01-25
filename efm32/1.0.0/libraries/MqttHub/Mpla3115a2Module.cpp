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

//Example for using the MPL3115A2 Altitude Sensor on the Engimusing RS232 board
//For more info goto http://emus.us/m3115a2-1
//Modified by Tim George
//Engimusing 2014
//This shows how to read and interpret the data from the 
// MPL3115A2 Altitude Sensor
////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 MPL3115A2 Altitude Sensor Example
 By: A.Weiss, 7/17/2012, changes Nathan Seidle Sept 23rd, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Usage:
 -Serial terminal at 9600bps
 -Prints altitude in meters, temperature in degrees C, with 1/16 resolution.
 -software enabled interrupt on new data, ~1Hz with full resolution
 
 During testing, GPS with 9 sattelites reported 5393ft, sensor reported 5360ft (delta of 33ft). Very close!
 
 */

#include "Mpla3115a2Module.h"

#include <Wire.h>

#define STATUS     0x00
#define OUT_P_MSB  0x01
#define OUT_P_CSB  0x02
#define OUT_P_LSB  0x03
#define OUT_T_MSB  0x04
#define OUT_T_LSB  0x05
#define DR_STATUS  0x06
#define OUT_P_DELTA_MSB  0x07
#define OUT_P_DELTA_CSB  0x08
#define OUT_P_DELTA_LSB  0x09
#define OUT_T_DELTA_MSB  0x0A
#define OUT_T_DELTA_LSB  0x0B
#define WHO_AM_I   0x0C
#define F_STATUS   0x0D
#define F_DATA     0x0E
#define F_SETUP    0x0F
#define TIME_DLY   0x10
#define SYSMOD     0x11
#define INT_SOURCE 0x12
#define PT_DATA_CFG 0x13
#define BAR_IN_MSB 0x14
#define BAR_IN_LSB 0x15
#define P_TGT_MSB  0x16
#define P_TGT_LSB  0x17
#define T_TGT      0x18
#define P_WND_MSB  0x19
#define P_WND_LSB  0x1A
#define T_WND      0x1B
#define P_MIN_MSB  0x1C
#define P_MIN_CSB  0x1D
#define P_MIN_LSB  0x1E
#define T_MIN_MSB  0x1F
#define T_MIN_LSB  0x20
#define P_MAX_MSB  0x21
#define P_MAX_CSB  0x22
#define P_MAX_LSB  0x23
#define T_MAX_MSB  0x24
#define T_MAX_LSB  0x25
#define CTRL_REG1  0x26
#define CTRL_REG2  0x27
#define CTRL_REG3  0x28
#define CTRL_REG4  0x29
#define CTRL_REG5  0x2A
#define OFF_P      0x2B
#define OFF_T      0x2C
#define OFF_H      0x2D

#define MPL3115A2_ADDRESS 0x60 // 7-bit I2C address

long startTime;

// ------------------------------- Mpla3115a2Module -------------------------
void Mpla3115a2Module::begin(MqttHub &hub, const char* mod, TwoWire *wire, int32_t enablePin, uint32_t updateDelay)
{
   if(enablePin > 0)
  {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);
  }
  
  myWire = wire;
  
   // Initialize the 'Wire' class for the I2C-bus.
  wire->begin();
  myUpdateDelay = updateDelay;
  
  MqttModule::begin(hub, mod, true);
  
  //give the slave a slight delay so it can turn on.
  delay(50);
  
  int value = i2cRead(WHO_AM_I);
  while(value != 196)
  {
	delay(1000);
	value = i2cRead(WHO_AM_I);
  }
  
  // Configure the sensor
  setModeAltimeter(); // Measure altitude above sea level in meters
 
  setOversampleRate(7); // Set Oversample to the recommended 128
  enableEventFlags(); // Enable all three pressure and temp event flags
  
}

void Mpla3115a2Module::update(void)
{
  if(millis() > myTick + myUpdateDelay) {
    myTick = millis();
	
    sendMQTTTempData();
	 sendMQTTAltitudeData();
	 //sendMQTTPressureData();
	
	
  }
}

uint8_t Mpla3115a2Module::decode(const char* topic, const char* payload)
{
  int8_t j = isTopicThisModule(topic);
  if(j == 0)
  {
	  return 0;
  }
  
  if(compare_token(&topic[j],"STATUS")) {
    sendMQTTTempData();
	 sendMQTTAltitudeData();
	 //sendMQTTPressureData();
    return 1;
  }
}

void Mpla3115a2Module::sendMQTTTempData()
{
	myHub->sendMessage((const char*)myModule, "DEG_C", readTemp());	
}

void Mpla3115a2Module::sendMQTTAltitudeData()
{
	myHub->sendMessage((const char*)myModule, "ALT_M", readAltitude());	
}

void Mpla3115a2Module::sendMQTTPressureData()
{
	myHub->sendMessage((const char*)myModule, "PRESSURE", readPressure());	
}

//Returns the number of meters above sea level
float Mpla3115a2Module::readAltitude()
{
  toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading

  //Wait for PDR bit, indicates we have new pressure data
  int counter = 0;
  while( (i2cRead(STATUS) & (1<<1)) == 0)
  {
      if(++counter > 100) return(-999); //Error out
      delay(10);
  }
  
  // Read pressure registers
  myWire->beginTransmission(MPL3115A2_ADDRESS);
  myWire->write(OUT_P_MSB);  // Address of data to get
  myWire->endTransmission(false); // Send data to I2C dev with option for a repeated start. THIS IS NECESSARY and not supported before Arduino V1.0.1!
  myWire->requestFrom(MPL3115A2_ADDRESS, 3); // Request three bytes

  //Wait for data to become available
  counter = 0;
  while(myWire->available() < 3)
  {
    if(counter++ > 100) return(-999); //Error out
    delay(10);
  }

  byte msb, csb, lsb;
  msb = myWire->read();
  csb = myWire->read();
  lsb = myWire->read();

  toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading

  // The least significant bytes l_altitude and l_temp are 4-bit,
  // fractional values, so you must cast the calulation in (float),
  // shift the value over 4 spots to the right and divide by 16 (since 
  // there are 16 values in 4-bits). 
  float tempcsb = (lsb>>4)/16.0;

  float altitude = (float)( (msb << 8) | csb) + tempcsb;

  return(altitude);
}

//Returns the number of feet above sea level
float Mpla3115a2Module::readAltitudeFt()
{
  return(readAltitude() * 3.28084);
}

//Reads the current pressure in Pa
//Unit must be set in barometric pressure mode
float Mpla3115a2Module::readPressure()
{
  toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading

  //Wait for PDR bit, indicates we have new pressure data
  int counter = 0;
  while( (i2cRead(STATUS) & (1<<2)) == 0)
  {
      if(++counter > 100) return(-999); //Error out
      delay(10);
  }

  // Read pressure registers
  myWire->beginTransmission(MPL3115A2_ADDRESS);
  myWire->write(OUT_P_MSB);  // Address of data to get
  myWire->endTransmission(false); // Send data to I2C dev with option for a repeated start. THIS IS NECESSARY and not supported before Arduino V1.0.1!
  myWire->requestFrom(MPL3115A2_ADDRESS, 3); // Request three bytes

  //Wait for data to become available
  counter = 0;
  while(myWire->available() < 3)
  {
    if(counter++ > 100) return(-999); //Error out
    delay(10);
  }

  byte msb, csb, lsb;
  msb = myWire->read();
  csb = myWire->read();
  lsb = myWire->read();

  toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading

  // Pressure comes back as a left shifted 20 bit number
  long pressure_whole = (long)msb<<16 | (long)csb<<8 | (long)lsb;
  pressure_whole >>= 6; //Pressure is an 18 bit number with 2 bits of decimal. Get rid of decimal portion.

  lsb &= 0b00110000; //Bits 5/4 represent the fractional component
  lsb >>= 4; //Get it right aligned
  float pressure_decimal = (float)lsb/4.0; //Turn it into fraction

  float pressure = (float)pressure_whole + pressure_decimal;

  return(pressure);
}

float Mpla3115a2Module::readTemp()
{
  toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading

  //Wait for TDR bit, indicates we have new temp data
  int counter = 0;
  while( (i2cRead(STATUS) & (1<<1)) == 0)
  {
      if(++counter > 100) return(-999); //Error out
      delay(10);
  }
  
  // Read temperature registers
  myWire->beginTransmission(MPL3115A2_ADDRESS);
  myWire->write(OUT_T_MSB);  // Address of data to get
  myWire->endTransmission(false); // Send data to I2C dev with option for a repeated start. THIS IS NECESSARY and not supported before Arduino V1.0.1!
  myWire->requestFrom(MPL3115A2_ADDRESS, 2); // Request two bytes

  //Wait for data to become available
  counter = 0;
  while(myWire->available() < 2)
  {
    if(++counter > 100) return(-999); //Error out
    delay(10);
  }

  byte msb, lsb;
  msb = myWire->read();
  lsb = myWire->read();
  
  // The least significant bytes l_altitude and l_temp are 4-bit,
  // fractional values, so you must cast the calulation in (float),
  // shift the value over 4 spots to the right and divide by 16 (since 
  // there are 16 values in 4-bits). 
  float templsb = (lsb>>4)/16.0; //temp, fraction of a degree

  float temperature = (float)(msb + templsb);

  return(temperature);
}

//Give me temperature in fahrenheit!
float Mpla3115a2Module::readTempF()
{
  return((readTemp() * 9.0)/ 5.0 + 32.0); // Convert celsius to fahrenheit
}

//Sets the mode to Barometer
//CTRL_REG1, ALT bit
void Mpla3115a2Module::setModeBarometer()
{
  byte tempSetting = i2cRead(CTRL_REG1); //Read current settings
  tempSetting &= ~(1<<7); //Clear ALT bit
  i2cWrite(CTRL_REG1, tempSetting);
}

//Sets the mode to Altimeter
//CTRL_REG1, ALT bit
void Mpla3115a2Module::setModeAltimeter()
{
  byte tempSetting = i2cRead(CTRL_REG1); //Read current settings
  tempSetting |= (1<<7); //Set ALT bit
  i2cWrite(CTRL_REG1, tempSetting);
}

//Puts the sensor in standby mode
//This is needed so that we can modify the major control registers
void Mpla3115a2Module::setModeStandby()
{
  byte tempSetting = i2cRead(CTRL_REG1); //Read current settings
  tempSetting &= ~(1<<0); //Clear SBYB bit for Standby mode
  i2cWrite(CTRL_REG1, tempSetting);
}

//Puts the sensor in active mode
//This is needed so that we can modify the major control registers
void Mpla3115a2Module::setModeActive()
{
  byte tempSetting = i2cRead(CTRL_REG1); //Read current settings
  tempSetting |= (1<<0); //Set SBYB bit for Active mode
  i2cWrite(CTRL_REG1, tempSetting);
}

//Setup FIFO mode to one of three modes. See page 26, table 31
//From user jr4284
void Mpla3115a2Module::setFIFOMode(byte f_Mode)
{
  if (f_Mode > 3) f_Mode = 3; // FIFO value cannot exceed 3.
  f_Mode <<= 6; // Shift FIFO byte left 6 to put it in bits 6, 7.

  byte tempSetting = i2cRead(F_SETUP); //Read current settings
  tempSetting &= ~(3<<6); // clear bits 6, 7
  tempSetting |= f_Mode; //Mask in new FIFO bits
  i2cWrite(F_SETUP, tempSetting);
}

//Call with a rate from 0 to 7. See page 33 for table of ratios.
//Sets the over sample rate. Datasheet calls for 128 but you can set it 
//from 1 to 128 samples. The higher the oversample rate the greater
//the time between data samples.
void Mpla3115a2Module::setOversampleRate(byte sampleRate)
{
  if(sampleRate > 7) sampleRate = 7; //OS cannot be larger than 0b.0111
  sampleRate <<= 3; //Align it for the CTRL_REG1 register

  byte tempSetting = i2cRead(CTRL_REG1); //Read current settings
  tempSetting &= 0b11000111; //Clear out old OS bits
  tempSetting |= sampleRate; //Mask in new OS bits
  i2cWrite(CTRL_REG1, tempSetting);
}

//Clears then sets the OST bit which causes the sensor to immediately take another reading
//Needed to sample faster than 1Hz
void Mpla3115a2Module::toggleOneShot(void)
{
  byte tempSetting = i2cRead(CTRL_REG1); //Read current settings
  tempSetting &= ~(1<<1); //Clear OST bit
  i2cWrite(CTRL_REG1, tempSetting);

  tempSetting = i2cRead(CTRL_REG1); //Read current settings to be safe
  tempSetting |= (1<<1); //Set OST bit
  i2cWrite(CTRL_REG1, tempSetting);
}

//Enables the pressure and temp measurement event flags so that we can
//test against them. This is recommended in datasheet during setup.
void Mpla3115a2Module::enableEventFlags()
{
  i2cWrite(PT_DATA_CFG, 0x07); // Enable all three pressure and temp event flags 
}

// These are the two I2C functions in this sketch.
byte Mpla3115a2Module::i2cRead(byte regAddr)
{
  // This function reads one byte over IIC
  myWire->beginTransmission(MPL3115A2_ADDRESS);
  myWire->write(regAddr);  // Address of CTRL_REG1
  myWire->endTransmission(false); // Send data to I2C dev with option for a repeated start. THIS IS NECESSARY and not supported before Arduino V1.0.1!
  myWire->requestFrom(MPL3115A2_ADDRESS, 1); // Request the data...
  return myWire->read();
}

void Mpla3115a2Module::i2cWrite(byte regAddr, byte value)
{
  // This function writes one byto over IIC
  myWire->beginTransmission(MPL3115A2_ADDRESS);
  myWire->write(regAddr);
  myWire->write(value);
  myWire->endTransmission(true);
}
