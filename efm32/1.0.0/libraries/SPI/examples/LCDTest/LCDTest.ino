/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#include "SPI.h"

int extComm = 53;
int extMode = 57;
int displayOn = 54;
int dispScs = 62;

#define spi SPI1

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(48, OUTPUT);

  pinMode(extComm, OUTPUT);
  pinMode(extMode, OUTPUT);
  pinMode(displayOn, OUTPUT);
  pinMode(dispScs, OUTPUT);
  digitalWrite(extMode, HIGH);
  digitalWrite(displayOn, LOW);
  digitalWrite(extComm, LOW);
  digitalWrite(dispScs, LOW);

  delay(100);
  digitalWrite(displayOn, HIGH);
  
  //The LCD screen is LSB not MSB!!!! This is important, the EM won't be able to comunicate with the LCD screen unless this is false.
  spi.setBitOrder(false);
  spi.begin();
  
}
int count = 0;
int count2 = 0;
unsigned long previousMillis = 0;        // will store last time LED was updated

int xLoc = 64;
int yLoc = 64;


// the loop function runs over and over again forever
void loop() {
  count2++;
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= 999)
  {
    previousMillis = currentMillis;
    digitalWrite(extMode, HIGH);   // turn the LED on (HIGH is the voltage level)
    count++;
  }else
  {
    digitalWrite(extMode, LOW);    // turn the LED off by making the voltage LOW
  }
 
  digitalWrite(dispScs, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1);
  unsigned short col,row;
  spi.transfer(0x01); //Update command 0x04 for clear

  
  
  for (row = 1; row <= 128; row ++) 
  {
    spi.transfer(row);
    for (col = 0; col < 16; col++) 
    {
      if(row == yLoc && xLoc/8 == col)
      {
        int bit = (xLoc - ((xLoc/8)*8));
        spi.transfer(0x01 << bit);
      }
      else
        spi.transfer(0xff);
    }
    spi.transfer(0xff);
  }
  spi.transfer(0xff);
  digitalWrite(dispScs, LOW);   // turn the LED on (HIGH is the voltage level)
  //Serial.println("FRAME!");
  if(count2 == 5)
  {
    digitalWrite(48, HIGH);
  }
  else if(count2 == 10)
  {
    
    digitalWrite(48, LOW);
    count2 = 0;
  }
  
  xLoc++;
  if(xLoc == 128)
  {
    yLoc++;
    xLoc = 0;
  }

  if(yLoc == 129)
  {
    yLoc = 1;
  }
  
  
}