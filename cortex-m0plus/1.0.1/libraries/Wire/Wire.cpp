/*
 * TwoWire.h - TWI/I2C library for Arduino Due
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

TwoWire::TwoWire(I2C_TypeDef * _i2c, uint8_t location, CMU_Clock_TypeDef _i2cClock, void(*_beginCb)(void)) :
  i2c(_i2c), rxBufferIndex(0), rxBufferLength(0), txAddress(0),
  txBufferLength(0), srvBufferIndex(0), srvBufferLength(0), 
  status(UNINITIALIZED), onBeginCallback(_beginCb), myLocation(location), i2cClock(_i2cClock) {
  // Empty

}

static I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

void TwoWire::begin(void) {
	
  if (onBeginCallback)
    onBeginCallback();

  /* Enable High Frequency Peripherals */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(i2cClock, true);

  i2c->ROUTE = I2C_ROUTE_SDAPEN |
    I2C_ROUTE_SCLPEN |
    (myLocation << _I2C_ROUTE_LOCATION_SHIFT);
	
				
  status = MASTER_IDLE;
	
  I2C_Init(i2c, &i2cInit);
  I2C_Enable(i2c, true);
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
  if(sendStop == false)
    {
      status = MASTER_IDLE;
      return 0;
    }
  myCurTransmission.addr = (txAddress << 1); //convert to 8-bit address for energy micro
	
  if(txBufferLength > 0)
    {
      myCurTransmission.buf[0].data = &txBuffer[0];
      myCurTransmission.buf[0].len = 1;
      myCurTransmission.flags = I2C_FLAG_WRITE;
	
      if(rxBufferLength > 0)//assume it is a read transmission
	{	
	  myCurTransmission.buf[1].data = &rxBuffer[0];
	  myCurTransmission.buf[1].len = rxBufferLength;
	  myCurTransmission.flags = I2C_FLAG_WRITE_READ;
	}else if(txBufferLength > 1)
	{
	  myCurTransmission.buf[1].data = &txBuffer[1];
	  myCurTransmission.buf[1].len = txBufferLength - 1;
	  myCurTransmission.flags = I2C_FLAG_WRITE_WRITE;
	}
	
    }else if(rxBufferLength > 0)
    {
      myCurTransmission.buf[0].data = &rxBuffer[0];
      myCurTransmission.buf[0].len = rxBufferLength;
      myCurTransmission.flags = I2C_FLAG_READ;
    }else
    {
      status = MASTER_IDLE;
      return 0;
    }
	

  // transmit buffer (blocking)
  I2C_TransferReturn_TypeDef ret = I2C_TransferInit(i2c,&myCurTransmission);
  while (ret == i2cTransferInProgress)
    {
      ret = I2C_Transfer(i2c);
    }
  // empty buffer
  txBufferLength = 0;

  status = MASTER_IDLE;
	
  if(ret == i2cTransferDone)
    {
      //return the number of bytes sent and recieved
      return myCurTransmission.buf[0].len + myCurTransmission.buf[1].len;
    }else
    {
      return 0;
    }
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

void TwoWire::onService(void) {
	
  //not supported yet
  return;
  /*
  // Retrieve interrupt status
  uint32_t sr = TWI_GetStatus(twi);

  if (status == SLAVE_IDLE && TWI_STATUS_SVACC(sr)) {
  TWI_DisableIt(twi, TWI_IDR_SVACC);
  TWI_EnableIt(twi, TWI_IER_RXRDY | TWI_IER_GACC | TWI_IER_NACK
  | TWI_IER_EOSACC | TWI_IER_SCL_WS | TWI_IER_TXCOMP);

  srvBufferLength = 0;
  srvBufferIndex = 0;

  // Detect if we should go into RECV or SEND status
  // SVREAD==1 means *master* reading -> SLAVE_SEND
  if (!TWI_STATUS_SVREAD(sr)) {
  status = SLAVE_RECV;
  } else {
  status = SLAVE_SEND;

  // Alert calling program to generate a response ASAP
  if (onRequestCallback)
  onRequestCallback();
  else
  // create a default 1-byte response
  write((uint8_t) 0);
  }
  }

  if (status != SLAVE_IDLE) {
  if (TWI_STATUS_TXCOMP(sr) && TWI_STATUS_EOSACC(sr)) {
  if (status == SLAVE_RECV && onReceiveCallback) {
  // Copy data into rxBuffer
  // (allows to receive another packet while the
  // user program reads actual data)
  for (uint8_t i = 0; i < srvBufferLength; ++i)
  rxBuffer[i] = srvBuffer[i];
  rxBufferIndex = 0;
  rxBufferLength = srvBufferLength;

  // Alert calling program
  onReceiveCallback( rxBufferLength);
  }

  // Transfer completed
  TWI_EnableIt(twi, TWI_SR_SVACC);
  TWI_DisableIt(twi, TWI_IDR_RXRDY | TWI_IDR_GACC | TWI_IDR_NACK
  | TWI_IDR_EOSACC | TWI_IDR_SCL_WS | TWI_IER_TXCOMP);
  status = SLAVE_IDLE;
  }
  }

  if (status == SLAVE_RECV) {
  if (TWI_STATUS_RXRDY(sr)) {
  if (srvBufferLength < BUFFER_LENGTH)
  srvBuffer[srvBufferLength++] = TWI_ReadByte(twi);
  }
  }

  if (status == SLAVE_SEND) {
  if (TWI_STATUS_TXRDY(sr) && !TWI_STATUS_NACK(sr)) {
  uint8_t c = 'x';
  if (srvBufferIndex < srvBufferLength)
  c = srvBuffer[srvBufferIndex++];
  TWI_WriteByte(twi, c);
  }
  }
  */
}

