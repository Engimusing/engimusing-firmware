///@file TCS3200Device.h
///@brief Contains TCS3200Device class which is a Device derived class for accessing a TCS3200 color sensor
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/TCS3200_TCS3210-A_Color_Light_to_Frequency_Converter.pdf
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

///@brief Class for connecting to a TCS3200 color sensor.
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/TCS3200_TCS3210-A_Color_Light_to_Frequency_Converter.pdf
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
        
        ///@brief Initializer function for setting up the pins to connect to the TCS3200Device
        ///@param [in] s0Pin Pin connected to the s0Pin on the TCS3200
        ///@param [in] s1Pin Pin connected to the s1Pin on the TCS3200
        ///@param [in] s2Pin Pin connected to the s2Pin on the TCS3200
        ///@param [in] s3Pin Pin connected to the s3Pin on the TCS3200
        ///@param [in] taosOutPin Pin connected to the taos out pin on the TCS3200
        ///@param [in] mode Sets the sensitivity for the color sensor. 0 turns off the device and 1-3 set different sensitivities with 1 being the most sensitive.
        virtual void begin(uint8_t s0Pin, uint8_t s1Pin, uint8_t s2Pin, uint8_t s3Pin, uint8_t taosOutPin, uint8_t mode = 1);
        
        ///@brief Get an intensity reading for the specified color.
        ///@param [in] color Color to read the intensity of.
        ///@return Frequency in hertz returned from the sensor for the particular color.
        virtual float readColorHertz(Color color);
       
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = WHITE_HZ (float) - current reading for the color white
        ///index 1 = RED_HZ (float) - current reading for the color red
        ///index 2 = BLUE_HZ (float) - current reading for the color blue
        ///index 3 = GREEN_HZ (float) - current reading for the color green
        virtual Device::ValueStruct readValue(int index);
        
        ///@brief Number of value types available to read.
        ///@return Always returns 4 for this class.
        virtual uint32_t numValues();   
        
   protected:   
   
        ///@details Operation modes area, controlled by hi/lo settings on S0 and S1 pins.
        ///setting mode to zero will put taos into low power mode. taosMode(0);
        virtual void setTaosMode(uint8_t mode);
        
        uint8_t myS0Pin;
        uint8_t myS1Pin;
        uint8_t myS2Pin;
        uint8_t myS3Pin;
        uint8_t myTaosOutPin;
        uint8_t myMode;
      
};