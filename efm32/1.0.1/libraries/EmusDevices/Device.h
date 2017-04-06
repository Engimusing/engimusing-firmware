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
//Interface for a device that is used by commuication classes to get information from a device 
// without knowing the specifics about the device
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
        virtual void update() {};
        
        virtual ValueStruct readValue(int index) = 0;
        
        virtual uint32_t numValues()
        {
            return 0;
        }
        
};