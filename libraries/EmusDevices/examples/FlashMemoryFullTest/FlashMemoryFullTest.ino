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
int printDelay = 10000;
int lastPrint = 0;

void setup() {
  //Setup the DF11 connection to the AT45DB161E flash memory from the ZGUSB board
  FlashMemory.begin(SPI, 4,3,2);
}

union uint32ToByteArray
{
  uint32_t intValue;
  uint8_t charArray[4];
};


int checkForTaskToRun()
{
  int taskToRun = 0;
  if(printDelay + lastPrint <= millis())
  {
    lastPrint = millis();
    Serial.println("Select a task to run:");
    Serial.println("1 - write random values");
    Serial.println("2 - verify random values");    
    Serial.println("3 - write and verify random values");    
  }

  while(Serial.available())
  {
    char readVal = Serial.read();
    if(readVal >= '1' && readVal <= '3')
    {
       taskToRun = readVal - '0';
    }
  }

  return taskToRun;
}

const int seed = 0;

void runWriteRandTask()
{
  Serial.println("Running Write Rand Task!");
  //initialize the random number generation, the seed here
  // must match the srand seed in runVerifyRandTask in order for this to work.
  srand(seed);
  rand();
  //use this union to convert from uint32 to a byte array
  uint32ToByteArray converter;
  
  //loop over all the pages in the flash
  for(int page = 0; page < FlashMemory.numPages(); page++)
  {
    Serial.print("Writing random data for Page:");
    Serial.println(page);
    
    //loop over all the bytes in the page
    int pageSize = FlashMemory.pageSize();
    for(int i = 0; i < pageSize; i+=4)
    {
      uint32_t address = i + (page*pageSize);
      //get a random value to write.
      converter.intValue = rand();
      FlashMemory.writeData(address, 4, converter.charArray); 
    }
  }  
  FlashMemory.saveData();
  Serial.println("Write Rand Task Done!");
}

void runVerifyRandTask()
{
  Serial.println("Running Verify Rand Task!");

  srand(seed);
  rand();
  uint32ToByteArray converter;
  int pageFailCount = 0;
  int pageSize = FlashMemory.pageSize();
  for(int page = 0; page < FlashMemory.numPages(); page++)
  {
    Serial.print("Verifying Page:");
    Serial.println(page);
    for(int i = 0; i < pageSize; i+=4)
    {
      uint32_t address = i + (page*pageSize);
      FlashMemory.readData(address, 4, converter.charArray); 
      
      //get the expected random value and compare it to the value read from the flash
      int randomValue = rand();
      if(converter.intValue != randomValue)
      {
        Serial.print("Compare for failed at:");
        Serial.print(address);
        Serial.print(" Received:");
        Serial.print(converter.intValue);
        Serial.print(" Expected:");
        Serial.println(randomValue);
        
        //log the failure
        pageFailCount++;
        break; //don't waste time reading the rest of the page if it fails.
      }
    }
  }
  
  if(pageFailCount == 0)
  {
    Serial.println("Verify Rand Task Succeeded!");
  }
  else
  {
    Serial.print("Verify Task Failed! Page Fail Count:");
    Serial.println(pageFailCount);
  }
}

void loop() {

  int taskToRun = checkForTaskToRun();
  if(taskToRun > 0)
  {
    if(taskToRun == 1)//WriteTest
    {
      runWriteRandTask();
    }
    else if(taskToRun == 2)//verifyTest
    {
      runVerifyRandTask();      
    }
    else if(taskToRun == 3)//write and verifyTest
    {
      runWriteRandTask();
      runVerifyRandTask();      
    }
  }
}


