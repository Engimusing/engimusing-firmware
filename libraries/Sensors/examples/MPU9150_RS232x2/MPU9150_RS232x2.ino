/*
  Copyright (c) 2016-2018 Engimusing LLC.  All right reserved.
  
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
    There are 2 devices on this board. An LED and a MPU9150 9-axis Motion Tracker.
    See https://www.engimusing.com for more information about the board.
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu.
#endif

#include <MPU9150Device.h>
#include <Wire.h>

MPU9150Device MPU9150;
TogglePin led;
Timeout serialTimer;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println("Simple MPU9150 example 0");
  Serial1.println("Simple MPU9150 example 1");
  led.begin(1000);
  serialTimer.begin(1000,true);
 
  
  MPU9150.begin(Wire0, 3, 6);
}

void loop()
{


  MPU9150.update();

  
  
  if(serialTimer.update())
  { 
    float temp;
    MPU9150.getTemp(temp);
    Serial.print("temperature = ");
    Serial.print(temp);
    Serial.println(" C");

    int cX;
    int cY;
    int cZ;
    MPU9150.getCompassData(cX,cY,cZ);
    Serial.print("Compass = (");
    Serial.print(cX);
    Serial.print(",");
    Serial.print(cY);
    Serial.print(",");
    Serial.print(cZ);
    Serial.println(")");

    int gX;
    int gY;
    int gZ;
    MPU9150.getGyroData(gX,gY,gZ);
    Serial.print("Gyro = (");
    Serial.print(gX);
    Serial.print(",");
    Serial.print(gY);
    Serial.print(",");
    Serial.print(gZ);
    Serial.println(")");

    int aX;
    int aY;
    int aZ;

    MPU9150.getAccelData(aX,aY,aZ);
    Serial.print("Acceleration = (");
    Serial.print(aX);
    Serial.print(",");
    Serial.print(aY);
    Serial.print(",");
    Serial.print(aZ);
    Serial.println(")");
  
    Serial1.print("temperature = ");
    Serial1.print(temp);
    Serial1.println(" C");

    Serial1.print("Compass = (");
    Serial1.print(cX);
    Serial1.print(",");
    Serial1.print(cY);
    Serial1.print(",");
    Serial1.print(cZ);
    Serial1.println(")");

    Serial1.print("Gyro = (");
    Serial1.print(gX);
    Serial1.print(",");
    Serial1.print(gY);
    Serial1.print(",");
    Serial1.print(gZ);
    Serial1.println(")");

    Serial1.print("Acceleration = (");
    Serial1.print(aX);
    Serial1.print(",");
    Serial1.print(aY);
    Serial1.print(",");
    Serial1.print(aZ);
    Serial1.println(")");
  
  }
  led.update();
}