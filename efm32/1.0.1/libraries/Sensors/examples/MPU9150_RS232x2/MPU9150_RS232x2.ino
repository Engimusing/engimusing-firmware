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
/* Example for how to print out readings from the MPU9150 RS232x2 Engimusing board
 *  See http://www.engimusing.com/products/mpu9150-3 for more information about the board.
 */

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <Wire.h>

#include "Arduino.h"

#include <MPU9150Device.h>

MPU9150Device MPU9150;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Simple MPU9150 example 0");
  Serial1.println("Simple MPU9150 example 1");

  //Initialize the Humidity sensor
  MPU9150.begin(Wire0, 3, 6);
}

void loop()
{

  static int on = HIGH;

  digitalWrite(LED_BUILTIN, on);   // turn the LED on (HIGH is the voltage level)
  
  
  float temp;
  MPU9150.getTemp(temp);
  Serial.print("temperature = ");
  Serial.print(temp);
  Serial.println(" C");
  
  Serial1.print("temperature = ");
  Serial1.print(temp);
  Serial1.println(" C");
  
  int x;
  int y;
  int z;
  MPU9150.getCompassData(x,y,z);
  Serial.print("Compass = (");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println(")");
  
  Serial1.print("Compass = (");
  Serial1.print(x);
  Serial1.print(",");
  Serial1.print(y);
  Serial1.print(",");
  Serial1.print(z);
  Serial1.println(")");
  
  
  MPU9150.getGyroData(x,y,z);
  Serial.print("Gyro = (");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println(")");
  
  Serial1.print("Gyro = (");
  Serial1.print(x);
  Serial1.print(",");
  Serial1.print(y);
  Serial1.print(",");
  Serial1.print(z);
  Serial1.println(")");
  
  MPU9150.getAccelData(x,y,z);
  Serial.print("Acceleration = (");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println(")");
  
  Serial1.print("Acceleration = (");
  Serial1.print(x);
  Serial1.print(",");
  Serial1.print(y);
  Serial1.print(",");
  Serial1.print(z);
  Serial1.println(")");
  
  delay(1000);                       // wait for a second
  
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
  
}
