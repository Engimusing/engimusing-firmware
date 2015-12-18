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

#ifndef _LEUART_CLASS_
#define _LEUART_CLASS_

#include "RingBuffer.h"
#include "HardwareSerial.h"
#include "efm_lib/io_types.h"
#include "device/inc/efm32zg222f32.h"

typedef struct
{
  __IO uint32_t CTRL;          // Control Register
  __IO uint32_t CMD;           // Command Register
  __I uint32_t  STATUS;        // Status Register
  __IO uint32_t CLKDIV;        // Clock Control Register
  __IO uint32_t STARTFRAME;    // Start Frame Register
  __IO uint32_t SIGFRAME;      // Signal Frame Register
  __I uint32_t  RXDATAX;       // Receive Buffer Data Extended Register
  __I uint32_t  RXDATA;        // Receive Buffer Data Register
  __I uint32_t  RXDATAXP;      // Receive Buffer Data Extended Peek Register
  __IO uint32_t TXDATAX;       // Transmit Buffer Data Extended Register
  __IO uint32_t TXDATA;        // Transmit Buffer Data Register
  __I uint32_t  IF;            // Interrupt Flag Register
  __IO uint32_t IFS;           // Interrupt Flag Set Register
  __IO uint32_t IFC;           // Interrupt Flag Clear Register
  __IO uint32_t IEN;           // Interrupt Enable Register
  __IO uint32_t PULSECTRL;     // Pulse Control Register
  __IO uint32_t FREEZE;        // Freeze Register
  __I uint32_t  SYNCBUSY;      // Synchronization Busy Register
  uint32_t      RESERVED0[3];  // Reserved for future use
  __IO uint32_t ROUTE;         // I/O Routing Register
  uint32_t      RESERVED1[21]; // Reserved for future use
  __IO uint32_t INPUTREG;      // LEUART Input Register
} LEUART_TypeDef;

#define LEUART0      ((LEUART_TypeDef *) 0x40084000UL)      // LEUART0 base pointer
#define LEUART1      ((LEUART_TypeDef *) 0x40084400UL)      // LEUART1 base pointer

// Bit fields for LEUART CTRL
#define LEUART_CTRL_AUTOTRI               (0x1 << 0)        // Automatic Transmitter Tristate
#define LEUART_CTRL_DATABITS_NINE         (0x1 << 1)        // Shifted mode NINE for LEUART_CTRL
#define _LEUART_CTRL_PARITY_SHIFT                  2        // Shift value for LEUART_PARITY
#define _LEUART_CTRL_PARITY_MASK                 0xC        // Bit mask for LEUART_PARITY
#define LEUART_CTRL_PARITY_NONE           (0x0 << 2)        // Shifted mode NONE for LEUART_CTRL
#define LEUART_CTRL_PARITY_EVEN           (0x2 << 2)        // Shifted mode EVEN for LEUART_CTRL
#define LEUART_CTRL_PARITY_ODD            (0x3 << 2)        // Shifted mode ODD for LEUART_CTRL
#define LEUART_CTRL_STOPBITS_TWO          (0x1 << 4)        // Shifted mode TWO for LEUART_CTRL
#define LEUART_CTRL_INV                   (0x1 << 5)        // Invert Input And Output
#define LEUART_CTRL_ERRSDMA               (0x1 << 6)        // Clear RX DMA On Error
#define LEUART_CTRL_LOOPBK                (0x1 << 7)        // Loopback Enable
#define LEUART_CTRL_SFUBRX                (0x1 << 8)        // Start-Frame UnBlock RX
#define LEUART_CTRL_MPM                   (0x1 << 9)        // Multi-Processor Mode
#define LEUART_CTRL_MPAB                  (0x1 << 10)       // Multi-Processor Address-Bit
#define LEUART_CTRL_BIT8DV                (0x1 << 11)       // Bit 8 Default Value
#define LEUART_CTRL_RXDMAWU               (0x1 << 12)       // RX DMA Wakeup
#define LEUART_CTRL_TXDMAWU               (0x1 << 13)       // TX DMA Wakeup
#define LEUART_CTRL_TXDELAY_NONE          (0x0 << 14)       // Shifted mode NONE for LEUART_CTRL
#define LEUART_CTRL_TXDELAY_SINGLE        (0x1 << 14)       // Shifted mode SINGLE for LEUART_CTRL
#define LEUART_CTRL_TXDELAY_DOUBLE        (0x2 << 14)       // Shifted mode DOUBLE for LEUART_CTRL
#define LEUART_CTRL_TXDELAY_TRIPLE        (0x3 << 14)       // Shifted mode TRIPLE for LEUART_CTRL

