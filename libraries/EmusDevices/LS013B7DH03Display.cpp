/*
  Copyright (c) 2018 Engimusing LLC.  All right reserved.

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

#include <LS013B7DH03Display.h>

#if SPI_INTERFACES_COUNT > 0

#include <spi.h>


LS013B7DH03Display::LS013B7DH03Display()
{
}


void LS013B7DH03Display::begin(SPIClass &spi, uint8_t extCommPin, uint8_t extModePin, uint8_t displayOnPin, uint8_t displayScsPin) 
{
  mySpi = &spi;
  
  myExtCommPin = extCommPin;
  pinMode(myExtCommPin, OUTPUT);
  digitalWrite(myExtCommPin, LOW);
  
  myExtModePin = extModePin;
  pinMode(myExtModePin, OUTPUT);
  digitalWrite(myExtModePin, HIGH);
  
  myDisplayOnPin = displayOnPin;
  pinMode(myDisplayOnPin, OUTPUT);
  digitalWrite(myDisplayOnPin, LOW);
  
  myDisplayScsPin = displayScsPin;
  pinMode(myDisplayScsPin, OUTPUT);
  digitalWrite(myDisplayScsPin, LOW);
  
  delay(100);
  digitalWrite(myDisplayOnPin, HIGH);
  
  for(int i = 0; i < WIDTH*HEIGHT; i++)
  {
    myDigitsToDisplay[i] = 10; //10 displays an empty section instead of any digit.
  }

  //The LCD screen is LSB not MSB!!!! This is important, the EM won't be able to comunicate with the LCD screen unless this is false.
  mySpi->setBitOrder(false);
  mySpi->begin();
  
  myPreviousModeHigh = millis();
  
  //Currenly only one display mode but we can add more later
  myDisplayMode = DISPLAY_4X4_DIGITS;
  
}

// the loop function runs over and over again forever
void LS013B7DH03Display::update() 
{
  unsigned long currentMillis = millis();

  if(currentMillis - myPreviousModeHigh >= 999)
  {
    myPreviousModeHigh = currentMillis;
    digitalWrite(myExtModePin, HIGH);   // turn the LED on (HIGH is the voltage level)
  }else
  {
    digitalWrite(myExtModePin, LOW);    // turn the LED off by making the voltage LOW
  }
 
  digitalWrite(myDisplayScsPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  if(myDisplayMode == DISPLAY_4X4_DIGITS)
  {
    draw4x4Digits();
  }
  
}
  
void LS013B7DH03Display::draw4x4Digits()
{
  
  //delay(1);
  unsigned short majorCol, minorRow, minorCol, majorRow;
  mySpi->transfer(0x01); //Update command 0x04 for clear

  int currentDigit = 0;
  //Major rows and columns are the 4x4 grid of digits
  //Minor rows and columns are the rows and columns that make us a single digit
  for(majorRow = 0; majorRow < HEIGHT; majorRow++)
  {
    //Digits are 32 pixels talll
    for (minorRow = 0; minorRow < 32; minorRow ++) 
    {
      //Send down the row number
      mySpi->transfer(majorRow*32 + minorRow + 1);
      
      for (majorCol = 0; majorCol < WIDTH; majorCol++) 
      {
        int digitToDisplay = myDigitsToDisplay[majorRow * WIDTH + majorCol];
        
        //Digits only go from 0 to 9, set anything else to 10 for a blank space
        if(digitToDisplay < 0 || digitToDisplay > 9)
        {
          digitToDisplay = 10;
        }
        digitToDisplay *= 8; //convert into an array index for the top of the digit
        
        //digits are 32 pixels wide, each byte sent down the the display is
        // 8 pixels wide of data;
        for(minorCol = 0; minorCol < 4; minorCol++)
        { 
          
          int currentDigitIdx = digitToDisplay + (minorRow / 4);
          if(currentDigitIdx < 88)
          {
            int currentDigitRowValue = numberTexture[currentDigitIdx];

            //since each bit in the number Texture is really a 4x4 display pixel there is a lookup
            // to convert from 2-bits of digit data to 8-bits of display data
            unsigned char value = twobitLookup[(currentDigitRowValue >> (6-(minorCol*2))) & 0x3];          
            mySpi->transfer(value);
          }
          else
          {
            //anything else should be cleared
            mySpi->transfer(0xff);  
          }
        }
      }
      //End  of frame
      mySpi->transfer(0xff);
    }
    
  }
  mySpi->transfer(0xff);
  digitalWrite(myDisplayScsPin, LOW);   // turn the LED on (HIGH is the voltage level)
}

//!@brief used to set a specific one of the 4x4 digits 
void LS013B7DH03Display::setDigitToDisplay(uint8_t digit, uint8_t column, uint8_t row)
{
  if(row > HEIGHT || column > WIDTH)
  {
    return;
  }
  myDigitsToDisplay[row * WIDTH + column] = digit;
}
    
//!@brief used to set a row to a number between 0 and 9999
void LS013B7DH03Display::setValueToDisplay(int value, uint8_t row)
{
  setDigitToDisplay(value % 10, 3, row);
  if(value > 10)
  {
    setDigitToDisplay(value / 10 % 10, 2, row);
  }
  else
  {
    setDigitToDisplay(10, 2, row);
  }
  if(value > 100)
  {
    setDigitToDisplay(value / 100 % 10, 1, row);
  }
  else
  {
    setDigitToDisplay(10, 1, row);
  }
  if(value > 1000)
  {
    setDigitToDisplay(value / 1000 % 10, 0, row);
  }
  else
  {
    setDigitToDisplay(10, 0, row);
  }
  
}
  

#endif 