///@file HTU21DDevice.h
///@brief Contains the HTU21DDevice class which is a Device derived class for accessing a HTU21D temperature/Humidity Sensor
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/HTU21D_HPP845_Humidity_Temp.pdf
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

///@brief Class for accessing a HTU21 Temperature/Humidity sensor.
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/HTU21D_HPP845_Humidity_Temp.pdf
class HTU21DDevice : public Device
{
 
   public:
        ///@brief Initializer which sets up which Wire and pin are attached to the HTU21
        ///@param [in] wire TwoWire object that is physically connected to the HTU21
        ///@param [in] enablePin Pin that is connected to the enable pin on the HTU21
        virtual void begin(TwoWire &wire, int32_t enablePin);
        
        ///@brief Device interface class for accessing the current state of the device. 
        ///@param [in] index Index of the value to get.
        ///@return Current value of the value type specified by index.
        ///@details index 0 = DEG_C (float or string) - returns NOREADING if myWire is not initialized    
        ///index 1 = HUM (float or string) - float is the humidity as a relative humidity value returns NOREADING if myWire is not initialized        
        virtual Device::ValueStruct readValue(int index);
       
        ///@brief Number of value types available to read.
        ///@return Always returns 2 for this class.
        virtual uint32_t numValues(); 
        
        ///@brief Get the current raw temperature value from the HTU21
        ///@return The raw uncompensated temperature value
        ///@details Pass the result of this function to calcTemp to get the current temperature in Celsius
        virtual unsigned int readTemp();
        
        ///@brief Get the raw humidity value from the HTU21
        ///@return Raw humidity value from the HTU21
        ///@details Pass the result of this function calcHumidity to get the current relative humidity
        virtual unsigned int readHumidity();
        
        ///@brief Calculate the temperature in Celsius based on the raw temperature from the HTU21
        ///@param [in] SigTemp Pass in the result of readTemp()
        ///@return Temperature in Celsius
        virtual float calcTemp(int SigTemp);
        
        ///@brief Calculate the relative humidity
        ///@param [in] SigRH Pass in the result of readHumidity()
        ///@return Current relative humidity
        virtual float calcHumidity(int SigRH);
        
   protected:   
        TwoWire *myWire;
      
};
