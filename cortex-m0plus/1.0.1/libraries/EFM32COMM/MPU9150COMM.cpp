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

//Example for using the MPU5190 9-axis sensor with MQTT
//For more info goto http://emus.us/mpu5190-1
//Modified by Tim George
//Engimusing 2016
//This shows how to read and interpret the data from the 
// MPU5190 9-axis sensor
////////////////////////////////////////////////////////////////////////////////////////////////////////

// MPU-9150 Accelerometer + Gyro + Compass + Temperature
// -----------------------------
//
// By arduino.cc user "frtrobotik" (Tobias Hübner)
//
//
// July 2013
//      first version
//
// Open Source / Public Domain
//
// Using Arduino 1.0.1
// It will not work with an older version,
// since myWire->endTransmission() uses a parameter
// to hold or release the I2C bus.
//
// Documentation:
// - The InvenSense documents:
//   - "MPU-9150 Product Specification Revision 4.0",
//     PS-MPU-9150A.pdf
//   - "MPU-9150 Register Map and Descriptions Revision 4.0",
//     RM-MPU-9150A-00.pdf
//   - "MPU-9150 9-Axis Evaluation Board User Guide"
//     AN-MPU-9150EVB-00.pdf
//
// The accuracy is 16-bits.
//
// Some parts are copied by the MPU-6050 Playground page.
// playground.arduino.cc/Main/MPU-6050
// There are more Registervalues. Here are only the most
// nessecary ones to get started with this sensor.

#include "MPU9150COMM.h"

#include <Wire.h>

// Register names according to the datasheet.
// According to the InvenSense document
// "MPU-9150 Register Map and Descriptions Revision 4.0",

