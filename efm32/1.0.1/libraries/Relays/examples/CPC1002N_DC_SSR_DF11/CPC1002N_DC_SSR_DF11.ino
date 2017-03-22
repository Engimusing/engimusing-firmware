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
  
  Example for how to setup the CPC1002N DC SSR DF 11 board connected to the ZGUSB Engimusing board
  There are two CPC1002N devices on the DF 11 board and a 3 color LED on the ZGUSB. This example
  does not do much unless you wire up the relays and GPIOs but it shows how to set up the sketch.
  See https://www.engimusing.com/products/ssr_dc-2 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include "Arduino.h"

#define GPIO0     2
#define GPIO1     3
#define GPIO2     4
#define GPIO3     5
#define DCR0_ON   6
#define DCR1_ON  10

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GPIO0,   OUTPUT);
  pinMode(GPIO1,   OUTPUT);
  pinMode(GPIO2,   OUTPUT);
  pinMode(GPIO3,   OUTPUT);
  pinMode(DCR0_ON, OUTPUT);
  pinMode(DCR1_ON, OUTPUT);
}

void loop()
{
  digitalWrite(DCR1_ON, HIGH);
  digitalWrite(GPIO3, HIGH);
  digitalWrite(GPIO1, HIGH);
  digitalWrite(DCR0_ON, HIGH);
  digitalWrite(GPIO0, HIGH);
  digitalWrite(GPIO2, HIGH);

  delay(250);

  digitalWrite(DCR1_ON, LOW);
  digitalWrite(GPIO3, LOW);
  digitalWrite(GPIO1, LOW);
  digitalWrite(DCR0_ON, LOW);
  digitalWrite(GPIO0, LOW);
  digitalWrite(GPIO2, LOW);

  delay(250);
 }
