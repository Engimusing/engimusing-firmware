/*
  Copyright (c) 2016-2017 Engimusing LLC.  All right reserved.
  
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
/* Example for how to print out readings from the HTU21D  DF11 board using the ZB USB Engimusing board
    There are 2 devices on this board. An LED and a HTU21D humidity and temperature sensor.
    See https://www.engimusing.com/products/htu21d-1 for more information about the board.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include <HTU21DDevice.h>
#include <Wire.h>

HTU21DDevice HTU21D;

void setup()
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple HTU21D example 0");

  
  HTU21D.begin(Wire0, 10);
}

int lastMillis = 0; // store the last time the current was printed.
int printDelay = 1000; //print every second.

void loop()
{

  static int on = HIGH;

  HTU21D.update();

  if(millis() - lastMillis > printDelay)
  {
    lastMillis = millis();

    digitalWrite(LED_BUILTIN, on);   // toggle the LED (HIGH is the voltage level)
    
    float hum = HTU21D.calcHumidity(HTU21D.readHumidity());
    float temp = HTU21D.calcTemp(HTU21D.readTemp());
    delay(1000);                       // wait for a second
    Serial.print("temperature = ");
    Serial.print(temp);
    Serial.print("   humidity = ");
    Serial.println(hum);

    on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
  }
}