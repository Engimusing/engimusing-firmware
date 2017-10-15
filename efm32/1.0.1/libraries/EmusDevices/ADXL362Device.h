///
///@file ADXL362Device.h
///@brief Contains ADXL362Device class which is the Device implementation for the ADXL362 accelerometer
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
///

#pragma once

#include "Arduino.h"

#include "Device.h"

//the following gave resonable values if you need really accurate absolute temperatures you need to calculate a new bias
#define DEFAULT_TEMP_BAIS (350 + 290) 

class SPIClass;
class UARTClass;

///@brief Device implementation for the ADXL362 accelerometer. 
///Datasheet link: http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL362.pdf
class ADXL362Device : public Device
{
   public:
   
        ///@brief Sensitivity setting options for the ADXL362
        enum Sensitivity
        {
            TWO_GEES,
            FOUR_GEES,
            EIGHT_GEES
        }; 
   
         //
        // Basic Device control and readback functions
        //
        ///@brief Setup function for the device. Configures the settings for using the ADXL362
        ///@param [in] vddPin Pin which is connected to the Vio pin on the ADXL362
        ///@param [in] vsPin Pin which is connected to the Vs pin on the ADXL362
        ///@param [in] slaveSelectPin Pin which is connected to the CS pin on the ADXL32
        ///@param [in] ADXL_SPI Spi class to use for this device. 
        ///@param [in] maxGeesSetting Sensitivity setting to use for this device. (Default is 2 Gs)
        ///@param [in] tempBias Temperature bias to use for this device. The temperature sensor on the ADXL requires calibration to be accurate. (Default is 640)
        ///@param [in] debugSerial Serial port to use for debug printouts (Default is NULL and there will be no debug printouts)
        virtual void begin(int vddPin, int vsPin, int slaveSelectPin, SPIClass *ADXL_SPI, Sensitivity maxGeesSetting = TWO_GEES, int16_t tempBias = DEFAULT_TEMP_BAIS, UARTClass *debugSerial = 0);
        
        ///@brief Turn on measurement mode. Called by begin() to start the ADXL362 taking measurements.
        void beginMeasure(); 
        
        ///@brief Read the X data for the acceleration.
        ///@return Raw acceleration in the X-axis from the ADXL362
        int readXData();
        ///@brief Read the Y data for the acceleration.
        ///@return Raw acceleration in the Y-axis from the ADXL362
        int readYData();
        ///@brief Read the Z data for the acceleration.
        ///@return Raw acceleration in the Z-axis from the ADXL362
        int readZData();
        ///@brief Read the temperature data.
        ///@return Raw temperature data from the ADXL362
        int readTemp();
        
        
        ///@brief Read all axis's and the temperature at the same time
        ///@param [in] xData Raw acceleration in the X-Axis
        ///@param [in] yData Raw acceleration in the Y-Axis
        ///@param [in] zData Raw acceleration in the Z-Axis
        ///@param [in] temperature Raw temperature data
        void readXYZTData(int &xData, int &yData, int &zData, int &temperature);
        
        ///@brief After calling sampleXYZT all the getSample and other get functions have data from the same instance.
        ///@return Raw acceleration in the X-axis from the last time sampleXYZT was called.
        int16_t getSampleX();
        ///@brief After calling sampleXYZT all the getSample functions have data from the same instance.
        ///@return Raw acceleration in the Y-axis from the last time sampleXYZT was called.
        int16_t getSampleY();
        ///@brief After calling sampleXYZT all the getSample functions have data from the same instance.
        ///@return Raw acceleration in the Z-axis from the last time sampleXYZT was called.
        int16_t getSampleZ();
        ///@brief After calling sampleXYZT all the getSample functions have data from the same instance.
        ///@return Raw temperature data from the last time sampleXYZT was called.
        int16_t getSampleT();
        
        ///@brief Get the last sampleXYZT X sample converted to Gees
        ///@return Acceleration in the X-axis converted to Gees
        float getXGees();
        ///@brief Get the last sampleXYZT Y sample converted to Gees
        ///@return Acceleration in the Y-axis converted to Gees
        float getYGees();
        ///@brief Get the last sampleXYZT Z sample converted to Gees
        ///@return Acceleration in the Z-axis converted to Gees
        float getZGees();
        ///@brief Get the last sampleXYZT temperature sample converted to Celsius
        ///@return Temperature with the temp bias applied and converted to Celsius
        float getTCelsius();
        
        ///@brief Get all the acceleration and temperature data for a single sample time. Use the get functions to get the results
        void sampleXYZT();
     
        //
        // Activity/Inactivity interrupt functions
        //
        void setupDCActivityInterrupt(int threshold, byte time);	
        void setupDCInactivityInterrupt(int threshold, int time);
        void setupACActivityInterrupt(int threshold, byte time);
        void setupACInactivityInterrupt(int threshold, int time);
        
        // need to add the following functions
        // void mapINT1(
        // void mapINT2
        // void autoSleep
        // void activityInterruptControl
        //		-Activity, Inactivity, Both
        //		- Referenced, Absolute
        //		- Free Fall, Linked Mode, Loop Mode
             
        ///@brief Device overridden function which reads one of the values from the device.
        ///@param [in] index Value index to read
        ///@return ValueStruct which contains the name and value for the requested index.
        ///@details index 0 = X_GEES (float)
        ///index 1 = Y_GEES (float) 
        ///index 2 = Z_GEES (float)
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Gets the number of values this device has (3 in this case)
        ///@return Number of different values this device has (always 3 for the ADXL362)
        virtual uint32_t numValues(); 
        
        ///@brief Change the sensitivity currently being used by the ADXL362
        ///@param [in] maxGeesSetting Sensitivity setting to use
        void setMaxGeesSetting(Sensitivity maxGeesSetting);
        
   protected:
        //  Low-level SPI control, to simplify overall coding
        byte SPIreadOneRegister(byte regAddress);
        void SPIwriteOneRegister(byte regAddress, byte regValue);
        int  SPIreadTwoRegisters(byte regAddress);
        void SPIwriteTwoRegisters(byte regAddress, int twoRegValue);
        

   protected:   
        int mySlaveSelectPin;
        
        int16_t mySampleX;
        int16_t mySampleY;
        int16_t mySampleZ;
        int16_t mySampleT;
        
        int16_t myTempBias;
        
        Sensitivity myMaxGeesSetting;
        float myAxisScalar;
        
        
        SPIClass *mySpi;
        UARTClass *myDebugSerial;
	
      
};