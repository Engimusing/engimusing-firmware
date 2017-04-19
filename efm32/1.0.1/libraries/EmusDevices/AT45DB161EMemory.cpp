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

#include "AT45DB161EMemory.h"
#include "SPI.h"


AT45DB161EMemory::AT45DB161EMemory()
{
};
        
void AT45DB161EMemory::begin(SPIClass &spi, uint8_t chipSelectPin, uint8_t writeProtectPin, uint8_t resetPin)
{
    //setup the pins   
    myChipSelectPin = chipSelectPin;
    pinMode(myChipSelectPin, OUTPUT);
    deselectDevice();
    
    myWriteProtectPin = writeProtectPin;
    pinMode(myWriteProtectPin, OUTPUT);
    digitalWrite(myWriteProtectPin, HIGH);
    
    myResetPin =  resetPin;
    pinMode(myResetPin, OUTPUT);
    digitalWrite(myResetPin, HIGH);
    

    //Setup the SPI commuication with the memory device
    mySpi = &spi;
    //setup clock mode for SPI to match device
    mySpi->setDataMode(usartClockMode3);
    mySpi->begin();
    
    //Let the device wakeup
    delay(10);
    
    //get the number of bits in the page address 
    uint8_t curStatus = status();
    uint8_t density = (curStatus >> 3) & 0x7;
    
    myPageBits = pageBitMapping[density];
    //calculate the power of 2 page size we can use
    myPageSize = (0x1 << (myPageBits - 1));
    
    
    //initialize the buffer state variables
    myBufferDirty[0] = false;
    myBufferDirty[1] = false;
    myBufferPage[0] = -1;
    myBufferPage[1] = -1;
    myLastUsedBuffer = 1;
}
        
uint8_t  AT45DB161EMemory::status()
{
    selectDevice();
    
    mySpi->transfer(StatusReg); // read opcode for status register
    uint8_t ret = mySpi->transfer(DummyOp);
    
    deselectDevice();
    return ret;
}
        
//write both buffers currently in use to flash
void AT45DB161EMemory::saveData()
{
    //save buffer checks to see if a buffer is dirty and saves it if it is dirty
    saveBuffer(1);
    saveBuffer(2);  
}

void AT45DB161EMemory::saveBuffer(uint8_t buffer)
{
    if(buffer > 2 || buffer < 1)
        return;
    
    uint8_t bufferOpCode = Buf1ToFlashWE;
    if(buffer == 2)
    {
        bufferOpCode = Buf2ToFlashWE;
    }
    
    //let only save the buffer if it is dirty
    if(myBufferDirty[buffer - 1] && myBufferPage[buffer - 1] >= 0)
    {
        selectDevice();
        mySpi->transfer(bufferOpCode);
        mySpi->transfer((uint8_t) myBufferPage[buffer - 1] >> (16 - myPageBits));
        mySpi->transfer((uint8_t) myBufferPage[buffer - 1] << (myPageBits - 8));
        mySpi->transfer(DummyOp);
        deselectDevice();    
        
        selectDevice();
        while(!(status() & 0x80));
        deselectDevice();    
        
        myBufferDirty[buffer -1] = false;
    }
}


//write data to a buffer (will write buffers to flash only if necessary due to needing a new buffer to use)
void AT45DB161EMemory::writeData(uint32_t address, uint16_t len, uint8_t *data)
{
    processData(true, address, len, data);
}
        
//read data to a buffer (will write buffers to flash if it needs access to a page that is not in a current buffer
void AT45DB161EMemory::readData(uint32_t address, uint16_t len, uint8_t *data)
{
    processData(false, address, len, data);
}

