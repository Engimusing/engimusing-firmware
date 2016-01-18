/*
  Copyright (c) 2015 Engimusing.  All right reserved.
  Copyright (c) 2011 Arduino.  All right reserved.

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

#include "RingBuffer.h"
#include "HardwareSerial.h"
#include "efm_leuart.h"


typedef LEUART_TypeDef Leuart;

class LEUARTClass : public HardwareSerial
{
 public:
  LEUARTClass(Leuart *pUart, IRQn_Type dwIrq, uint32_t dwId, RingBuffer *pRx_buffer, RingBuffer *pTx_buffer, uint8_t port, uint8_t txpin, uint8_t rxpin, uint32_t location, uint32_t cmu_clken, uint32_t leuart_clkdiv);

  void   begin(const uint32_t dwBaudRate);
  void   begin(const uint32_t dwBaudRate, uint8_t config);
  void   end(void);
  int    available(void);
  int    availableForWrite(void);
  int    peek(void);
  int    read(void);
  void   flush(void);
  size_t write(const uint8_t c);
  using  Print::write; // pull in write(str) and write(buf, size) from Print

  void     setInterruptPriority(uint32_t priority);
  uint32_t getInterruptPriority();

  void IrqHandler(void);

  void chk_reset(void);

  operator bool() { return true; }; // LEUART0 always active

 protected:
  void init(const uint32_t dwBaudRate, uint8_t config);

  RingBuffer *_rx_buffer;
  RingBuffer *_tx_buffer;

  Leuart* _pUart;
  IRQn_Type _dwIrq;
  uint32_t _dwId;
  uint8_t _port;
  uint8_t _txpin;
  uint8_t _rxpin;
  uint32_t _location;
  uint32_t _cmu_clken;
  uint32_t _clkdiv;

};

