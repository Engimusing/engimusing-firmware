/*
  Copyright (c) 2015 Engimusing LLC.  All right reserved.

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

#include "Arduino.h"
#include "tickHandler.h"

tickHandler::tickHandler()
{
  interval = 0;
  current = 0;
}

void tickHandler::setInterval(uint32_t intval)
{
  interval = intval;
  current = 0;
}

volatile bool tickHandler::serviceTick(void)
{
  if(interval == 0) {
    return false;
  }
  if(current <= 0) {
    current = interval;
    return true;
  } else {
    current--;
    return false;
  }
}

void tickHandler::print(void)
{
  Serial.printf("\r\n");
  Serial.printf("interval = %d current = %d\r\n",interval,current);
  Serial.printf("\r\n");
}
