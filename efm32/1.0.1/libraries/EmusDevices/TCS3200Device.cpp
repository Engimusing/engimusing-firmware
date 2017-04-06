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
  
  Example for using the TCS3200 Light Frequency Sensor on the Engimusing DF11 board
  For more info goto http://emus.us/tcs3200-1
  Modified by Tim George
  Engimusing 2014
  Original Code: http://forums.parallax.com/showthread.php/136258-Code-for-using-a-TCS3200-with-Arduino-and-a-question
  Eecher's TCS3200 program
      adapted from code found at reibot.org
  
  This shows how to read and interpret the data from the TCS3200 sensor

*/

#include <TCS3200Device.h>
#include <Arduino.h>

void TCS3200Device::begin(uint8_t s0Pin, uint8_t s1Pin, uint8_t s2Pin, uint8_t s3Pin, uint8_t taosOutPin, uint8_t mode)
{    
    myS0Pin = s0Pin;
    myS1Pin = s1Pin;
    myS2Pin = s2Pin;
    myS3Pin = s3Pin;
    myTaosOutPin = taosOutPin;
    myMode = mode;
    
    //color mode selection
    pinMode(myS0Pin,OUTPUT);
    pinMode(myS1Pin,OUTPUT); 
    
    //color response pin (only actual input from taos)
    pinMode(myTaosOutPin, INPUT); //taosOutPin pinC

    //communication freq (sensitivity) selection
    pinMode(myS2Pin,OUTPUT);
    pinMode(myS3Pin,OUTPUT);

    
}


/*
This section will return the pulseIn reading of the selected color.  
It will turn on the sensor at the start setTaosMode(myMode), and it will power off the sensor at the end setTaosMode(0)
color codes: 0=white, 1=red, 2=blue, 3=green
taosOutPin is the ouput pin of the TCS3200.
*/

float TCS3200Device::readColorHertz(Color color){ 

  //turn on sensor and use highest frequency/sensitivity setting
  setTaosMode(myMode);

  //setting for a delay to let the sensor sit for a moment before taking a reading.
  int sensorDelay = 100;

  //set the S2 and S3 pins to select the color to be sensed 
  if(color == 0){//white
    digitalWrite(myS3Pin, LOW); //S3
    digitalWrite(myS2Pin, HIGH); //S2
    // Serial.print(" w");
  }

  else if(color == 1){//red
    digitalWrite(myS3Pin, LOW); //S3
    digitalWrite(myS2Pin, LOW); //S2
    // Serial.print(" r");
  }

  else if(color == 2){//blue
    digitalWrite(myS3Pin, HIGH); //S3
    digitalWrite(myS2Pin, LOW); //S2 
    // Serial.print(" b");
  }

  else if(color == 3){//green
    digitalWrite(myS3Pin, HIGH); //S3
    digitalWrite(myS2Pin, HIGH); //S2 
    // Serial.print(" g");
  }

  // create a var where the pulse reading from sensor will go
  float readPulse;
  
  // wait a bit for LEDs to actually turn on, as directed by sensorDelay var
  delay(sensorDelay);

  // now take a measurement from the sensor, timing a low pulse on the sensor's "out" pin
  readPulse = pulseIn(myTaosOutPin, LOW, 80000);

  //if the pulseIn times out, it returns 0 and that throws off numbers. just cap it at 80k if it happens
  if(readPulse < .1){
    readPulse = 80000;
  }

  //turn off color sensor and LEDs to save power 
  setTaosMode(0);

  // return the pulse value back to whatever called for it... but convert to Hz first
  return 100000.0f/((float)readPulse);

}


// Operation modes area, controlled by hi/lo settings on S0 and S1 pins.
//setting mode to zero will put taos into low power mode. taosMode(0);
void TCS3200Device::setTaosMode(uint8_t mode)
{

  if(mode == 0){
    //power OFF mode-  LED off and both channels "low"
    digitalWrite(myS0Pin, LOW); //S0
    digitalWrite(myS1Pin, LOW); //S1
   
  }else if(mode == 1){
    //this will put in 1:1, highest sensitivity
    digitalWrite(myS0Pin, HIGH); //S0
    digitalWrite(myS1Pin, HIGH); //S1
    
  }else if(mode == 2){
    //this will put in 1:5
    digitalWrite(myS0Pin, HIGH); //S0
    digitalWrite(myS1Pin, LOW); //S1
    
  }else if(mode == 3){
    //this will put in 1:50
    digitalWrite(myS0Pin, LOW); //S0
    digitalWrite(myS1Pin, HIGH); //S1 
    
  }

  return;

}

Device::ValueStruct TCS3200Device::readValue(int index)
{
    Device::ValueStruct output;
    
    if(index == 0)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readColorHertz(WHITE);
        output.name = "WHITE_HZ";
    }
    else if(index == 1)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readColorHertz(RED);
        output.name = "RED_HZ";
    }
    else if(index == 2)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readColorHertz(BLUE);
        output.name = "BLUE_HZ";
    }
    else if(index == 3)
    {
        output.type = Device::TypeFloat;
        output.value.decimal = readColorHertz(GREEN);
        output.name = "GREEN_HZ";
    }
    else
    {
        output.type = Device::TypeInvaild;
        output.name = "";
    } 
    return output;
}

uint32_t TCS3200Device::numValues()
{
    return 4; 
}



