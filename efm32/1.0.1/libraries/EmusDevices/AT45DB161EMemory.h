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

#pragma once

#include "Arduino.h"

//opcodes for AT45DB161E
#define FlashPageRead			       0x52	// Main memory page read
#define FlashToBuf1Transfer 		   0x53	// Main memory page to buffer 1 transfer
#define Buf1Read			               0x54	// Buffer 1 read
#define FlashToBuf2Transfer 		   0x55	// Main memory page to buffer 2 transfer
#define Buf2Read			               0x56	// Buffer 2 read
#define StatusReg			               0x57	// Status register
#define AutoPageReWrBuf1		       0x58	// Auto page rewrite through buffer 1
#define AutoPageReWrBuf2             0x59	// Auto page rewrite through buffer 2
#define FlashToBuf1Compare           0x60	// Main memory page to buffer 1 compare
#define FlashToBuf2Compare	       0x61	// Main memory page to buffer 2 compare
#define ContArrayRead                   0x68	// Continuous Array Read (Note : Only A/B-parts supported)
#define PageErase                          0x81  // Page erase
#define FlashProgBuf1			           0x82	// Main memory page program through buffer 1
#define Buf1ToFlashWE   		           0x83	// Buffer 1 to main memory page program with built-in erase
#define Buf1Write			               0x84	// Buffer 1 write
#define FlashProgBuf2			           0x85	// Main memory page program through buffer 2
#define Buf2ToFlashWE   		           0x86	// Buffer 2 to main memory page program with built-in erase
#define Buf2Write			               0x87	// Buffer 2 write
#define Buf1ToFlash     		           0x88	// Buffer 1 to main memory page program without built-in erase
#define Buf2ToFlash		               0x89    // Buffer 2 to main memory page program without built-in erase
#define DummyOp                       0x00 //dummy op used for reading and other purposes
const uint8_t pageBitMapping[] ={9,  9,  9,  9,  9,  10,  10,  11};

//we are using powers of 2 for now so we don't need this
//const uint16_t pageSizeMapping[] ={264,264, 264, 264, 264, 528, 528,1056};


class SPIClass;

class AT45DB161EMemory 
{
    public:
        AT45DB161EMemory();
        void begin(SPIClass &spi, uint8_t chipSelectPin, uint8_t writeProtectPin, uint8_t resetPin);
        
        uint8_t  status();
        
        //write both buffers currently in use to flash
        void saveData(); 
        
        //write data to a buffer (will write buffers to flash only if necessary due to needing a new buffer to use)
        void writeData(uint32_t address, uint16_t len, uint8_t *data); 
                
        //read data to a buffer (will write buffers to flash if it needs access to a page that is not in a current buffer
        void readData(uint32_t address, uint16_t len, uint8_t *data);
                       
    protected:
    
        void saveBuffer(uint8_t buffer);
        
        void selectDevice();
        void deselectDevice();

        void putPageInBuffer(uint16_t pageAddress, uint8_t buffer);
        
        void readFromBuffer(uint8_t buffer, uint16_t address, uint16_t len, uint8_t *data);
        
        void writeToBuffer(uint8_t buffer, uint16_t address, uint16_t len, uint8_t *data);
        
        void processData(bool write, uint32_t address, uint16_t len, uint8_t *data);
        
        SPIClass *mySpi;
        uint8_t myChipSelectPin;
        uint8_t myWriteProtectPin;
        uint8_t myResetPin;         

        uint8_t myLastUsedBuffer;
        int16_t myBufferPage[2];
        
        bool myBufferDirty[2];
        
        uint16_t myPageBits;
        uint16_t myPageSize;
        
        
};