#define MPU9150_SELF_TEST_X        0x0D   // R/W
#define MPU9150_SELF_TEST_Y        0x0E   // R/W
#define MPU9150_SELF_TEST_X        0x0F   // R/W
#define MPU9150_SELF_TEST_A        0x10   // R/W
#define MPU9150_SMPLRT_DIV         0x19   // R/W
#define MPU9150_CONFIG             0x1A   // R/W
#define MPU9150_GYRO_CONFIG        0x1B   // R/W
#define MPU9150_ACCEL_CONFIG       0x1C   // R/W
#define MPU9150_FF_THR             0x1D   // R/W
#define MPU9150_FF_DUR             0x1E   // R/W
#define MPU9150_MOT_THR            0x1F   // R/W
#define MPU9150_MOT_DUR            0x20   // R/W
#define MPU9150_ZRMOT_THR          0x21   // R/W
#define MPU9150_ZRMOT_DUR          0x22   // R/W
#define MPU9150_FIFO_EN            0x23   // R/W
#define MPU9150_I2C_MST_CTRL       0x24   // R/W
#define MPU9150_I2C_SLV0_ADDR      0x25   // R/W
#define MPU9150_I2C_SLV0_REG       0x26   // R/W
#define MPU9150_I2C_SLV0_CTRL      0x27   // R/W
#define MPU9150_I2C_SLV1_ADDR      0x28   // R/W
#define MPU9150_I2C_SLV1_REG       0x29   // R/W
#define MPU9150_I2C_SLV1_CTRL      0x2A   // R/W
#define MPU9150_I2C_SLV2_ADDR      0x2B   // R/W
#define MPU9150_I2C_SLV2_REG       0x2C   // R/W
#define MPU9150_I2C_SLV2_CTRL      0x2D   // R/W
#define MPU9150_I2C_SLV3_ADDR      0x2E   // R/W
#define MPU9150_I2C_SLV3_REG       0x2F   // R/W
#define MPU9150_I2C_SLV3_CTRL      0x30   // R/W
#define MPU9150_I2C_SLV4_ADDR      0x31   // R/W
#define MPU9150_I2C_SLV4_REG       0x32   // R/W
#define MPU9150_I2C_SLV4_DO        0x33   // R/W
#define MPU9150_I2C_SLV4_CTRL      0x34   // R/W
#define MPU9150_I2C_SLV4_DI        0x35   // R  
#define MPU9150_I2C_MST_STATUS     0x36   // R
#define MPU9150_INT_PIN_CFG        0x37   // R/W
#define MPU9150_INT_ENABLE         0x38   // R/W
#define MPU9150_INT_STATUS         0x3A   // R  
#define MPU9150_ACCEL_XOUT_H       0x3B   // R  
#define MPU9150_ACCEL_XOUT_L       0x3C   // R  
#define MPU9150_ACCEL_YOUT_H       0x3D   // R  
#define MPU9150_ACCEL_YOUT_L       0x3E   // R  
#define MPU9150_ACCEL_ZOUT_H       0x3F   // R  
#define MPU9150_ACCEL_ZOUT_L       0x40   // R  
#define MPU9150_TEMP_OUT_H         0x41   // R  
#define MPU9150_TEMP_OUT_L         0x42   // R  
#define MPU9150_GYRO_XOUT_H        0x43   // R  
#define MPU9150_GYRO_XOUT_L        0x44   // R  
#define MPU9150_GYRO_YOUT_H        0x45   // R  
#define MPU9150_GYRO_YOUT_L        0x46   // R  
#define MPU9150_GYRO_ZOUT_H        0x47   // R  
#define MPU9150_GYRO_ZOUT_L        0x48   // R  
#define MPU9150_EXT_SENS_DATA_00   0x49   // R  
#define MPU9150_EXT_SENS_DATA_01   0x4A   // R  
#define MPU9150_EXT_SENS_DATA_02   0x4B   // R  
#define MPU9150_EXT_SENS_DATA_03   0x4C   // R  
#define MPU9150_EXT_SENS_DATA_04   0x4D   // R  
#define MPU9150_EXT_SENS_DATA_05   0x4E   // R  
#define MPU9150_EXT_SENS_DATA_06   0x4F   // R  
#define MPU9150_EXT_SENS_DATA_07   0x50   // R  
#define MPU9150_EXT_SENS_DATA_08   0x51   // R  
#define MPU9150_EXT_SENS_DATA_09   0x52   // R  
#define MPU9150_EXT_SENS_DATA_10   0x53   // R  
#define MPU9150_EXT_SENS_DATA_11   0x54   // R  
#define MPU9150_EXT_SENS_DATA_12   0x55   // R  
#define MPU9150_EXT_SENS_DATA_13   0x56   // R  
#define MPU9150_EXT_SENS_DATA_14   0x57   // R  
#define MPU9150_EXT_SENS_DATA_15   0x58   // R  
#define MPU9150_EXT_SENS_DATA_16   0x59   // R  
#define MPU9150_EXT_SENS_DATA_17   0x5A   // R  
#define MPU9150_EXT_SENS_DATA_18   0x5B   // R  
#define MPU9150_EXT_SENS_DATA_19   0x5C   // R  
#define MPU9150_EXT_SENS_DATA_20   0x5D   // R  
#define MPU9150_EXT_SENS_DATA_21   0x5E   // R  
#define MPU9150_EXT_SENS_DATA_22   0x5F   // R  
#define MPU9150_EXT_SENS_DATA_23   0x60   // R  
#define MPU9150_MOT_DETECT_STATUS  0x61   // R  
#define MPU9150_I2C_SLV0_DO        0x63   // R/W
#define MPU9150_I2C_SLV1_DO        0x64   // R/W
#define MPU9150_I2C_SLV2_DO        0x65   // R/W
#define MPU9150_I2C_SLV3_DO        0x66   // R/W
#define MPU9150_I2C_MST_DELAY_CTRL 0x67   // R/W
#define MPU9150_SIGNAL_PATH_RESET  0x68   // R/W
#define MPU9150_MOT_DETECT_CTRL    0x69   // R/W
#define MPU9150_USER_CTRL          0x6A   // R/W
#define MPU9150_PWR_MGMT_1         0x6B   // R/W
#define MPU9150_PWR_MGMT_2         0x6C   // R/W
#define MPU9150_FIFO_COUNTH        0x72   // R/W
#define MPU9150_FIFO_COUNTL        0x73   // R/W
#define MPU9150_FIFO_R_W           0x74   // R/W
#define MPU9150_WHO_AM_I           0x75   // R

