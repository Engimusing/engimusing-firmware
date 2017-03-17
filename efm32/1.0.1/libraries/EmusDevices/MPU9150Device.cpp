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

#include <Arduino.h>

#include <MPU9150Device.h>
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
#define MPU9150_CMPS_XOUT_L        0x03   // R
#define MPU9150_CMPS_XOUT_H        0x04   // R
#define MPU9150_CMPS_YOUT_L        0x05   // R
#define MPU9150_CMPS_YOUT_H        0x06   // R
#define MPU9150_CMPS_ZOUT_L        0x07   // R
#define MPU9150_CMPS_ZOUT_H        0x08   // R
#define MPU9150_CMPS_CNTL       0x0A   // R


// I2C address 0x69 could be 0x68 depends on your wiring. 
#define MPU9150_I2C_ADDRESS 0x68
#define MPU9150_CMPS_ADDRESS 0x0C
void MPU9150Device::begin(TwoWire &wire, int32_t standbyPin, int32_t frameSyncPin)
{    
    myCurrentI2CAddress = MPU9150_I2C_ADDRESS;
    if(standbyPin > 0)
  {
	pinMode(standbyPin, OUTPUT);
	digitalWrite(standbyPin, LOW);
  }

  if(frameSyncPin > 0)
  {
   pinMode(frameSyncPin, OUTPUT);
   digitalWrite(frameSyncPin, LOW);
  }
  
  myWire = &wire;
  
   // Initialize the 'Wire' class for the I2C-bus.
  myWire->begin();
  
  // Clear the 'sleep' bit to start the sensor.
  writeSensor(MPU9150_PWR_MGMT_1, 0);

  setupCompass();
}


void MPU9150Device::getTemp(float& temp)
{
	temp = (( (float) MPU9150Device::readSensor(MPU9150_TEMP_OUT_L,MPU9150_TEMP_OUT_H)) / 340.0f) + 35.0;
}

void MPU9150Device::readCompassData()
{
    myCurrentI2CAddress = MPU9150_CMPS_ADDRESS;      //change Adress to Compass
  
    writeSensor(MPU9150_CMPS_CNTL, 0x01); //trigger single read
    delay(10);

    myCompassX = readSensor(MPU9150_CMPS_XOUT_L,MPU9150_CMPS_XOUT_H);
	myCompassY = readSensor(MPU9150_CMPS_YOUT_L,MPU9150_CMPS_YOUT_H);
	myCompassZ = readSensor(MPU9150_CMPS_ZOUT_L,MPU9150_CMPS_ZOUT_H);
    
    myCurrentI2CAddress = MPU9150_I2C_ADDRESS;      //change Adress to MPU
}

void MPU9150Device::getCompassData(int& x, int& y, int& z)
{
    readCompassData();
    
    x = myCompassX;
    y = myCompassY;
    z = myCompassZ;
}

int MPU9150Device::readGyroX()
{
    return readSensor(MPU9150_GYRO_XOUT_L,MPU9150_GYRO_XOUT_H);
}

int MPU9150Device::readGyroY()
{
    return readSensor(MPU9150_GYRO_YOUT_L,MPU9150_GYRO_YOUT_H);
}

int MPU9150Device::readGyroZ()
{
    return readSensor(MPU9150_GYRO_ZOUT_L,MPU9150_GYRO_ZOUT_H);
}

void MPU9150Device::getGyroData(int& x, int& y, int& z)
{
	x = readGyroX();
	y = readGyroY();
	z = readGyroZ();
}

int MPU9150Device::readAccelX()
{
    return readSensor(MPU9150_ACCEL_XOUT_L,MPU9150_ACCEL_XOUT_H);
}

int MPU9150Device::readAccelY()
{
    return readSensor(MPU9150_ACCEL_YOUT_L,MPU9150_ACCEL_YOUT_H);
}

int MPU9150Device::readAccelZ()
{
    return readSensor(MPU9150_ACCEL_ZOUT_L,MPU9150_ACCEL_ZOUT_H);
}

void MPU9150Device::getAccelData(int& x, int& y, int& z)
{
	x = readAccelX();
	y = readAccelY();
	z = readAccelZ();
}

//http://pansenti.wordpress.com/2013/03/26/pansentis-invensense-mpu-9150-software-for-arduino-is-now-on-github/
//Thank you to pansenti for setup code.
void MPU9150Device::setupCompass()
{
  
  writeSensor(MPU9150_USER_CTRL, 0x00); //clear usr setting
  writeSensor(MPU9150_INT_PIN_CFG, 0x02); //clear usr setting
  
  myCurrentI2CAddress = MPU9150_CMPS_ADDRESS;      //change Adress to Compass

  writeSensor(MPU9150_CMPS_CNTL, 0x01); //PowerDownMode
  delay(10);
  
  myCurrentI2CAddress = MPU9150_I2C_ADDRESS;      //change Adress to MPU

}

////////////////////////////////////////////////////////////
///////// I2C functions to get easier all values ///////////
////////////////////////////////////////////////////////////

int MPU9150Device::readSensor(int addrL, int addrH){
  myWire->beginTransmission(myCurrentI2CAddress);
  myWire->write(addrL);
  myWire->endTransmission(false);

  myWire->requestFrom(myCurrentI2CAddress, 1, true);
  byte L = myWire->read();

  myWire->beginTransmission(myCurrentI2CAddress);
  myWire->write(addrH);
  myWire->endTransmission(false);

  myWire->requestFrom(myCurrentI2CAddress, 1, true);
  byte H = myWire->read();
  
  return (int16_t)(H<<8)+L;
}

int MPU9150Device::readSensor(int addr){
  myWire->beginTransmission(myCurrentI2CAddress);
  myWire->write(addr);
  myWire->endTransmission(false);

  myWire->requestFrom(myCurrentI2CAddress, 1, true);
  return myWire->read();
}

int MPU9150Device::writeSensor(int addr,int data){
  myWire->beginTransmission(myCurrentI2CAddress);
  myWire->write(addr);
  myWire->write(data);
  myWire->endTransmission(true);
 
  return 1;
}

Device::ValueStruct MPU9150Device::readValue(int index)
{
    Device::ValueStruct output;
    if(index == 0)
    {
        float temp;
        getTemp(temp);
        output.type = Device::TypeFloat;
        output.value.decimal = temp;
        output.name = "DEG_C";
    }
    else if(index == 1)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readGyroX();
        output.name = "GYRO_X";
    }
    else if(index == 2)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readGyroY();
        output.name = "GYRO_Y";
    }
    else if(index == 3)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readGyroZ();
        output.name = "GYRO_Z";
    }
    else if(index == 4)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readAccelX();
        output.name = "ACCEL_X";
    }
    else if(index == 5)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readAccelY();
        output.name = "ACCEL_Y";
    }
    else if(index == 6)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readAccelZ();
        output.name = "ACCEL_Z";
    }
    else if(index == 7)
    {
        readCompassData();
        output.type = Device::TypeFloat;
        output.value.decimal = myCompassX;
        output.name = "COMPASS_X";
    }
    else if(index == 8)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = myCompassY;
        output.name = "COMPASS_Y";
    }
    else if(index == 9)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = myCompassZ;
        output.name = "COMPASS_Z";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

float MPU9150Device::numValues()
{
    return 10; 
}

