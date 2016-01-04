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

#include "efm_pin_config.h"
#include "leds.h"
#include "pins_arduino.h"

void ledRedOff(void)   {GPIO->P[ledPorts[RED_LED]].DOUTSET   = (1 << ledPins[RED_LED]);}
void ledRedOn(void)    {GPIO->P[ledPorts[RED_LED]].DOUTCLR   = (1 << ledPins[RED_LED]);}
void ledGreenOff(void) {GPIO->P[ledPorts[GREEN_LED]].DOUTSET = (1 << ledPins[GREEN_LED]);}
void ledGreenOn(void)  {GPIO->P[ledPorts[GREEN_LED]].DOUTCLR = (1 << ledPins[GREEN_LED]);}
void ledBlueOff(void)  {GPIO->P[ledPorts[BLUE_LED]].DOUTSET  = (1 << ledPins[BLUE_LED]);}
void ledBlueOn(void)   {GPIO->P[ledPorts[BLUE_LED]].DOUTCLR  = (1 << ledPins[BLUE_LED]);}

void ledAllOff(void)
{
  GPIO->P[ledPorts[RED_LED]].DOUTSET   = (1 << ledPins[RED_LED]);
  GPIO->P[ledPorts[GREEN_LED]].DOUTSET = (1 << ledPins[GREEN_LED]);
  GPIO->P[ledPorts[BLUE_LED]].DOUTSET  = (1 << ledPins[BLUE_LED]);
}

void ledAllOn(void)
{
  GPIO->P[ledPorts[RED_LED]].DOUTCLR   = (1 << ledPins[RED_LED]);
  GPIO->P[ledPorts[GREEN_LED]].DOUTCLR = (1 << ledPins[GREEN_LED]);
  GPIO->P[ledPorts[BLUE_LED]].DOUTCLR  = (1 << ledPins[BLUE_LED]);
}


