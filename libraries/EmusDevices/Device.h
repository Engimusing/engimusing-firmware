///@file Device.h
///@brief Contains the Device interface which is a common interface for the Device classes
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
///@brief Interface for a device that is used by communication classes to get information from a device 
/// without knowing the specifics about the device
class Device
{
    public:
       enum ValueType { TypeFloat, TypeInt, TypeBool, TypeCharArray, TypeInvaild };
       
       union ValueUnion{
          float decimal;
          int32_t integer; // Assumes float is 32 bits wide
          bool boolean;
          const char * charArray;
       };
       
       ///@brief Class for passing data from a Device. It can contain a float, integer, boolean, or string.
       ///Check the type member variable to find out what type of data is stored in the object.
        struct ValueStruct{
           
           ValueStruct()
            : type(TypeInvaild)
            , name("")
           {
               value.decimal = 0;
           }
           
           ValueType type;
           ValueUnion value;
           const char *name;
       };
       
   public:
        ///@brief No op update function that is a placeholder for derived classes update() functions
        virtual void update() {};
        
        ///@brief No op write value function which is used by derived classes that have state that can be modified externally.
        ///@param [in] valueName Name of the state value to update.
        ///@param [in] value Value to set the state value to.
        ///@return True if the value was used, else false.
        ///@details Can be used to handle commands. For example the OnOffCtrlDevice checks for a valueName of CTL and values of ON or OFF.
        virtual bool writeValue(const char *valueName, const char *value) {return false;}
        
        ///@brief Abstract function used by derived classes to provide read access to device state
        ///@param [in] index Index of the value to read from the state
        ///@return ValueStruct object which contains a value, name, and type for the requested value.
         virtual ValueStruct readValue(int index) = 0;
        
        ///@brief Over-ridable function for the derived class to use to provide the number of available values.
        ///@return Number of values available to read using readValue.
        virtual uint32_t numValues()
        {
            return 0;
        }
        
        ///@brief Utility function for comparing two strings.
        ///@param [in] inStr Haystack string to look for the needle string in.
        ///@param [in] cmpStr Needle string to look for in the haystack string.
        ///@return True if the inStr contains the cmpStr.
        bool compare_string(const char* inStr, const char* cmpStr)
        {
          int8_t iLen = strlen((char*) inStr);
          int8_t cLen = strlen((char*) cmpStr);
          if(iLen < cLen) {
            return false;
          }
          for(int i = 0; i < cLen; i++) {
            if(inStr[i] != cmpStr[i]) {
              return false;
            }
          }
          return true;
        }
        
};