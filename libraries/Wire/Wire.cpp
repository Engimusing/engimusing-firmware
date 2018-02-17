/*
 * TwoWire.h - TWI/I2C library for Engimusing Devices
 * Copyright (c) 2016 Engimusing LLC.  All right reserved.
 * Copyright (c) 2011 Cristian Maglie <c.maglie@bug.st>.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

extern "C" {
#include <string.h>
}

#include "Wire.h"

#include "efm_lib/I2CClass.h"

TwoWire::TwoWire(I2CClass &_i2c) :
  myI2c(_i2c), rxBufferIndex(0), rxBufferLength(0), txAddress(0),
  txBufferLength(0), srvBufferIndex(0), srvBufferLength(0), 
  status(UNINITIALIZED)
{
  // Empty

}


void TwoWire::begin(void) 
{
	
    status = MASTER_IDLE;
    myI2c.begin();
  
}

void TwoWire::begin(uint8_t address) {
  //this does not yet support slave i2c
  return;
  /*if (onBeginCallback)
    onBeginCallback();

    // Disable PDC channel
    twi->TWI_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;

    TWI_ConfigureSlave(twi, address);
    status = SLAVE_IDLE;
    TWI_EnableIt(twi, TWI_IER_SVACC);*/
  //| TWI_IER_RXRDY | TWI_IER_TXRDY	| TWI_IER_TXCOMP);
}

void TwoWire::begin(int address) {
  begin((uint8_t) address);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {
  if (quantity > BUFFER_LENGTH)
    quantity = BUFFER_LENGTH;

  // set rx buffer iterator vars
  rxBufferIndex = 0;
  rxBufferLength = quantity;

  if(status == MASTER_IDLE) //not in a transmission so send a read request now
    {
      txAddress = address;
      endTransmission(true);
    }
  return quantity;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
  return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity) {
  return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop) {
  return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) sendStop);
}

void TwoWire::beginTransmission(uint8_t address) {
  status = MASTER_SEND;

  // save address of target and empty buffer
  txAddress = address;
  txBufferLength = 0;
	
  rxBufferIndex = 0;
  rxBufferLength = 0;
	
}

void TwoWire::beginTransmission(int address) {
  beginTransmission((uint8_t) address);
}

//
//	Originally, 'endTransmission' was an f(void) function.
//	It has been modified to take one parameter indicating
//	whether or not a STOP should be performed on the bus.
//	Calling endTransmission(false) allows a sketch to
//	perform a repeated start.
//
//	WARNING: Nothing in the library keeps track of whether
//	the bus tenure has been properly ended with a STOP. It
//	is very possible to leave the bus in a hung state if
//	no call to endTransmission(true) is made. Some I2C
//	devices will behave oddly if they do not see a STOP.
//
uint8_t TwoWire::endTransmission(uint8_t sendStop) {
  //there will be a read command after this which will send the transmission
  if(sendStop == false || (txBufferLength <= 0 && rxBufferLength <= 0))
    {
      status = MASTER_IDLE;
      return 0;
    }
  
   status = MASTER_IDLE;
	
    
    uint8_t ret = myI2c.transfer(txAddress, txBufferLength, &txBuffer[0], rxBufferLength, &rxBuffer[0]);
    
    //reset the tx buffer.
    txBufferLength = 0;
    
    return ret;
}

//	This provides backwards compatibility with the original
//	definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void)
{
  return endTransmission(true);
}

size_t TwoWire::write(uint8_t data) {
  if (status == MASTER_SEND) {
    if (txBufferLength >= BUFFER_LENGTH)
      return 0;
    txBuffer[txBufferLength++] = data;
    return 1;
  } else {
    if (srvBufferLength >= BUFFER_LENGTH)
      return 0;
    srvBuffer[srvBufferLength++] = data;
    return 1;
  }
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
  if (status == MASTER_SEND) {
    for (size_t i = 0; i < quantity; ++i) {
      if (txBufferLength >= BUFFER_LENGTH)
	return i;
      txBuffer[txBufferLength++] = data[i];
    }
  } else {
    for (size_t i = 0; i < quantity; ++i) {
      if (srvBufferLength >= BUFFER_LENGTH)
	return i;
      srvBuffer[srvBufferLength++] = data[i];
    }
  }
  return quantity;
}

int TwoWire::available(void) {
  return rxBufferLength - rxBufferIndex;
}

int TwoWire::read(void) {
  if (rxBufferIndex < rxBufferLength)
    return rxBuffer[rxBufferIndex++];
  return -1;
}

int TwoWire::peek(void) {
  if (rxBufferIndex < rxBufferLength)
    return rxBuffer[rxBufferIndex];
  return -1;
}

void TwoWire::flush(void) {
  // Do nothing, use endTransmission(..) to force
  // data transfer.
}

void TwoWire::onReceive(void(*function)(int)) {
  onReceiveCallback = function;
}

void TwoWire::onRequest(void(*function)(void)) {
  onRequestCallback = function;
}



#if WIRE_INTERFACES_COUNT > 0

TwoWire Wire0 = TwoWire(I2C_0);

#endif

#if WIRE_INTERFACES_COUNT > 1

TwoWire Wire1 = TwoWire(I2C_1);

#endif

#if WIRE_INTERFACES_COUNT > 2

TwoWire Wire2 = TwoWire(I2C_2);

#endif

#if WIRE_INTERFACES_COUNT > 3

TwoWire Wire3 = TwoWire(I2C_3);

#endif