//MPU9150 Compass
#define MPU9150_CMPS_XOUT_L        0x4A   // R
#define MPU9150_CMPS_XOUT_H        0x4B   // R
#define MPU9150_CMPS_YOUT_L        0x4C   // R
#define MPU9150_CMPS_YOUT_H        0x4D   // R
#define MPU9150_CMPS_ZOUT_L        0x4E   // R
#define MPU9150_CMPS_ZOUT_H        0x4F   // R


// I2C address 0x69 could be 0x68 depends on your wiring. 
int MPU9150_I2C_ADDRESS = 0x68;


//Variables where our values can be stored
int cmps[3];
int accl[3];
int gyro[3];
int temp;

// ------------------------------- i2cSingleRegisterClass -------------------------
void mpu9150Class::begin(const char* mod, TwoWire *_wire, int32_t _standbyPin, uint32_t _updateDelay)
{
   if(_standbyPin > 0)
  {
	pinMode(_standbyPin, OUTPUT);
	digitalWrite(_standbyPin, LOW);
  }

  uint32_t _frameSync = 6;
  pinMode(_frameSync, OUTPUT);
  digitalWrite(_frameSync, LOW);
  
  myWire = _wire;
  
   // Initialize the 'Wire' class for the I2C-bus.
  _wire->begin();
  myUpdateDelay = _updateDelay;
  
  MQTTBaseHandler::begin(mod, true);
  
  //give the slave a slight delay so it can turn on.
  delay(50);
  
  // Clear the 'sleep' bit to start the sensor.
  mpu9150Class::writeSensor(MPU9150_PWR_MGMT_1, 0);

  mpu9150Class::setupCompass();
  

  
}

void mpu9150Class::update(void)
{
  if(millis() > myTick + myUpdateDelay) {
    myTick = millis();
	
    sendMQTTTempData();
	sendMQTTCompassData();
	sendMQTTGyroData();
	sendMQTTAccelData();
	
  }
}

uint8_t mpu9150Class::decode(void)
{
  int8_t j = isTopicThisModule();
  if(j == 0)
  {
	  return 0;
  }
  
  if(COMM.compare_token(&COMM.topic[j],"STATUS")) {
    sendMQTTTempData();
	sendMQTTCompassData();
	sendMQTTGyroData();
	sendMQTTAccelData();
    return 1;
  }
}

void mpu9150Class::getTemp(float& temp)
{
	temp = ( (float) mpu9150Class::readSensor(MPU9150_TEMP_OUT_L,MPU9150_TEMP_OUT_H) + 12412.0f) / 340.0f;
}

void mpu9150Class::sendMQTTTempData()
{
	float temp;
	getTemp(temp);
	COMM.sendMessage((const char*)myModule, "DEG_C", temp);	
}

void mpu9150Class::getCompassData(int& x, int& y, int& z)
{
	x = mpu9150Class::readSensor(MPU9150_CMPS_XOUT_L,MPU9150_CMPS_XOUT_H);
	y = mpu9150Class::readSensor(MPU9150_CMPS_YOUT_L,MPU9150_CMPS_YOUT_H);
	z = mpu9150Class::readSensor(MPU9150_CMPS_ZOUT_L,MPU9150_CMPS_ZOUT_H);
}

void mpu9150Class::sendMQTTCompassData()
{
	int x;
	int y;
	int z;
	getCompassData(x,y,x);
	
	COMM.sendMessage((const char*)myModule, "COMPASS_X", x);	
	COMM.sendMessage((const char*)myModule, "COMPASS_Y", y);	
	COMM.sendMessage((const char*)myModule, "COMPASS_Z", z);	
}

void mpu9150Class::getGyroData(int& x, int& y, int& z)
{
	x = mpu9150Class::readSensor(MPU9150_GYRO_XOUT_L,MPU9150_GYRO_XOUT_H);
	y = mpu9150Class::readSensor(MPU9150_GYRO_YOUT_L,MPU9150_GYRO_YOUT_H);
	z = mpu9150Class::readSensor(MPU9150_GYRO_ZOUT_L,MPU9150_GYRO_ZOUT_H);
}

