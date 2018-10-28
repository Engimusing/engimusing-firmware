///
///@file LS013B7DH03Display.h
///@brief Contains LS013B7DH03Display class which is used to draw on an LS013B7DH03 LCD display
///
///@section License
///Copyright (c) 2018 Engimusing LLC.  All right reserved.
///
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
///

#pragma once

#include "Arduino.h"

#if SPI_INTERFACES_COUNT > 0

class SPIClass;


//every number is 8 bytes
// array is 88 bytes long
static unsigned char numberTexture[] = {0x00, 0x38, 0x44, 0x4C, 0x54, 0x64, 0x44, 0x38, // 0 
                                                        0x00, 0x10, 0x30, 0x10, 0x10, 0x10, 0x10, 0x38, // 1
                                                        0x00, 0x38, 0x44, 0x08, 0x10, 0x20, 0x40, 0x7C, // 2
                                                        0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38, // 3
                                                        0x00, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x08, 0x08, // 4
                                                        0x00, 0x7c, 0x40, 0x40, 0x78, 0x04, 0x04, 0x78, // 5
                                                        0x00, 0x38, 0x44, 0x40, 0x78, 0x44, 0x44, 0x38, // 6
                                                        0x00, 0x7c, 0x44, 0x04, 0x08, 0x10, 0x10, 0x10, // 7
                                                        0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38, // 8
                                                        0x00, 0x38, 0x44, 0x44, 0x3c, 0x04, 0x04, 0x38, // 9
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // NULL

static unsigned char twobitLookup[] = { 0xFF, 0x0F, 0xF0, 0x00 };  





///@brief Class for rendering a 4x4 grid of digits to an LS013B7DH03 display. 
class LS013B7DH03Display 
{
  public:
    ///@brief Constructor that does nothing
    ///@return LS013B7DH03Display object which needs begin() called before being used
    LS013B7DH03Display();
  
    ///@brief Setup function for specifying the pins connected to the LS013B7DH03
    ///@param [in] spi SPI object to use when communicating with the LS013B7DH03
    ///@param [in] extCommPin Chip Select pin connected to the ext comm pin on the LS013B7DH03
    ///@param [in] extModePin Write Protect pin connected to the ext mode pin on the LS013B7DH03
    ///@param [in] displayOnPin Reset pin connected to the display on pin on the LS013B7DH03
    ///@param [in] displayScsPin Reset pin connected to the display SCS pin on the LS013B7DH03
    void begin(SPIClass &spi, uint8_t extCommPin, uint8_t extModePin, uint8_t displayOnPin, uint8_t displayScsPin);
    
    ///@brief Call periodically so that the display can update what is being drawn on it.
    /// Needs to be called after the digits to display have changed in order to display the changes.
    void update();
  
    //!@brief used to set a specific one of the 4x4 digits 
    void setDigitToDisplay(uint8_t digit, uint8_t column, uint8_t row);
    
    //!@brief used to set a row to a number between 0 and 9999
    void setValueToDisplay(int value, uint8_t row);
  
  protected:
    //!@brief draw the myDigitsToDisplay array of digits to the display
    void draw4x4Digits();
  
  protected:
    SPIClass *mySpi;
    uint8_t myExtCommPin;
    uint8_t myExtModePin;
    uint8_t myDisplayOnPin;
    uint8_t myDisplayScsPin;
    
    static const int WIDTH = 4;
    static const int HEIGHT = 4;
    
    uint8_t myDigitsToDisplay[WIDTH * HEIGHT];
    
    unsigned long myPreviousModeHigh;
    
    enum DisplayMode
    {
      DISPLAY_4X4_DIGITS = 0,
    };
    
    DisplayMode myDisplayMode;
    
};

#endif