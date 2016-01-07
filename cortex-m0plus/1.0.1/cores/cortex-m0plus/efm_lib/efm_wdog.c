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

#include "efm_wdog.h"

void initWdog(void)
{
  WDOG->CTRL = WDOG_CTRL_CLKSEL_LFRCO | wdogPeriod_64k << 8;
}

void WDOG_Feed(void)
{
  if(!(WDOG->CTRL & WDOG_CTRL_EN) || (WDOG->SYNCBUSY & WDOG_SYNCBUSY_CMD)) { // do not feed if disabled
    return;
  }
  while(WDOG->SYNCBUSY & WDOG_SYNCBUSY_CTRL); // wait for other writes to complete
  WDOG->CMD = WDOG_CMD_CLEAR;
}

