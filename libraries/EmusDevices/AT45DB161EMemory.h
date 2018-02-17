///
///@file AT45DB161EMemory.h
///@brief Contains AT45DB161EMemory class which is used to access an AT45DB161E
///Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/AT45DB161E.pdf
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
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

const uint16_t NUM_PAGES = 4096; // this is specific to the AT45DB161E device

//we are using powers of 2 for now so we don't need this
//const uint16_t pageSizeMapping[] ={264,264, 264, 264, 264, 528, 528,1056};


class SPIClass;
///@brief Class for accessing an AT45DB161E chip. Supports both writing and reading to the flash.
/// Has simple buffering to avoid excess writes to the flash which avoids extra wear.
/// Datasheet link: http://engimusing.github.io/Product_Documentation/data_sheets/AT45DB161E.pdf
class AT45DB161EMemory 
{
    public:
        ///@brief Constructor that does nothing
        ///@return AT45DB161EMemory object which needs begin() called before being used
        AT45DB161EMemory();
        
        ///@brief Setup function for specifying the pins connected to the AT45DB161E
        ///@param [in] spi SPI object to use when communicating with the AT45DB161E
        ///@param [in] chipSelectPin Chip Select pin connected to the CS pin on the AT45DB161E
        ///@param [in] writeProtectPin Write Protect pin connected to the WP pin on the AT45DB161E
        ///@param [in] resetPin Reset pin connected to the RESET pin on the AT45DB161E
        void begin(SPIClass &spi, uint8_t chipSelectPin, uint8_t writeProtectPin, uint8_t resetPin);
        
        ///@brief Get the current status of the AT45DB161E from the chip
        ///@return First byte of the status register for the AT45DB161E
        ///@details See table 9-1 in the <a href="http://engimusing.github.io/Product_Documentation/data_sheets/AT45DB161E.pdf#page=27">datasheet</a> for a detailed description of the bits.  
        uint8_t  status();
        
        ///@brief write both temporary buffers currently in use to flash
        void saveData(); 
        
        ///@brief write data to a buffer (will write buffers to flash only if necessary due to needing a new buffer to use)
        ///@param [in] address Byte address to write the data to
        ///@param [in] len Length of the data contained in the array that the data parameter is pointing to.
        ///@param [in] data Data to write to the flash memory
        void writeData(uint32_t address, uint16_t len, uint8_t *data); 
                
        ///@brief read data to a buffer (will write buffers to flash if it needs access to a page that is not in a current buffer
        ///@param [in] address Byte address to read the data from
        ///@param [in] len Length of the data to read from the flash memory.
        ///@param [in] data Buffer to write with the data read from the flash memory
        void readData(uint32_t address, uint16_t len, uint8_t *data);
               
        ///@brief Get the number of pages this particular device supports.
        ///@return Number of pages (currently only supports the AT45DB161E which is always 4096 pages)
        uint16_t numPages();
        
        ///@brief Size in bytes of a page of memory on the device
        ///@return Number of bytes contained in a single page of memory
        uint16_t pageSize();
    protected:
    
        ///@brief Helper function to save a single temporary write buffer to the flash.
        ///@param [in] buffer Either 1 or 2 to specify the buffer to write to the flash.
        void saveBuffer(uint8_t buffer);
        
        ///@brief Select the device using the CS for the SPI
        void selectDevice();
        
        ///@brief Stop selecting the device using the CS for the SPI
        void deselectDevice();

        ///@brief Read a page from the permanent flash into the temporary buffer on the device
        ///@param [in] pageAddress Address of the page to read.
        ///@param [in] buffer Buffer number to read the data into. Either 1 or 2
        void putPageInBuffer(uint16_t pageAddress, uint8_t buffer);
        
        ///@brief Read data from the temporary buffer
        ///@param [in] buffer Buffer number to read from. Etither 1 or 2
        ///@param [in] address Address of data to read from the Buffer. Address is local to a page.
        ///@param [in] len Number of bytes to read from the temprorary buffer
        ///@param [in] data Array to put the read data into. Needs to point to an array larger than len bytes.
        void readFromBuffer(uint8_t buffer, uint16_t address, uint16_t len, uint8_t *data);
        
        ///@brief Write data into a temporary buffer on the device
        ///@param [in] buffer Buffer number to write into. Either 1 or 2
        ///@param [in] address Address of where in the buffer to start writing the data. Address is local to a page.
        ///@param [in] len Number of bytes to write into the temporary buffer.  
        ///@param [in] data Array of data to write into the temporary buffer. Needs to point to an array larger than len bytes. 
        void writeToBuffer(uint8_t buffer, uint16_t address, uint16_t len, uint8_t *data);
        
        ///@brief Helper function which can both write or read into the flash.
        ///@param [in] write True for writting and false for reading.
        ///@param [in] address Address of where to start reading/writing.
        ///@param [in] len Number of bytes to read or write.
        ///@param [in] data Array for either getting back data from the flash or full of data to write to the flash. Needs to point to an array larger than len bytes.
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

#endif