void mpu9150Class::sendMQTTGyroData()
{
	int x;
	int y;
	int z;
	getGyroData(x,y,x);
	
	COMM.sendMessage((const char*)myModule, "GYRO_X", x);	
	COMM.sendMessage((const char*)myModule, "GYRO_Y", y);	
	COMM.sendMessage((const char*)myModule, "GYRO_Z", z);	
}

void mpu9150Class::getAccelData(int& x, int& y, int& z)
{
	x = mpu9150Class::readSensor(MPU9150_ACCEL_XOUT_L,MPU9150_ACCEL_XOUT_H);
	y = mpu9150Class::readSensor(MPU9150_ACCEL_YOUT_L,MPU9150_ACCEL_YOUT_H);
	z = mpu9150Class::readSensor(MPU9150_ACCEL_ZOUT_L,MPU9150_ACCEL_ZOUT_H);
}

void mpu9150Class::sendMQTTAccelData()
{
	int x;
	int y;
	int z;
	getAccelData(x,y,x);
	
	COMM.sendMessage((const char*)myModule, "ACCEL_X", x);	
	COMM.sendMessage((const char*)myModule, "ACCEL_Y", y);	
	COMM.sendMessage((const char*)myModule, "ACCEL_Z", z);	
}

//http://pansenti.wordpress.com/2013/03/26/pansentis-invensense-mpu-9150-software-for-arduino-is-now-on-github/
//Thank you to pansenti for setup code.
void mpu9150Class::setupCompass(){
  MPU9150_I2C_ADDRESS = 0x0C;      //change Adress to Compass

  writeSensor(0x0A, 0x00); //PowerDownMode
  writeSensor(0x0A, 0x0F); //SelfTest
  writeSensor(0x0A, 0x00); //PowerDownMode

  MPU9150_I2C_ADDRESS = 0x69;      //change Adress to MPU

  writeSensor(0x24, 0x40); //Wait for Data at Slave0
  writeSensor(0x25, 0x8C); //Set i2c address at slave0 at 0x0C
  writeSensor(0x26, 0x02); //Set where reading at slave 0 starts
  writeSensor(0x27, 0x88); //set offset at start reading and enable
  writeSensor(0x28, 0x0C); //set i2c address at slv1 at 0x0C
  writeSensor(0x29, 0x0A); //Set where reading at slave 1 starts
  writeSensor(0x2A, 0x81); //Enable at set length to 1
  writeSensor(0x64, 0x01); //overvride register
  writeSensor(0x67, 0x03); //set delay rate
  writeSensor(0x01, 0x80);

  writeSensor(0x34, 0x04); //set i2c slv4 delay
  writeSensor(0x64, 0x00); //override register
  writeSensor(0x6A, 0x00); //clear usr setting
  writeSensor(0x64, 0x01); //override register
  writeSensor(0x6A, 0x20); //enable master i2c mode
  writeSensor(0x34, 0x13); //disable slv4
}

////////////////////////////////////////////////////////////
///////// I2C functions to get easier all values ///////////
////////////////////////////////////////////////////////////

int mpu9150Class::readSensor(int addrL, int addrH){
  myWire->beginTransmission(MPU9150_I2C_ADDRESS);
  myWire->write(addrL);
  myWire->endTransmission(false);

  myWire->requestFrom(MPU9150_I2C_ADDRESS, 1, true);
  byte L = myWire->read();

  myWire->beginTransmission(MPU9150_I2C_ADDRESS);
  myWire->write(addrH);
  myWire->endTransmission(false);

  myWire->requestFrom(MPU9150_I2C_ADDRESS, 1, true);
  byte H = myWire->read();

  return (H<<8)+L;
}

int mpu9150Class::readSensor(int addr){
  myWire->beginTransmission(MPU9150_I2C_ADDRESS);
  myWire->write(addr);
  myWire->endTransmission(false);

  myWire->requestFrom(MPU9150_I2C_ADDRESS, 1, true);
  return myWire->read();
}

int mpu9150Class::writeSensor(int addr,int data){
  myWire->beginTransmission(MPU9150_I2C_ADDRESS);
  myWire->write(addr);
  myWire->write(data);
  myWire->endTransmission(true);

  return 1;
}