#if WIRE_INTERFACES_COUNT > 0

static void Wire0_Init(void) {

  CMU_ClockEnable(cmuClock_HFPER, true);

  pinMode(
		  PIN_WIRE0_SDA,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(PIN_WIRE0_SDA, 1);
  pinMode(
		  PIN_WIRE0_SCL,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(PIN_WIRE0_SCL, 1);
			
  //NVIC_DisableIRQ(I2C0_IRQn);
  //NVIC_ClearPendingIRQ(I2C0_IRQn);
  //NVIC_SetPriority(I2C0_IRQn, 0);
  //NVIC_EnableIRQ(I2C0_IRQn);
}

TwoWire Wire0 = TwoWire(WIRE0_INTERFACE, WIRE0_LOC, WIRE0_CLOCK, Wire0_Init);

void WIRE0_ISR_HANDLER(void) {
  Wire0.onService();
#if WIRE_INTERFACES_COUNT > 1
#if WIRE0_ISR_HANDLER == WIRE1_ISR_HANDLER
  Wire1.onService();
#endif
#endif
#if WIRE_INTERFACES_COUNT > 2
#if WIRE0_ISR_HANDLER == WIRE2_ISR_HANDLER
  Wire2.onService();
#endif
#endif
#if WIRE_INTERFACES_COUNT > 3
#if WIRE0_ISR_HANDLER == WIRE3_ISR_HANDLER
  Wire3.onService();
#endif
#endif
}
#endif

#if WIRE_INTERFACES_COUNT > 1
static void Wire1_Init(void) {

  CMU_ClockEnable(cmuClock_HFPER, true);

	
  pinMode(
		  PIN_WIRE1_SDA,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(PIN_WIRE1_SDA, 1);
  pinMode(
		  PIN_WIRE1_SCL,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(PIN_WIRE1_SCL, 1);
		  
  //NVIC_DisableIRQ(I2C0_IRQn);
  //NVIC_ClearPendingIRQ(I2C0_IRQn);
  //NVIC_SetPriority(I2C0_IRQn, 0);
  //NVIC_EnableIRQ(I2C0_IRQn);
}

TwoWire Wire1 = TwoWire(WIRE1_INTERFACE, WIRE1_LOC, WIRE1_CLOCK, Wire1_Init);

#if WIRE0_ISR_HANDLER != WIRE1_ISR_HANDLER
void WIRE1_ISR_HANDLER(void) {
  Wire1.onService();
#if WIRE_INTERFACES_COUNT > 2
#if WIRE1_ISR_HANDLER == WIRE2_ISR_HANDLER
  Wire2.onService();
#endif
#endif
#if WIRE_INTERFACES_COUNT > 3
#if WIRE1_ISR_HANDLER == WIRE3_ISR_HANDLER
  Wire3.onService();
#endif
#endif
}
#endif

#endif

#if WIRE_INTERFACES_COUNT > 2
static void Wire2_Init(void) {

  CMU_ClockEnable(cmuClock_HFPER, true);
	
	
  pinMode(
		  PIN_WIRE2_SDA,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(PIN_WIRE2_SDA, 1);
  pinMode(
		  PIN_WIRE2_SCL,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(PIN_WIRE2_SCL, 1);
  
  
  //NVIC_DisableIRQ(I2C0_IRQn);
  //NVIC_ClearPendingIRQ(I2C0_IRQn);
  //NVIC_SetPriority(I2C0_IRQn, 0);
  //NVIC_EnableIRQ(I2C0_IRQn);
}

TwoWire Wire2 = TwoWire(WIRE2_INTERFACE, WIRE2_LOC, WIRE2_CLOCK, Wire2_Init);
#if WIRE0_ISR_HANDLER != WIRE2_ISR_HANDLER && \
	 WIRE1_ISR_HANDLER != WIRE2_ISR_HANDLER 
void WIRE2_ISR_HANDLER(void) {
  Wire2.onService();
#if WIRE_INTERFACES_COUNT > 3
#if WIRE2_ISR_HANDLER == WIRE3_ISR_HANDLER
  Wire3.onService();
#endif
#endif
}
#endif

#endif

#if WIRE_INTERFACES_COUNT > 3
static void Wire3_Init(void) {

  CMU_ClockEnable(cmuClock_HFPER, true);
	
	
  pinMode(
		  PIN_WIRE3_SDA,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(PIN_WIRE3_SDA, 1);
  pinMode(
		  PIN_WIRE3_SCL,
		  gpioModeWiredAndPullUpFilter);
  digitalWrite(PIN_WIRE3_SCL, 1);
  

  //NVIC_DisableIRQ(I2C0_IRQn);
  //NVIC_ClearPendingIRQ(I2C0_IRQn);
  //NVIC_SetPriority(I2C0_IRQn, 0);
  //NVIC_EnableIRQ(I2C0_IRQn);
}

TwoWire Wire3 = TwoWire(WIRE3_INTERFACE, WIRE3_LOC, WIRE3_CLOCK, Wire3_Init);

#if WIRE0_ISR_HANDLER != WIRE3_ISR_HANDLER && \
	 WIRE1_ISR_HANDLER != WIRE3_ISR_HANDLER && \
	 WIRE2_ISR_HANDLER != WIRE3_ISR_HANDLER
void WIRE3_ISR_HANDLER(void) {
  Wire3.onService();
}
#endif

#endif