// Bit fields for LEUART CMD
#define LEUART_CMD_RXEN                    (0x1 << 0)       // Receiver Enable
#define LEUART_CMD_RXDIS                   (0x1 << 1)       // Receiver Disable
#define LEUART_CMD_TXEN                    (0x1 << 2)       // Transmitter Enable
#define LEUART_CMD_TXDIS                   (0x1 << 3)       // Transmitter Disable
#define LEUART_CMD_RXBLOCKEN               (0x1 << 4)       // Receiver Block Enable
#define LEUART_CMD_RXBLOCKDIS              (0x1 << 5)       // Receiver Block Disable
#define LEUART_CMD_CLEARTX                 (0x1 << 6)       // Clear TX
#define LEUART_CMD_CLEARRX                 (0x1 << 7)       // Clear RX

// Bit fields for LEUART STATUS
#define LEUART_STATUS_RXENS                (0x1 << 0)       // Receiver Enable Status
#define LEUART_STATUS_TXENS                (0x1 << 1)       // Transmitter Enable Status
#define LEUART_STATUS_RXBLOCK              (0x1 << 2)       // Block Incoming Data
#define LEUART_STATUS_TXC                  (0x1 << 3)       // TX Complete
#define LEUART_STATUS_TXBL                 (0x1 << 4)       // TX Buffer Level
#define LEUART_STATUS_RXDATAV              (0x1 << 5)       // RX Data Valid

// Bit fields for LEUART CLKDIV
#define _LEUART_CLKDIV_DIV_SHIFT                    3       // Shift value for LEUART_DIV
#define _LEUART_CLKDIV_DIV_MASK                0x7FF8       // Bit mask for LEUART_DIV

// Bit fields for LEUART STARTFRAME
#define _LEUART_STARTFRAME_STARTFRAME_MASK      0x1FF       // Bit mask for LEUART_STARTFRAME

// Bit fields for LEUART SIGFRAME
#define _LEUART_SIGFRAME_SIGFRAME_MASK          0x1FF       // Bit mask for LEUART_SIGFRAME

// Bit fields for LEUART RXDATAX
#define _LEUART_RXDATAX_RXDATA_MASK             0x1FF       // Bit mask for LEUART_RXDATA
#define LEUART_RXDATAX_PERR               (0x1 << 14)       // Receive Data Parity Error
#define LEUART_RXDATAX_FERR               (0x1 << 15)       // Receive Data Framing Error

// Bit fields for LEUART RXDATA
#define _LEUART_RXDATA_RXDATA_MASK               0xFF       // Bit mask for LEUART_RXDATA

// Bit fields for LEUART RXDATAXP
#define _LEUART_RXDATAXP_RXDATAP_MASK           0x1FF       // Bit mask for LEUART_RXDATAP
#define LEUART_RXDATAXP_PERRP             (0x1 << 14)       // Receive Data Parity Error Peek
#define LEUART_RXDATAXP_FERRP             (0x1 << 15)       // Receive Data Framing Error Peek

// Bit fields for LEUART TXDATAX
#define _LEUART_TXDATAX_TXDATA_MASK             0x1FF       // Bit mask for LEUART_TXDATA
#define LEUART_TXDATAX_TXBREAK            (0x1 << 13)       // Transmit Data As Break
#define LEUART_TXDATAX_TXDISAT            (0x1 << 14)       // Disable TX After Transmission
#define LEUART_TXDATAX_RXENAT             (0x1 << 15)       // Enable RX After Transmission

// Bit fields for LEUART TXDATA
#define _LEUART_TXDATA_TXDATA_MASK               0xFF       // Bit mask for LEUART_TXDATA

