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

//the following gave resonable values if you need really accurate absolute temperatures you need to calculate a new bias
#define DEFAULT_TEMP_BAIS (350 + 290) 

class SPIClass;
class UARTClass;

class ADXL362Device : public Device
{
   public:
   
        enum Sensitivity
        {
            TWO_GEES,
            FOUR_GEES,
            EIGHT_GEES
        }; 
   
         //
        // Basic Device control and readback functions
        //
        virtual void begin(int vddPin, int vsPin, int slaveSelectPin, SPIClass *ADXL_SPI, Sensitivity maxGeesSetting = TWO_GEES, int16_t tempBias = DEFAULT_TEMP_BAIS, UARTClass *debugSerial = 0);
        
        void beginMeasure(); 
        
        int readXData();
        int readYData();
        int readZData();
        int readTemp();
        
        void readXYZTData(int &xData, int &yData, int &zData, int &temperature);
        
        int16_t getSampleX();
        int16_t getSampleY();
        int16_t getSampleZ();
        int16_t getSampleT();
        
        float getXGees();
        float getYGees();
        float getZGees();
        float getTCelsius();
        
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
             
        virtual Device::ValueStruct readValue(int index);
        virtual uint32_t numValues(); 
        
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