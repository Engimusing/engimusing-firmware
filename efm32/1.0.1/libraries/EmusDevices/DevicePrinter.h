///@file DevicePrinter.h
///@brief Contains the DevicePrinter class for periodically printing information from a Device based class.
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

#include "efm_lib/timeout.h"

class Device;
class Print;
//Class for periodically printing information about the current state of a device
class DevicePrinter
{
    public:
       DevicePrinter();
       
    public:
        virtual void begin(Print &printer, Device &device, int delay, const char *deviceName);
        virtual void update();
        
    private:
        Print *myPrinter;
        Device *myDevice;
        Timeout myTimeout;
        const char *myDeviceName;
        int myLastPrint;
};