// Bit fields for LEUART IF
#define LEUART_IF_TXC                       (0x1 << 0)      // TX Complete Interrupt Flag
#define LEUART_IF_TXBL                      (0x1 << 1)      // TX Buffer Level Interrupt Flag
#define LEUART_IF_RXDATAV                   (0x1 << 2)      // RX Data Valid Interrupt Flag
#define LEUART_IF_RXOF                      (0x1 << 3)      // RX Overflow Interrupt Flag
#define LEUART_IF_RXUF                      (0x1 << 4)      // RX Underflow Interrupt Flag
#define LEUART_IF_TXOF                      (0x1 << 5)      // TX Overflow Interrupt Flag
#define LEUART_IF_PERR                      (0x1 << 6)      // Parity Error Interrupt Flag
#define LEUART_IF_FERR                      (0x1 << 7)      // Framing Error Interrupt Flag
#define LEUART_IF_MPAF                      (0x1 << 8)      // Multi-Processor Address Frame Interrupt Flag
#define LEUART_IF_STARTF                    (0x1 << 9)      // Start Frame Interrupt Flag
#define LEUART_IF_SIGF                     (0x1 << 10)      // Signal Frame Interrupt Flag

// Bit fields for LEUART IFS
#define LEUART_IFS_TXC                      (0x1 << 0)      // Set TX Complete Interrupt Flag
#define LEUART_IFS_RXOF                     (0x1 << 3)      // Set RX Overflow Interrupt Flag
#define LEUART_IFS_RXUF                     (0x1 << 4)      // Set RX Underflow Interrupt Flag
#define LEUART_IFS_TXOF                     (0x1 << 5)      // Set TX Overflow Interrupt Flag
#define LEUART_IFS_PERR                     (0x1 << 6)      // Set Parity Error Interrupt Flag
#define LEUART_IFS_FERR                     (0x1 << 7)      // Set Framing Error Interrupt Flag
#define LEUART_IFS_MPAF                     (0x1 << 8)      // Set Multi-Processor Address Frame Interrupt Flag
#define LEUART_IFS_STARTF                   (0x1 << 9)      // Set Start Frame Interrupt Flag
#define LEUART_IFS_SIGF                    (0x1 << 10)      // Set Signal Frame Interrupt Flag

// Bit fields for LEUART IFC
#define _LEUART_IFC_MASK                         0x7F9      // Mask for LEUART_IFC
#define LEUART_IFC_TXC                      (0x1 << 0)      // Clear TX Complete Interrupt Flag
#define LEUART_IFC_RXOF                     (0x1 << 3)      // Clear RX Overflow Interrupt Flag
#define LEUART_IFC_RXUF                     (0x1 << 4)      // Clear RX Underflow Interrupt Flag
#define LEUART_IFC_TXOF                     (0x1 << 5)      // Clear TX Overflow Interrupt Flag
#define LEUART_IFC_PERR                     (0x1 << 6)      // Clear Parity Error Interrupt Flag
#define LEUART_IFC_FERR                     (0x1 << 7)      // Clear Framing Error Interrupt Flag
#define LEUART_IFC_MPAF                     (0x1 << 8)      // Clear Multi-Processor Address Frame Interrupt Flag
#define LEUART_IFC_STARTF                   (0x1 << 9)      // Clear Start-Frame Interrupt Flag
#define LEUART_IFC_SIGF                    (0x1 << 10)      // Clear Signal-Frame Interrupt Flag

// Bit fields for LEUART IEN
#define LEUART_IEN_TXC                      (0x1 << 0)       // TX Complete Interrupt Enable
#define LEUART_IEN_TXBL                     (0x1 << 1)       // TX Buffer Level Interrupt Enable
#define LEUART_IEN_RXDATAV                  (0x1 << 2)       // RX Data Valid Interrupt Enable
#define LEUART_IEN_RXOF                     (0x1 << 3)       // RX Overflow Interrupt Enable
#define LEUART_IEN_RXUF                     (0x1 << 4)       // RX Underflow Interrupt Enable
#define LEUART_IEN_TXOF                     (0x1 << 5)       // TX Overflow Interrupt Enable
#define LEUART_IEN_PERR                     (0x1 << 6)       // Parity Error Interrupt Enable
#define LEUART_IEN_FERR                     (0x1 << 7)       // Framing Error Interrupt Enable
#define LEUART_IEN_MPAF                     (0x1 << 8)       // Multi-Processor Address Frame Interrupt Enable
#define LEUART_IEN_STARTF                   (0x1 << 9)       // Start Frame Interrupt Enable
#define LEUART_IEN_SIGF                    (0x1 << 10)       // Signal Frame Interrupt Enable

