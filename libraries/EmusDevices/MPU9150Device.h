///@file MPU9150Device.h
///@brief Contains the MPU9150Device class which is a Device derived for accessing an MPU9150 9-axis motion sensor
///Datasheet link https://www.invensense.com/wp-content/uploads/2015/02/MPU-9150-Datasheet.pdf
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#pragma once

#include "Arduino.h"

#include "Device.h"

class TwoWire;

///@brief Class for accessing an MPU9150 9-axis motion sensor.
///Datasheet link https://www.invensense.com/wp-content/uploads/2015/02/MPU-9150-Datasheet.pdf
class MPU9150Device : public Device
{
 
    public:
        ///@brief Initialize the settings for the TwoWire and pins to use to access the MPU9150
        ///@param [in] wire TwoWire object that is connected to the MPU9150
        ///@param [in] standbyPin Pin that is connected to the standby pin on the MPU9150
        ///@param [in] frameSyncPin Pin that is connected to the frame sync pin on the MPU9150
        virtual void begin(TwoWire &wire, int32_t standbyPin, int32_t frameSyncPin);
         
        ///@brief Get the temperature in Celsius from the MPU9150
        ///@param [out] temp Temperature in Celsius read from the MPU9150
        virtual void getTemp(float& temp);
        ///@brief Get the current compass data from the MPU9150
        ///@param [out] x Raw compass data for the x axis
        ///@param [out] y Raw compass data for the y axis
        ///@param [out] z Raw compass data for the z axis
        virtual void getCompassData(int& x, int& y, int& z);
        ///@brief Get the current gyroscope data from the MPU9150
        ///@param [out] x Raw gyroscope data for the x axis
        ///@param [out] y Raw gyroscope data for the y axis
        ///@param [out] z Raw gyroscope data for the z axis
        virtual void getGyroData(int& x, int& y, int& z);
        ///@brief Get the current acceleration data from the MPU9150
        ///@param [out] x Raw acceleration data for the x axis
        ///@param [out] y Raw acceleration data for the y axis
        ///@param [out] z Raw acceleration data for the z axis
        virtual void getAccelData(int& x, int& y, int& z);

         ///@brief Device interface function for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = DEG_C (float)
        ///index 1,2,3 = GYRO_X, GYRO_Y, GYRO_Z (float)
        ///index 4,5,6 = ACCEL_X, ACCEL_Y, ACCEL_Z (float)
        ///index 7,8,9 = COMPASS_X, COMPASS_Y, COMPASS_Z (float)
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Number of value types available to read.
        ///@return Always returns 10 for this class.
        virtual uint32_t numValues(); 
        
    protected:   

        virtual void setupCompass();
        
        virtual void readCompassData();
                
        virtual int readGyroX();
        virtual int readGyroY();
        virtual int readGyroZ();
        
        virtual int readAccelX();
        virtual int readAccelY();
        virtual int readAccelZ();
        
        virtual int readSensor(int addrL, int addrH);
        virtual int readSensor(int addr);
        virtual int writeSensor(int addr,int data);

    protected:
    
        TwoWire *myWire; 
        int myCurrentI2CAddress;
        
        int myCompassX;
        int myCompassY;
        int myCompassZ;

};