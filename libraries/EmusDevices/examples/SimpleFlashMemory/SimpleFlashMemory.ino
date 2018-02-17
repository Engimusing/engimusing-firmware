/*
  Copyright (c) 2017 Engimusing LLC.  All right reserved.

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

/* Example for how to read/write to the AT45BD161E flash memory DF11 board using the EFM32ZGUSB Engimusing board
    There are 2 devices on this board. An LED and an AT45BD161E flash memory.
*/

#if !defined(EFM32ZGUSB)
#error Incorrect Board Selected! Please select Engimusing EFM32ZGUSB from the Tools->Board: menu.
#endif

#include "AT45DB161EMemory.h"
#include "SPI.h"

AT45DB161EMemory FlashMemory;
const int stringSize = 258;
uint8_t exampleText[stringSize] = "This is an example of how to write data to flash memory and read it back. Try it once with the writeExample = true; line left in and then comment it out using // and run the code again. See how the text is still read back correctly even after a power cycle.";

void setup() {
  FlashMemory.begin(SPI, 4,3,2);

  bool writeExample = false;
  //lets write the example text to the flash memory.
  writeExample = true; //comment this out after the first time running the example
  if(writeExample)
  {
    //writeData only writes to a temporary buffer unless it really needs to save 
    // the data due to running out of buffer space
    FlashMemory.writeData(0, stringSize, exampleText);

    //saveData forces the temporary buffers to be written to the flash.
    // this should be used sparingly since AT45BD161E only has 10000 erase cycles
    FlashMemory.saveData();
  }
}

void loop() {

  uint8_t readExampleText[stringSize];
  //Read the data from the flash
  FlashMemory.readData(0, stringSize, readExampleText);
  //print the string read from the flash
  Serial.println((const char*)readExampleText);

  delay(1000);
}