// Bit fields for LEUART PULSECTRL
#define _LEUART_PULSECTRL_PULSEW_MASK              0xF       // Bit mask for LEUART_PULSEW
#define LEUART_PULSECTRL_PULSEEN            (0x1 << 4)       // Pulse Generator/Extender Enable
#define LEUART_PULSECTRL_PULSEFILT          (0x1 << 5)       // Pulse Filter

// Bit fields for LEUART FREEZE
#define LEUART_FREEZE_REGFREEZE_UPDATE             0x0       // Shifted mode UPDATE for LEUART_FREEZE
#define LEUART_FREEZE_REGFREEZE_FREEZE             0x1       // Shifted mode FREEZE for LEUART_FREEZE

// Bit fields for LEUART SYNCBUSY
#define LEUART_SYNCBUSY_CTRL                 (0x1 << 0)      // CTRL Register Busy
#define LEUART_SYNCBUSY_CMD                  (0x1 << 1)      // CMD Register Busy
#define LEUART_SYNCBUSY_CLKDIV               (0x1 << 2)      // CLKDIV Register Busy
#define LEUART_SYNCBUSY_STARTFRAME           (0x1 << 3)      // STARTFRAME Register Busy
#define LEUART_SYNCBUSY_SIGFRAME             (0x1 << 4)      // SIGFRAME Register Busy
#define LEUART_SYNCBUSY_TXDATAX              (0x1 << 5)      // TXDATAX Register Busy
#define LEUART_SYNCBUSY_TXDATA               (0x1 << 6)      // TXDATA Register Busy
#define LEUART_SYNCBUSY_PULSECTRL            (0x1 << 7)      // PULSECTRL Register Busy

// Bit fields for LEUART ROUTE
#define LEUART_ROUTE_RXPEN                   (0x1 << 0)      // RX Pin Enable
#define LEUART_ROUTE_TXPEN                   (0x1 << 1)      // TX Pin Enable
#define _LEUART_ROUTE_LOCATION_SHIFT                  8      // Shift value for LEUART_LOCATION
#define _LEUART_ROUTE_LOCATION_MASK               0x700      // Bit mask for LEUART_LOCATION
#define LEUART_ROUTE_LOCATION_LOC0             (0 << 8)      // Shifted mode LOC0 for LEUART_ROUTE
#define LEUART_ROUTE_LOCATION_LOC1             (1 << 8)      // Shifted mode LOC1 for LEUART_ROUTE
#define LEUART_ROUTE_LOCATION_LOC2             (2 << 8)      // Shifted mode LOC2 for LEUART_ROUTE
#define LEUART_ROUTE_LOCATION_LOC3             (3 << 8)      // Shifted mode LOC3 for LEUART_ROUTE
#define LEUART_ROUTE_LOCATION_LOC4             (4 << 8)      // Shifted mode LOC4 for LEUART_ROUTE

// Bit fields for LEUART INPUT
#define _LEUART_INPUT_RXPRSSEL_SHIFT                  0      // Shift value for LEUART_RXPRSSEL
#define _LEUART_INPUT_RXPRSSEL_MASK                 0x3      // Bit mask for LEUART_RXPRSSEL
#define LEUART_INPUT_RXPRSSEL_PRSCH0                0x0      // Shifted mode PRSCH0 for LEUART_INPUT
#define LEUART_INPUT_RXPRSSEL_PRSCH1                0x1      // Shifted mode PRSCH1 for LEUART_INPUT
#define LEUART_INPUT_RXPRSSEL_PRSCH2                0x2      // Shifted mode PRSCH2 for LEUART_INPUT
#define LEUART_INPUT_RXPRSSEL_PRSCH3                0x3      // Shifted mode PRSCH3 for LEUART_INPUT
#define LEUART_INPUT_RXPRS                   (0x1 << 4)      // PRS RX Enable


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

#endif // _LEUART_CLASS_
