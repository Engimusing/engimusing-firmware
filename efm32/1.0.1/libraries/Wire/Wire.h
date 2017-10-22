///
///@file Wire.h
///@brief TWI/I2C library for Engimusing Devices
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///Copyright (c) 2011 Cristian Maglie <c.maglie@bug.st>.
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

#ifndef TwoWire_h
#define TwoWire_h

// Include Atmel CMSIS driver
#include <em_i2c.h>

#include "Stream.h"
#include "variant.h"

#define BUFFER_LENGTH 32

class I2CClass;

class TwoWire : public Stream {
 public:
    ///@brief Constructor that links an I2CClass to the TwoWire wrapper class.
    ///@param [in] _i2c I2C object to link to this TwoWire object
    ///@return TowWire object that is linked to an I2CClass
    TwoWire(I2CClass &_i2c);
    
    ///@brief Start the I2C connection in master mode. TwoWire currently only supports master mode.
    void begin();
    
    ///@brief Currently unsupported function for starting TwoWire in slave mode
    ///@param [in] uint8_t Slave address
    void begin(uint8_t);
    ///@brief Currently unsupported function for starting TwoWire in slave mode
    ///@param [in] int Slave address
    void begin(int);
    
    ///@brief Start a transmission between this TwoWire and one of the slaves
    ///@param [in] uint8_t Address of the slave to transmit to
    void beginTransmission(uint8_t);
    ///@brief Start a transmission between this TwoWire and one of the slaves
    ///@param [in] int Address of the slave to transmit to
    void beginTransmission(int);
    
      ///@brief End a currently running transmission
      ///@return Result of the transfer call to the I2CClass
      uint8_t endTransmission(void);
    
    
      ///@brief End a currently running transmission
      ///@param [in] sendStop Should this transmission be ended with a stop bit
      ///@return Result of the transfer call to the I2CClass
      ///@details
      ///	Originally, 'endTransmission' was an f(void) function.
      ///	It has been modified to take one parameter indicating
      ///	whether or not a STOP should be performed on the bus.
      ///	Calling endTransmission(false) allows a sketch to
      ///	perform a repeated start.
      ///
      ///	WARNING: Nothing in the library keeps track of whether
      ///	the bus tenure has been properly ended with a STOP. It
      ///	is very possible to leave the bus in a hung state if
      ///	no call to endTransmission(true) is made. Some I2C
      ///	devices will behave oddly if they do not see a STOP.
      ///
    uint8_t endTransmission(uint8_t);
    
    ///@brief Send a read request to a slave
    ///@param [in] address slave address to request a read from
    ///@param [in] quantity number of bytes to request from the slave
    ///@return Number of bytes requested
    uint8_t requestFrom(uint8_t, uint8_t);
    ///@brief Send a read request to a slave
    ///@param [in] address slave address to request a read from
    ///@param [in] quantity number of bytes to request from the slave
    ///@param [in] sendStop should a stop bit be sent after the request
    ///@return Number of bytes requested
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    ///@brief Send a read request to a slave
    ///@param [in] address slave address to request a read from
    ///@param [in] quantity number of bytes to request from the slave
    ///@return Number of bytes requested
    uint8_t requestFrom(int, int);
    ///@brief Send a read request to a slave
    ///@param [in] address slave address to request a read from
    ///@param [in] quantity number of bytes to request from the slave
    ///@param [in] sendStop should a stop bit be sent after the request
    ///@return Number of bytes requested
    uint8_t requestFrom(int, int, int);
    
    ///@brief Write a single byte to the transmit buffer so it can be sent to the slave later
    ///@param [in] data byte to send to the slave
    ///@return Number of bytes added to the transfer buffer
    virtual size_t write(uint8_t);
    ///@brief Write a single byte to the transmit buffer so it can be sent to the slave later
    ///@param [in] data byte to send to the slave
    ///@param [in] quantity number of bytes to send to the slave
    ///@return Number of bytes added to the transfer buffer
    virtual size_t write(const uint8_t *, size_t);
    
    ///@brief Check to see how many bytes are avilable in the read buffer
    ///@return Number of available bytes
    virtual int available(void);
    
    ///@brief Read and remove from the buffer the next available byte.
    ///@return Byte read off of the read buffer or -1 if it was not read.
    virtual int read(void);
    
    ///@brief Read but don't remove from the buffer the next available byte.
    ///@return Next available byte in the read buffer. 
    ///@details More details
    virtual int peek(void);
    
    ///@brief Currently not implemented 
    virtual void flush(void);
    
    ///@brief Currently unused but in the future may be used for handling data in a callback
    void onReceive(void(*)(int));
    ///@brief Currently unused but in the future may be used for handling data in a callback
    void onRequest(void(*)(void));

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;

    void onService(void);

 private:
    // RX Buffer
    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t rxBufferIndex;
    uint8_t rxBufferLength;

    // TX Buffer
    uint8_t txAddress;
    uint8_t txBuffer[BUFFER_LENGTH];
    uint8_t txBufferLength;

    // Service buffer unsed for now for Energy Micro
    uint8_t srvBuffer[BUFFER_LENGTH];
    uint8_t srvBufferIndex;
    uint8_t srvBufferLength;

    // Callback user functions
    void (*onRequestCallback)(void);
    void (*onReceiveCallback)(int);

    // TWI state
    enum TwoWireStatus {
	UNINITIALIZED,
	MASTER_IDLE,
	MASTER_SEND,
	MASTER_RECV,
	SLAVE_IDLE,
	SLAVE_RECV,
	SLAVE_SEND
    };
    TwoWireStatus status;
	
    I2CClass &myI2c;
};

#if WIRE_INTERFACES_COUNT > 0
#define Wire Wire0
extern TwoWire Wire0;
#endif
#if WIRE_INTERFACES_COUNT > 1
extern TwoWire Wire1;
#endif
#if WIRE_INTERFACES_COUNT > 2
extern TwoWire Wire2;
#endif
#if WIRE_INTERFACES_COUNT > 3
extern TwoWire Wire3;
#endif
#endif

