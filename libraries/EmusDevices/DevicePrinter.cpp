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

#include <DevicePrinter.h>
#include <Arduino.h>
#include <Device.h>

//Class for periodically printing information about the current state of a device
DevicePrinter::DevicePrinter()
{
    
}
   

void DevicePrinter::begin(Print &printer, Device &device, int delay, const char *deviceName)
{
    myPrinter = &printer;
    myDevice = &device;
    myTimeout.begin(delay);
    myDeviceName = deviceName;
}

void DevicePrinter::update()
{
    if(myTimeout.update()) 
    {
        myPrinter->print(myDeviceName);
        myPrinter->println(" values:");
        
        for(int i = 0; i < myDevice->numValues(); i++)
        {
            Device::ValueStruct valueStruct = myDevice->readValue(i);
            myPrinter->print(valueStruct.name);
            myPrinter->print(" = ");
            switch(valueStruct.type)
            {
                case Device::TypeFloat:
                    myPrinter->println(valueStruct.value.decimal);
                    break;
                case Device::TypeInt:
                   myPrinter->println(valueStruct.value.integer);
                    break;
                case Device::TypeBool:
                    if(valueStruct.value.boolean)
                    {
                        myPrinter->println("true");
                    }
                    else
                    {
                        myPrinter->println("false");
                    }
                    break;
                case Device::TypeCharArray:
                    myPrinter->println(valueStruct.value.charArray);
                    break;
            }
        }
    }
}        
    