void AT45DB161EMemory::processData(bool write, uint32_t address, uint16_t len, uint8_t *data)
{
    while(len > 0)
    {
        uint16_t pageAddress = (uint16_t)(address >> (myPageBits - 1)); 
        uint16_t bufferAddress = (uint16_t) address & ~(0xFFFF << (myPageBits - 1));
        
        uint8_t bufferToUse = 0;
        if(pageAddress == myBufferPage[0])
        {
            Serial.println("Buffer1");
            bufferToUse = 1;
        }
        else if(pageAddress == myBufferPage[1])
        {
            Serial.println("Buffer2");
            bufferToUse = 2;
        }else
        {
            if(myLastUsedBuffer == 1)
            {
                bufferToUse = 2;
                Serial.println("UseBuffer2");
            }
            else
            {
                bufferToUse = 1;
                Serial.println("UseBuffer1");
            }
            
            saveBuffer(bufferToUse);   
            putPageInBuffer(pageAddress, bufferToUse);
               
        }
        
        uint16_t lenToProcess = len;
        
        if(lenToProcess > (myPageSize - bufferAddress))
        {
            lenToProcess = myPageSize - bufferAddress;
        }
        
        if(write)
        {
            writeToBuffer(bufferToUse, bufferAddress, lenToProcess, data);

            //since we wrote to the buffer let's assume it is dirty (even though there is a slight chance it didn't change)
            myBufferDirty[bufferToUse-1] = true;
        }
        else
        {
            readFromBuffer(bufferToUse, bufferAddress, lenToProcess, data);
        }        
        
        //get ready for the next chuck of data if the data to process span's page boundries
        data += lenToProcess;
        address += lenToProcess;
        len -= lenToProcess;
            
        myLastUsedBuffer = bufferToUse;
        
    }
}

void AT45DB161EMemory::putPageInBuffer(uint16_t pageAddress, uint8_t buffer)
{   
    selectDevice();
        
    uint8_t opcode = FlashToBuf1Transfer;
    
    if(buffer == 2)
    {
        opcode = FlashToBuf2Transfer;
    }
    
    mySpi->transfer(opcode);
    mySpi->transfer((uint8_t)pageAddress >> (16 - myPageBits));
    mySpi->transfer((uint8_t)pageAddress << (myPageBits - 8));
    mySpi->transfer(DummyOp);
    
    deselectDevice();    
    
    selectDevice();
    while(!(status() & 0x80));
    deselectDevice();  
    
    myBufferPage[buffer - 1] = pageAddress;
}

void AT45DB161EMemory::writeToBuffer(uint8_t buffer, uint16_t address, uint16_t len, uint8_t *data)
{
    if(len + address > myPageSize)
    {
        return;
    }
    
    selectDevice();
    
    uint8_t opcode = Buf1Write;
    
    if(buffer == 2)
    {
        opcode = Buf2Write;
    }
    
    mySpi->transfer(opcode);
    mySpi->transfer(DummyOp);
    mySpi->transfer((uint8_t) (address >> 8));
    mySpi->transfer((uint8_t) address);
    
    for(int i = 0; i < len; i++)
    {
        mySpi->transfer(data[i]);
    }
    
    deselectDevice();
      
}

void AT45DB161EMemory::readFromBuffer(uint8_t buffer, uint16_t address, uint16_t len, uint8_t *data)
{
    if(len + address > myPageSize)
    {
        return;
    }
    
    selectDevice();
    
    uint8_t opcode = Buf1Read;
    
    if(buffer == 2)
    {
        opcode = Buf2Read;
    }
        
    mySpi->transfer(opcode);
    mySpi->transfer(DummyOp);
    mySpi->transfer((uint8_t) (address >> 8));
    mySpi->transfer((uint8_t) address);
    mySpi->transfer(DummyOp);
    for(int i = 0; i < len; i++)
    {
        data[i] = mySpi->transfer(DummyOp);
    }
    
    deselectDevice();
      
}    

void AT45DB161EMemory::selectDevice()
{
    digitalWrite(myChipSelectPin, LOW);
}

void AT45DB161EMemory::deselectDevice()
{
    digitalWrite(myChipSelectPin, HIGH);
}  