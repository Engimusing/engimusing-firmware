///
///@file I2CClass.h
///@brief contains I2CClass definition along with global I2CClasses I2C_0 through I2C_1
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

#include <em_i2c.h>

// Includes Atmel CMSIS
#include <em_device.h>
#include <em_cmu.h>

///@brief Class for accessing the I2C peripheral. Should only be instantiated by this file. I2C_0 through I2C_1 should be used to access the I2C peripheral.
/// This class is wrapped by the TwoWire class and the Wire0 through Wire4 should be used instead of this class directly
class I2CClass 
{
 public:
 
    ///@brief Sets up the I2C peripheral configuration. Used in the I2CClass.cpp file to setup I2C's for all boards.
    ///@param [in] _i2c Wire definition to use
    ///@param [in] loc Location # to use
    ///@param [in] _i2cClock clock to use
    ///@param [in] pinSda SDA pin
    ///@param [in] pinScl SCL pin
    ///@return instance of the I2CClass
    I2CClass(I2C_TypeDef &_i2c, uint8_t loc, CMU_Clock_TypeDef _i2cClock, uint32_t pinSda, uint32_t pinScl);

    void begin();
	
    uint8_t transfer(uint8_t address, uint8_t txLength, uint8_t *txBuffer, uint8_t rxLength, uint8_t *rxBuffer);
    
    void onService(void);
        	
 protected:
    
    // TWI instance
    I2C_TypeDef &myI2c;

	CMU_Clock_TypeDef myI2cClock;


    I2C_TransferSeq_TypeDef myCurTransmission;
    
    uint32_t myPinSda;
    uint32_t myPinScl;
    uint8_t myLocation;
    
	//const char *_id;
 public:
   
};

#if WIRE_INTERFACES_COUNT > 0
extern I2CClass I2C_0;
#endif
#if WIRE_INTERFACES_COUNT > 1
extern I2CClass I2C_1;
#endif
#if WIRE_INTERFACES_COUNT > 2
extern I2CClass I2C_2;
#endif
#if WIRE_INTERFACES_COUNT > 3
extern I2CClass I2C_3;
#endif


