/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.

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

#include "io_types.h"
#include "cmsis.h"

typedef struct
{
  __IO uint32_t CTRL;       // Control Register
  __IO uint32_t FRAME;      // USART Frame Format Register
  __IO uint32_t TRIGCTRL;   // USART Trigger Control register
  __IO uint32_t CMD;        // Command Register
  __I uint32_t  STATUS;     // USART Status Register
  __IO uint32_t CLKDIV;     // Clock Control Register
  __I uint32_t  RXDATAX;    // RX Buffer Data Extended Register
  __I uint32_t  RXDATA;     // RX Buffer Data Register
  __I uint32_t  RXDOUBLEX;  // RX Buffer Double Data Extended Register
  __I uint32_t  RXDOUBLE;   // RX FIFO Double Data Register
  __I uint32_t  RXDATAXP;   // RX Buffer Data Extended Peek Register
  __I uint32_t  RXDOUBLEXP; // RX Buffer Double Data Extended Peek Register
  __IO uint32_t TXDATAX;    // TX Buffer Data Extended Register
  __IO uint32_t TXDATA;     // TX Buffer Data Register
  __IO uint32_t TXDOUBLEX;  // TX Buffer Double Data Extended Register
  __IO uint32_t TXDOUBLE;   // TX Buffer Double Data Register
  __I uint32_t  IF;         // Interrupt Flag Register
  __IO uint32_t IFS;        // Interrupt Flag Set Register
  __IO uint32_t IFC;        // Interrupt Flag Clear Register
  __IO uint32_t IEN;        // Interrupt Enable Register
  __IO uint32_t IRCTRL;     // IrDA Control Register
  __IO uint32_t ROUTE;      // I/O Routing Register
  __IO uint32_t INPUT;      // USART Input Register
  __IO uint32_t I2SCTRL;    // I2S Control Register
} USART_TypeDef;

#define USART0       ((USART_TypeDef *) 0x4000C000UL)        // USART0 base pointer
#define USART1       ((USART_TypeDef *) 0x4000C400UL)        // USART1 base pointer
#define USART2       ((USART_TypeDef *) 0x4000C800UL)        // USART2 base pointer


// Bit fields for USART CTRL
#define USART_CTRL_SYNC                       (0x1UL << 0)                       // USART Synchronous Mode
#define USART_CTRL_SYNC_MASK                   0x1UL                             // Bit mask for USART_SYNC

#define USART_CTRL_LOOPBK                     (0x1UL << 1)                       // Loopback Enable
#define USART_CTRL_LOOPBK_MASK                 0x2UL                             // Bit mask for USART_LOOPBK

#define USART_CTRL_CCEN                       (0x1UL << 2)                       // Collision Check Enable
#define USART_CTRL_CCEN_MASK                   0x4UL                             // Bit mask for USART_CCEN

#define USART_CTRL_MPM                        (0x1UL << 3)                       // Multi-Processor Mode
#define USART_CTRL_MPM_MASK                    0x8UL                             // Bit mask for USART_MPM

#define USART_CTRL_MPAB                       (0x1UL << 4)                       // Multi-Processor Address-Bit
#define USART_CTRL_MPAB_MASK                   0x10UL                            // Bit mask for USART_MPAB

#define USART_CTRL_OVS_MASK                    0x60UL                            // Bit mask for USART_OVS
#define USART_CTRL_OVS_X16                    (0x00000000UL << 5)                // Shifted mode X16 for USART_CTRL
#define USART_CTRL_OVS_X8                     (0x00000001UL << 5)                // Shifted mode X8 for USART_CTRL
#define USART_CTRL_OVS_X6                     (0x00000002UL << 5)                // Shifted mode X6 for USART_CTRL
#define USART_CTRL_OVS_X4                     (0x00000003UL << 5)                // Shifted mode X4 for USART_CTRL

#define USART_CTRL_CLKPOL                     (0x1UL << 8)                       // Clock Polarity
#define USART_CTRL_CLKPOL_MASK                 0x100UL                           // Bit mask for USART_CLKPOL
#define USART_CTRL_CLKPOL_IDLELOW             (0x00000000UL << 8)                // Shifted mode IDLELOW for USART_CTRL
#define USART_CTRL_CLKPOL_IDLEHIGH            (0x00000001UL << 8)                // Shifted mode IDLEHIGH for USART_CTRL

#define USART_CTRL_CLKPHA                     (0x1UL << 9)                       // Clock Edge For Setup/Sample
#define USART_CTRL_CLKPHA_MASK                 0x200UL                           // Bit mask for USART_CLKPHA
#define USART_CTRL_CLKPHA_SAMPLELEADING       (0x00000000UL << 9)                // Shifted mode SAMPLELEADING for USART_CTRL
#define USART_CTRL_CLKPHA_SAMPLETRAILING      (0x00000001UL << 9)                // Shifted mode SAMPLETRAILING for USART_CTRL

#define USART_CTRL_MSBF                       (0x1UL << 10)                      // Most Significant Bit First
#define USART_CTRL_MSBF_MASK                   0x400UL                           // Bit mask for USART_MSBF

#define USART_CTRL_CSMA                       (0x1UL << 11)                      // Action On Slave-Select In Master Mode
#define USART_CTRL_CSMA_MASK                   0x800UL                           // Bit mask for USART_CSMA
#define USART_CTRL_CSMA_NOACTION              (0x00000000UL << 11)               // Shifted mode NOACTION for USART_CTRL
#define USART_CTRL_CSMA_GOTOSLAVEMODE         (0x00000001UL << 11)               // Shifted mode GOTOSLAVEMODE for USART_CTRL

#define USART_CTRL_TXBIL                      (0x1UL << 12)                      // TX Buffer Interrupt Level
#define USART_CTRL_TXBIL_MASK                  0x1000UL                          // Bit mask for USART_TXBIL
#define USART_CTRL_TXBIL_EMPTY                (0x00000000UL << 12)               // Shifted mode EMPTY for USART_CTRL
#define USART_CTRL_TXBIL_HALFFULL             (0x00000001UL << 12)               // Shifted mode HALFFULL for USART_CTRL

#define USART_CTRL_RXINV                      (0x1UL << 13)                      // Receiver Input Invert
#define USART_CTRL_RXINV_MASK                  0x2000UL                          // Bit mask for USART_RXINV

#define USART_CTRL_TXINV                      (0x1UL << 14)                      // Transmitter output Invert
#define USART_CTRL_TXINV_MASK                  0x4000UL                          // Bit mask for USART_TXINV

#define USART_CTRL_CSINV                      (0x1UL << 15)                      // Chip Select Invert
#define USART_CTRL_CSINV_MASK                  0x8000UL                          // Bit mask for USART_CSINV

#define USART_CTRL_AUTOCS                     (0x1UL << 16)                      // Automatic Chip Select
#define USART_CTRL_AUTOCS_MASK                 0x10000UL                         // Bit mask for USART_AUTOCS

#define USART_CTRL_AUTOTRI                    (0x1UL << 17)                      // Automatic TX Tristate
#define USART_CTRL_AUTOTRI_MASK                0x20000UL                         // Bit mask for USART_AUTOTRI

#define USART_CTRL_SCMODE                     (0x1UL << 18)                      // SmartCard Mode
#define USART_CTRL_SCMODE_MASK                 0x40000UL                         // Bit mask for USART_SCMODE

#define USART_CTRL_SCRETRANS                  (0x1UL << 19)                      // SmartCard Retransmit
#define USART_CTRL_SCRETRANS_MASK              0x80000UL                         // Bit mask for USART_SCRETRANS

#define USART_CTRL_SKIPPERRF                  (0x1UL << 20)                      // Skip Parity Error Frames
#define USART_CTRL_SKIPPERRF_MASK              0x100000UL                        // Bit mask for USART_SKIPPERRF

#define USART_CTRL_BIT8DV                     (0x1UL << 21)                      // Bit 8 Default Value
#define USART_CTRL_BIT8DV_MASK                 0x200000UL                        // Bit mask for USART_BIT8DV

#define USART_CTRL_ERRSDMA                    (0x1UL << 22)                      // Halt DMA On Error
#define USART_CTRL_ERRSDMA_MASK                0x400000UL                        // Bit mask for USART_ERRSDMA

#define USART_CTRL_ERRSRX                     (0x1UL << 23)                      // Disable RX On Error
#define USART_CTRL_ERRSRX_MASK                 0x800000UL                        // Bit mask for USART_ERRSRX

#define USART_CTRL_ERRSTX                     (0x1UL << 24)                      // Disable TX On Error
#define USART_CTRL_ERRSTX_MASK                 0x1000000UL                       // Bit mask for USART_ERRSTX

#define USART_CTRL_SSSEARLY                   (0x1UL << 25)                      // Synchronous Slave Setup Early
#define USART_CTRL_SSSEARLY_MASK               0x2000000UL                       // Bit mask for USART_SSSEARLY

#define USART_CTRL_TXDELAY_MASK                0xC000000UL                       // Bit mask for USART_TXDELAY
#define USART_CTRL_TXDELAY_NONE               (0x00000000UL << 26)               // Shifted mode NONE for USART_CTRL
#define USART_CTRL_TXDELAY_SINGLE             (0x00000001UL << 26)               // Shifted mode SINGLE for USART_CTRL
#define USART_CTRL_TXDELAY_DOUBLE             (0x00000002UL << 26)               // Shifted mode DOUBLE for USART_CTRL
#define USART_CTRL_TXDELAY_TRIPLE             (0x00000003UL << 26)               // Shifted mode TRIPLE for USART_CTRL

#define USART_CTRL_BYTESWAP                   (0x1UL << 28)                      // Byteswap In Double Accesses
#define USART_CTRL_BYTESWAP_MASK               0x10000000UL                      // Bit mask for USART_BYTESWAP

#define USART_CTRL_AUTOTX                     (0x1UL << 29)                      // Always Transmit When RX Not Full
#define USART_CTRL_AUTOTX_MASK                 0x20000000UL                      // Bit mask for USART_AUTOTX

#define USART_CTRL_MVDIS                      (0x1UL << 30)                      // Majority Vote Disable
#define USART_CTRL_MVDIS_MASK                  0x40000000UL                      // Bit mask for USART_MVDIS

#define USART_CTRL_SMSDELAY                   (0x1UL << 31)                      // Synchronous Master Sample Delay
#define USART_CTRL_SMSDELAY_MASK               0x80000000UL                      // Bit mask for USART_SMSDELAY

// Bit fields for USART FRAME

#define USART_FRAME_DATABITS_MASK              0xFUL                              // Bit mask for USART_DATABITS
#define USART_FRAME_DATABITS_FOUR             (0x00000001UL << 0)                 // Shifted mode FOUR for USART_FRAME
#define USART_FRAME_DATABITS_FIVE             (0x00000002UL << 0)                 // Shifted mode FIVE for USART_FRAME
#define USART_FRAME_DATABITS_SIX              (0x00000003UL << 0)                 // Shifted mode SIX for USART_FRAME
#define USART_FRAME_DATABITS_SEVEN            (0x00000004UL << 0)                 // Shifted mode SEVEN for USART_FRAME
#define USART_FRAME_DATABITS_EIGHT            (0x00000005UL << 0)                 // Shifted mode EIGHT for USART_FRAME
#define USART_FRAME_DATABITS_NINE             (0x00000006UL << 0)                 // Shifted mode NINE for USART_FRAME
#define USART_FRAME_DATABITS_TEN              (0x00000007UL << 0)                 // Shifted mode TEN for USART_FRAME
#define USART_FRAME_DATABITS_ELEVEN           (0x00000008UL << 0)                 // Shifted mode ELEVEN for USART_FRAME
#define USART_FRAME_DATABITS_TWELVE           (0x00000009UL << 0)                 // Shifted mode TWELVE for USART_FRAME
#define USART_FRAME_DATABITS_THIRTEEN         (0x0000000AUL << 0)                 // Shifted mode THIRTEEN for USART_FRAME
#define USART_FRAME_DATABITS_FOURTEEN         (0x0000000BUL << 0)                 // Shifted mode FOURTEEN for USART_FRAME
#define USART_FRAME_DATABITS_FIFTEEN          (0x0000000CUL << 0)                 // Shifted mode FIFTEEN for USART_FRAME
#define USART_FRAME_DATABITS_SIXTEEN          (0x0000000DUL << 0)                 // Shifted mode SIXTEEN for USART_FRAME

#define USART_FRAME_PARITY_MASK                0x300UL                             // Bit mask for USART_PARITY
#define USART_FRAME_PARITY_NONE               (0x00000000UL << 8)                  // Shifted mode NONE for USART_FRAME
#define USART_FRAME_PARITY_EVEN               (0x00000002UL << 8)                  // Shifted mode EVEN for USART_FRAME
#define USART_FRAME_PARITY_ODD                (0x00000003UL << 8)                  // Shifted mode ODD for USART_FRAME

#define USART_FRAME_STOPBITS_MASK              0x3000UL                            // Bit mask for USART_STOPBITS
#define USART_FRAME_STOPBITS_HALF             (0x00000000UL << 12)                 // Shifted mode HALF for USART_FRAME
#define USART_FRAME_STOPBITS_ONE              (0x00000001UL << 12)                 // Shifted mode ONE for USART_FRAME
#define USART_FRAME_STOPBITS_ONEANDAHALF      (0x00000002UL << 12)                 // Shifted mode ONEANDAHALF for USART_FRAME
#define USART_FRAME_STOPBITS_TWO              (0x00000003UL << 12)                 // Shifted mode TWO for USART_FRAME

// Bit fields for USART TRIGCTRL

#define USART_TRIGCTRL_TSEL_MASK               0x7UL                               // Bit mask for USART_TSEL
#define USART_TRIGCTRL_TSEL_PRSCH0            (0x00000000UL << 0)                  // Shifted mode PRSCH0 for USART_TRIGCTRL
#define USART_TRIGCTRL_TSEL_PRSCH1            (0x00000001UL << 0)                  // Shifted mode PRSCH1 for USART_TRIGCTRL
#define USART_TRIGCTRL_TSEL_PRSCH2            (0x00000002UL << 0)                  // Shifted mode PRSCH2 for USART_TRIGCTRL
#define USART_TRIGCTRL_TSEL_PRSCH3            (0x00000003UL << 0)                  // Shifted mode PRSCH3 for USART_TRIGCTRL
#define USART_TRIGCTRL_TSEL_PRSCH4            (0x00000004UL << 0)                  // Shifted mode PRSCH4 for USART_TRIGCTRL
#define USART_TRIGCTRL_TSEL_PRSCH5            (0x00000005UL << 0)                  // Shifted mode PRSCH5 for USART_TRIGCTRL
#define USART_TRIGCTRL_TSEL_PRSCH6            (0x00000006UL << 0)                  // Shifted mode PRSCH6 for USART_TRIGCTRL
#define USART_TRIGCTRL_TSEL_PRSCH7            (0x00000007UL << 0)                  // Shifted mode PRSCH7 for USART_TRIGCTRL

#define USART_TRIGCTRL_RXTEN                  (0x1UL << 4)                         // Receive Trigger Enable
#define USART_TRIGCTRL_RXTEN_MASK              0x10UL                              // Bit mask for USART_RXTEN

#define USART_TRIGCTRL_TXTEN                  (0x1UL << 5)                         // Transmit Trigger Enable
#define USART_TRIGCTRL_TXTEN_MASK              0x20UL                              // Bit mask for USART_TXTEN

#define USART_TRIGCTRL_AUTOTXTEN              (0x1UL << 6)                         // AUTOTX Trigger Enable
#define USART_TRIGCTRL_AUTOTXTEN_MASK          0x40UL                              // Bit mask for USART_AUTOTXTEN

// Bit fields for USART CMD

#define USART_CMD_RXEN                        (0x1UL << 0)                          // Receiver Enable
#define USART_CMD_RXEN_MASK                    0x1UL                                // Bit mask for USART_RXEN

#define USART_CMD_RXDIS                       (0x1UL << 1)                          // Receiver Disable
#define USART_CMD_RXDIS_MASK                   0x2UL                                // Bit mask for USART_RXDIS

#define USART_CMD_TXEN                        (0x1UL << 2)                          // Transmitter Enable
#define USART_CMD_TXEN_MASK                    0x4UL                                // Bit mask for USART_TXEN

#define USART_CMD_TXDIS                       (0x1UL << 3)                          // Transmitter Disable
#define USART_CMD_TXDIS_MASK                   0x8UL                                // Bit mask for USART_TXDIS

#define USART_CMD_MASTEREN                    (0x1UL << 4)                          // Master Enable
#define USART_CMD_MASTEREN_MASK                0x10UL                               // Bit mask for USART_MASTEREN

#define USART_CMD_MASTERDIS                   (0x1UL << 5)                          // Master Disable
#define USART_CMD_MASTERDIS_MASK               0x20UL                               // Bit mask for USART_MASTERDIS

#define USART_CMD_RXBLOCKEN                   (0x1UL << 6)                          // Receiver Block Enable
#define USART_CMD_RXBLOCKEN_MASK               0x40UL                               // Bit mask for USART_RXBLOCKEN

#define USART_CMD_RXBLOCKDIS                  (0x1UL << 7)                          // Receiver Block Disable
#define USART_CMD_RXBLOCKDIS_MASK              0x80UL                               // Bit mask for USART_RXBLOCKDIS

#define USART_CMD_TXTRIEN                     (0x1UL << 8)                          // Transmitter Tristate Enable
#define USART_CMD_TXTRIEN_MASK                 0x100UL                              // Bit mask for USART_TXTRIEN

#define USART_CMD_TXTRIDIS                    (0x1UL << 9)                          // Transmitter Tristate Disable
#define USART_CMD_TXTRIDIS_MASK                0x200UL                              // Bit mask for USART_TXTRIDIS

#define USART_CMD_CLEARTX                     (0x1UL << 10)                         // Clear TX
#define USART_CMD_CLEARTX_MASK                 0x400UL                              // Bit mask for USART_CLEARTX

#define USART_CMD_CLEARRX                     (0x1UL << 11)                         // Clear RX
#define USART_CMD_CLEARRX_MASK                 0x800UL                              // Bit mask for USART_CLEARRX

// Bit fields for USART STATUS

#define USART_STATUS_RXENS                    (0x1UL << 0)                          // Receiver Enable Status
#define USART_STATUS_RXENS_MASK                0x1UL                                // Bit mask for USART_RXENS

#define USART_STATUS_TXENS                    (0x1UL << 1)                          // Transmitter Enable Status
#define USART_STATUS_TXENS_MASK                0x2UL                                // Bit mask for USART_TXENS

#define USART_STATUS_MASTER                   (0x1UL << 2)                          // SPI Master Mode
#define USART_STATUS_MASTER_MASK               0x4UL                                // Bit mask for USART_MASTER

#define USART_STATUS_RXBLOCK                  (0x1UL << 3)                          // Block Incoming Data
#define USART_STATUS_RXBLOCK_MASK              0x8UL                                // Bit mask for USART_RXBLOCK

#define USART_STATUS_TXTRI                    (0x1UL << 4)                          // Transmitter Tristated
#define USART_STATUS_TXTRI_MASK                0x10UL                               // Bit mask for USART_TXTRI

#define USART_STATUS_TXC                      (0x1UL << 5)                          // TX Complete
#define USART_STATUS_TXC_MASK                  0x20UL                               // Bit mask for USART_TXC

#define USART_STATUS_TXBL                     (0x1UL << 6)                          // TX Buffer Level
#define USART_STATUS_TXBL_MASK                 0x40UL                               // Bit mask for USART_TXBL

#define USART_STATUS_RXDATAV                  (0x1UL << 7)                          // RX Data Valid
#define USART_STATUS_RXDATAV_MASK              0x80UL                               // Bit mask for USART_RXDATAV

#define USART_STATUS_RXFULL                   (0x1UL << 8)                          // RX FIFO Full
#define USART_STATUS_RXFULL_MASK               0x100UL                              // Bit mask for USART_RXFULL

#define USART_STATUS_TXBDRIGHT                (0x1UL << 9)                          // TX Buffer Expects Double Right Data
#define USART_STATUS_TXBDRIGHT_MASK            0x200UL                              // Bit mask for USART_TXBDRIGHT
#define USART_STATUS_TXBSRIGHT                (0x1UL << 10)                         // TX Buffer Expects Single Right Data
#define USART_STATUS_TXBSRIGHT_MASK            0x400UL                              // Bit mask for USART_TXBSRIGHT

#define USART_STATUS_RXDATAVRIGHT             (0x1UL << 11)                         // RX Data Right
#define USART_STATUS_RXDATAVRIGHT_MASK         0x800UL                              // Bit mask for USART_RXDATAVRIGHT

#define USART_STATUS_RXFULLRIGHT              (0x1UL << 12)                         // RX Full of Right Data
#define USART_STATUS_RXFULLRIGHT_MASK          0x1000UL                             // Bit mask for USART_RXFULLRIGHT

// Bit fields for USART CLKDIV
#define USART_CLKDIV_MASK                      0x001FFFC0UL                         // Mask for USART_CLKDIV
#define USART_CLKDIV_DIV_MASK                  0x1FFFC0UL                           // Bit mask for USART_DIV

// Bit fields for USART RXDATAX

#define USART_RXDATAX_RXDATA_MASK              0x1FFUL                              // Bit mask for USART_RXDATA

#define USART_RXDATAX_PERR                    (0x1UL << 14)                         // Data Parity Error
#define USART_RXDATAX_PERR_MASK                0x4000UL                             // Bit mask for USART_PERR

#define USART_RXDATAX_FERR                    (0x1UL << 15)                         // Data Framing Error
#define USART_RXDATAX_FERR_MASK                0x8000UL                             // Bit mask for USART_FERR

// Bit fields for USART RXDATA
#define USART_RXDATA_RXDATA_MASK               0xFFUL                               // Bit mask for USART_RXDATA

// Bit fields for USART RXDOUBLEX

#define USART_RXDOUBLEX_RXDATA0_MASK           0x1FFUL                              // Bit mask for USART_RXDATA0
#define USART_RXDOUBLEX_PERR0                 (0x1UL << 14)                         // Data Parity Error 0
#define USART_RXDOUBLEX_PERR0_MASK             0x4000UL                             // Bit mask for USART_PERR0
#define USART_RXDOUBLEX_FERR0                 (0x1UL << 15)                         // Data Framing Error 0
#define USART_RXDOUBLEX_FERR0_MASK             0x8000UL                             // Bit mask for USART_FERR0
#define USART_RXDOUBLEX_RXDATA1_MASK           0x1FF0000UL                          // Bit mask for USART_RXDATA1
#define USART_RXDOUBLEX_PERR1                 (0x1UL << 30)                         // Data Parity Error 1
#define USART_RXDOUBLEX_PERR1_MASK             0x40000000UL                         // Bit mask for USART_PERR1
#define USART_RXDOUBLEX_FERR1                 (0x1UL << 31)                         // Data Framing Error 1
#define USART_RXDOUBLEX_FERR1_MASK             0x80000000UL                         // Bit mask for USART_FERR1

// Bit fields for USART RXDOUBLE
#define USART_RXDOUBLE_RXDATA0_MASK            0xFFUL                               // Bit mask for USART_RXDATA0
#define USART_RXDOUBLE_RXDATA1_MASK            0xFF00UL                             // Bit mask for USART_RXDATA1

// Bit fields for USART RXDATAXP

#define USART_RXDATAXP_RXDATAP_MASK            0x1FFUL                              // Bit mask for USART_RXDATAP
#define USART_RXDATAXP_PERRP                  (0x1UL << 14)                         // Data Parity Error Peek
#define USART_RXDATAXP_PERRP_MASK              0x4000UL                             // Bit mask for USART_PERRP
#define USART_RXDATAXP_FERRP                  (0x1UL << 15)                         // Data Framing Error Peek
#define USART_RXDATAXP_FERRP_MASK              0x8000UL                             // Bit mask for USART_FERRP

// Bit fields for USART RXDOUBLEXP
#define USART_RXDOUBLEXP_RXDATAP0_MASK         0x1FFUL                              // Bit mask for USART_RXDATAP0
#define USART_RXDOUBLEXP_PERRP0               (0x1UL << 14)                         // Data Parity Error 0 Peek
#define USART_RXDOUBLEXP_PERRP0_MASK           0x4000UL                             // Bit mask for USART_PERRP0
#define USART_RXDOUBLEXP_FERRP0               (0x1UL << 15)                         // Data Framing Error 0 Peek
#define USART_RXDOUBLEXP_FERRP0_MASK           0x8000UL                             // Bit mask for USART_FERRP0
#define USART_RXDOUBLEXP_RXDATAP1_MASK         0x1FF0000UL                          // Bit mask for USART_RXDATAP1
#define USART_RXDOUBLEXP_PERRP1               (0x1UL << 30)                         // Data Parity Error 1 Peek
#define USART_RXDOUBLEXP_PERRP1_MASK           0x40000000UL                         // Bit mask for USART_PERRP1
#define USART_RXDOUBLEXP_FERRP1               (0x1UL << 31)                         // Data Framing Error 1 Peek
#define USART_RXDOUBLEXP_FERRP1_MASK           0x80000000UL                         // Bit mask for USART_FERRP1

// Bit fields for USART TXDATAX

#define USART_TXDATAX_TXDATAX_MASK             0x1FFUL                              // Bit mask for USART_TXDATAX

#define USART_TXDATAX_UBRXAT                  (0x1UL << 11)                         // Unblock RX After Transmission
#define USART_TXDATAX_UBRXAT_MASK              0x800UL                              // Bit mask for USART_UBRXAT
#define USART_TXDATAX_TXTRIAT                 (0x1UL << 12)                         // Set TXTRI After Transmission
#define USART_TXDATAX_TXTRIAT_MASK             0x1000UL                             // Bit mask for USART_TXTRIAT
#define USART_TXDATAX_TXBREAK                 (0x1UL << 13)                         // Transmit Data As Break
#define USART_TXDATAX_TXBREAK_MASK             0x2000UL                             // Bit mask for USART_TXBREAK
#define USART_TXDATAX_TXDISAT                 (0x1UL << 14)                         // Clear TXEN After Transmission
#define USART_TXDATAX_TXDISAT_MASK             0x4000UL                             // Bit mask for USART_TXDISAT
#define USART_TXDATAX_RXENAT                  (0x1UL << 15)                         // Enable RX After Transmission
#define USART_TXDATAX_RXENAT_MASK              0x8000UL                             // Bit mask for USART_RXENAT

// Bit fields for USART TXDATA
#define USART_TXDATA_RESETVALUE                0x00000000UL                         // Default value for USART_TXDATA
#define USART_TXDATA_MASK                      0x000000FFUL                         // Mask for USART_TXDATA
#define USART_TXDATA_TXDATA_MASK               0xFFUL                               // Bit mask for USART_TXDATA

// Bit fields for USART TXDOUBLEX

#define USART_TXDOUBLEX_TXDATA0_MASK           0x1FFUL                              // Bit mask for USART_TXDATA0

#define USART_TXDOUBLEX_UBRXAT0               (0x1UL << 11)                         // Unblock RX After Transmission
#define USART_TXDOUBLEX_UBRXAT0_MASK           0x800UL                              // Bit mask for USART_UBRXAT0

#define USART_TXDOUBLEX_TXTRIAT0              (0x1UL << 12)                         // Set TXTRI After Transmission
#define USART_TXDOUBLEX_TXTRIAT0_MASK          0x1000UL                             // Bit mask for USART_TXTRIAT0

#define USART_TXDOUBLEX_TXBREAK0              (0x1UL << 13)                         // Transmit Data As Break
#define USART_TXDOUBLEX_TXBREAK0_MASK          0x2000UL                             // Bit mask for USART_TXBREAK0

#define USART_TXDOUBLEX_TXDISAT0              (0x1UL << 14)                         // Clear TXEN After Transmission
#define USART_TXDOUBLEX_TXDISAT0_MASK          0x4000UL                             // Bit mask for USART_TXDISAT0

#define USART_TXDOUBLEX_RXENAT0               (0x1UL << 15)                         // Enable RX After Transmission
#define USART_TXDOUBLEX_RXENAT0_MASK           0x8000UL                             // Bit mask for USART_RXENAT0

#define USART_TXDOUBLEX_TXDATA1_MASK           0x1FF0000UL                          // Bit mask for USART_TXDATA1

#define USART_TXDOUBLEX_UBRXAT1               (0x1UL << 27)                         // Unblock RX After Transmission
#define USART_TXDOUBLEX_UBRXAT1_MASK           0x8000000UL                          // Bit mask for USART_UBRXAT1

#define USART_TXDOUBLEX_TXTRIAT1              (0x1UL << 28)                         // Set TXTRI After Transmission
#define USART_TXDOUBLEX_TXTRIAT1_MASK          0x10000000UL                         // Bit mask for USART_TXTRIAT1

#define USART_TXDOUBLEX_TXBREAK1              (0x1UL << 29)                         // Transmit Data As Break
#define USART_TXDOUBLEX_TXBREAK1_MASK          0x20000000UL                         // Bit mask for USART_TXBREAK1

#define USART_TXDOUBLEX_TXDISAT1              (0x1UL << 30)                         // Clear TXEN After Transmission
#define USART_TXDOUBLEX_TXDISAT1_MASK          0x40000000UL                         // Bit mask for USART_TXDISAT1

#define USART_TXDOUBLEX_RXENAT1               (0x1UL << 31)                         // Enable RX After Transmission
#define USART_TXDOUBLEX_RXENAT1_MASK           0x80000000UL                         // Bit mask for USART_RXENAT1

// Bit fields for USART TXDOUBLE

#define USART_TXDOUBLE_TXDATA0_MASK            0xFFUL                               // Bit mask for USART_TXDATA0
#define USART_TXDOUBLE_TXDATA1_MASK            0xFF00UL                             // Bit mask for USART_TXDATA1

// Bit fields for USART IF

#define USART_IF_TXC                          (0x1UL << 0)                          // TX Complete Interrupt Flag
#define USART_IF_TXC_MASK                      0x1UL                                // Bit mask for USART_TXC

#define USART_IF_TXBL                         (0x1UL << 1)                          // TX Buffer Level Interrupt Flag
#define USART_IF_TXBL_MASK                     0x2UL                                // Bit mask for USART_TXBL

#define USART_IF_RXDATAV                      (0x1UL << 2)                          // RX Data Valid Interrupt Flag

#define USART_IF_RXDATAV_MASK                  0x4UL                                // Bit mask for USART_RXDATAV

#define USART_IF_RXFULL                       (0x1UL << 3)                          // RX Buffer Full Interrupt Flag
#define USART_IF_RXFULL_MASK                   0x8UL                                // Bit mask for USART_RXFULL

#define USART_IF_RXOF                         (0x1UL << 4)                          // RX Overflow Interrupt Flag
#define USART_IF_RXOF_MASK                     0x10UL                               // Bit mask for USART_RXOF

#define USART_IF_RXUF                         (0x1UL << 5)                          // RX Underflow Interrupt Flag
#define USART_IF_RXUF_MASK                     0x20UL                               // Bit mask for USART_RXUF

#define USART_IF_TXOF                         (0x1UL << 6)                          // TX Overflow Interrupt Flag
#define USART_IF_TXOF_MASK                     0x40UL                               // Bit mask for USART_TXOF

#define USART_IF_TXUF                         (0x1UL << 7)                          // TX Underflow Interrupt Flag
#define USART_IF_TXUF_MASK                     0x80UL                               // Bit mask for USART_TXUF

#define USART_IF_PERR                         (0x1UL << 8)                          // Parity Error Interrupt Flag
#define USART_IF_PERR_MASK                     0x100UL                              // Bit mask for USART_PERR

#define USART_IF_FERR                         (0x1UL << 9)                          // Framing Error Interrupt Flag
#define USART_IF_FERR_MASK                     0x200UL                              // Bit mask for USART_FERR

#define USART_IF_MPAF                         (0x1UL << 10)                         // Multi-Processor Address Frame Interrupt Flag
#define USART_IF_MPAF_MASK                     0x400UL                              // Bit mask for USART_MPAF

#define USART_IF_SSM                          (0x1UL << 11)                         // Slave-Select In Master Mode Interrupt Flag
#define USART_IF_SSM_MASK                      0x800UL                              // Bit mask for USART_SSM

#define USART_IF_CCF                          (0x1UL << 12)                         // Collision Check Fail Interrupt Flag
#define USART_IF_CCF_MASK                      0x1000UL                             // Bit mask for USART_CCF

// Bit fields for USART IFS

#define USART_IFS_TXC                         (0x1UL << 0)                          // Set TX Complete Interrupt Flag
#define USART_IFS_TXC_MASK                     0x1UL                                // Bit mask for USART_TXC

#define USART_IFS_RXFULL                      (0x1UL << 3)                          // Set RX Buffer Full Interrupt Flag
#define USART_IFS_RXFULL_MASK                  0x8UL                                // Bit mask for USART_RXFULL

#define USART_IFS_RXOF                        (0x1UL << 4)                          // Set RX Overflow Interrupt Flag
#define USART_IFS_RXOF_MASK                    0x10UL                               // Bit mask for USART_RXOF

#define USART_IFS_RXUF                        (0x1UL << 5)                          // Set RX Underflow Interrupt Flag
#define USART_IFS_RXUF_MASK                    0x20UL                               // Bit mask for USART_RXUF

#define USART_IFS_TXOF                        (0x1UL << 6)                          // Set TX Overflow Interrupt Flag
#define USART_IFS_TXOF_MASK                    0x40UL                               // Bit mask for USART_TXOF

#define USART_IFS_TXUF                        (0x1UL << 7)                          // Set TX Underflow Interrupt Flag
#define USART_IFS_TXUF_MASK                    0x80UL                               // Bit mask for USART_TXUF

#define USART_IFS_PERR                        (0x1UL << 8)                          // Set Parity Error Interrupt Flag
#define USART_IFS_PERR_MASK                    0x100UL                              // Bit mask for USART_PERR

#define USART_IFS_FERR                        (0x1UL << 9)                          // Set Framing Error Interrupt Flag
#define USART_IFS_FERR_MASK                    0x200UL                              // Bit mask for USART_FERR

#define USART_IFS_MPAF                        (0x1UL << 10)                         // Set Multi-Processor Address Frame Interrupt Flag
#define USART_IFS_MPAF_MASK                    0x400UL                              // Bit mask for USART_MPAF

#define USART_IFS_SSM                         (0x1UL << 11)                         // Set Slave-Select in Master mode Interrupt Flag
#define USART_IFS_SSM_MASK                     0x800UL                              // Bit mask for USART_SSM

#define USART_IFS_CCF                         (0x1UL << 12)                         // Set Collision Check Fail Interrupt Flag
#define USART_IFS_CCF_MASK                     0x1000UL                             // Bit mask for USART_CCF

// Bit fields for USART IFC

#define USART_IFC_TXC                         (0x1UL << 0)                          // Clear TX Complete Interrupt Flag
#define USART_IFC_TXC_MASK                     0x1UL                                // Bit mask for USART_TXC

#define USART_IFC_RXFULL                      (0x1UL << 3)                          // Clear RX Buffer Full Interrupt Flag
#define USART_IFC_RXFULL_MASK                  0x8UL                                // Bit mask for USART_RXFULL

#define USART_IFC_RXOF                        (0x1UL << 4)                          // Clear RX Overflow Interrupt Flag
#define USART_IFC_RXOF_MASK                    0x10UL                               // Bit mask for USART_RXOF

#define USART_IFC_RXUF                        (0x1UL << 5)                          // Clear RX Underflow Interrupt Flag
#define USART_IFC_RXUF_MASK                    0x20UL                               // Bit mask for USART_RXUF

#define USART_IFC_TXOF                        (0x1UL << 6)                          // Clear TX Overflow Interrupt Flag
#define USART_IFC_TXOF_MASK                    0x40UL                               // Bit mask for USART_TXOF

#define USART_IFC_TXUF                        (0x1UL << 7)                          // Clear TX Underflow Interrupt Flag
#define USART_IFC_TXUF_MASK                    0x80UL                               // Bit mask for USART_TXUF

#define USART_IFC_PERR                        (0x1UL << 8)                          // Clear Parity Error Interrupt Flag
#define USART_IFC_PERR_MASK                    0x100UL                              // Bit mask for USART_PERR

#define USART_IFC_FERR                        (0x1UL << 9)                          // Clear Framing Error Interrupt Flag
#define USART_IFC_FERR_MASK                    0x200UL                              // Bit mask for USART_FERR

#define USART_IFC_MPAF                        (0x1UL << 10)                         // Clear Multi-Processor Address Frame Interrupt Flag
#define USART_IFC_MPAF_MASK                    0x400UL                              // Bit mask for USART_MPAF

#define USART_IFC_SSM                         (0x1UL << 11)                         // Clear Slave-Select In Master Mode Interrupt Flag
#define USART_IFC_SSM_MASK                     0x800UL                              // Bit mask for USART_SSM

#define USART_IFC_CCF                         (0x1UL << 12)                         // Clear Collision Check Fail Interrupt Flag
#define USART_IFC_CCF_MASK                     0x1000UL                             // Bit mask for USART_CCF

// Bit fields for USART IEN

#define USART_IEN_TXC                         (0x1UL << 0)                          // TX Complete Interrupt Enable
#define USART_IEN_TXC_MASK                     0x1UL                                // Bit mask for USART_TXC

#define USART_IEN_TXBL                        (0x1UL << 1)                          // TX Buffer Level Interrupt Enable
#define USART_IEN_TXBL_MASK                    0x2UL                                // Bit mask for USART_TXBL

#define USART_IEN_RXDATAV                     (0x1UL << 2)                          // RX Data Valid Interrupt Enable
#define USART_IEN_RXDATAV_MASK                 0x4UL                                // Bit mask for USART_RXDATAV

#define USART_IEN_RXFULL                      (0x1UL << 3)                          // RX Buffer Full Interrupt Enable
#define USART_IEN_RXFULL_MASK                  0x8UL                                // Bit mask for USART_RXFULL

#define USART_IEN_RXOF                        (0x1UL << 4)                          // RX Overflow Interrupt Enable
#define USART_IEN_RXOF_MASK                    0x10UL                               // Bit mask for USART_RXOF

#define USART_IEN_RXUF                        (0x1UL << 5)                          // RX Underflow Interrupt Enable
#define USART_IEN_RXUF_MASK                    0x20UL                               // Bit mask for USART_RXUF

#define USART_IEN_TXOF                        (0x1UL << 6)                          // TX Overflow Interrupt Enable
#define USART_IEN_TXOF_MASK                    0x40UL                               // Bit mask for USART_TXOF

#define USART_IEN_TXUF                        (0x1UL << 7)                          // TX Underflow Interrupt Enable
#define USART_IEN_TXUF_MASK                    0x80UL                               // Bit mask for USART_TXUF

#define USART_IEN_PERR                        (0x1UL << 8)                          // Parity Error Interrupt Enable
#define USART_IEN_PERR_MASK                    0x100UL                              // Bit mask for USART_PERR

#define USART_IEN_FERR                        (0x1UL << 9)                          // Framing Error Interrupt Enable
#define USART_IEN_FERR_MASK                    0x200UL                              // Bit mask for USART_FERR

#define USART_IEN_MPAF                        (0x1UL << 10)                         // Multi-Processor Address Frame Interrupt Enable
#define USART_IEN_MPAF_MASK                    0x400UL                              // Bit mask for USART_MPAF

#define USART_IEN_SSM                         (0x1UL << 11)                         // Slave-Select In Master Mode Interrupt Enable
#define USART_IEN_SSM_MASK                     0x800UL                              // Bit mask for USART_SSM

#define USART_IEN_CCF                         (0x1UL << 12)                         // Collision Check Fail Interrupt Enable
#define USART_IEN_CCF_MASK                     0x1000UL                             // Bit mask for USART_CCF

// Bit fields for USART IRCTRL
#define USART_IRCTRL_IREN                     (0x1UL << 0)                          // Enable IrDA Module
#define _USART_IRCTRL_IREN_MASK                0x1UL                                // Bit mask for USART_IREN

#define USART_IRCTRL_IRPW_MASK                 0x6UL                                // Bit mask for USART_IRPW
#define USART_IRCTRL_IRPW_ONE                 (0x00000000UL << 1)                   // Shifted mode ONE for USART_IRCTRL
#define USART_IRCTRL_IRPW_TWO                 (0x00000001UL << 1)                   // Shifted mode TWO for USART_IRCTRL
#define USART_IRCTRL_IRPW_THREE               (0x00000002UL << 1)                   // Shifted mode THREE for USART_IRCTRL
#define USART_IRCTRL_IRPW_FOUR                (0x00000003UL << 1)                   // Shifted mode FOUR for USART_IRCTRL

#define USART_IRCTRL_IRFILT                   (0x1UL << 3)                          // IrDA RX Filter
#define _USART_IRCTRL_IRFILT_MASK              0x8UL                                // Bit mask for USART_IRFILT

#define USART_IRCTRL_IRPRSSEL_MASK             0x70UL                               // Bit mask for USART_IRPRSSEL
#define USART_IRCTRL_IRPRSSEL_PRSCH0          (0x00000000UL << 4)                   // Shifted mode PRSCH0 for USART_IRCTRL
#define USART_IRCTRL_IRPRSSEL_PRSCH1          (0x00000001UL << 4)                   // Shifted mode PRSCH1 for USART_IRCTRL
#define USART_IRCTRL_IRPRSSEL_PRSCH2          (0x00000002UL << 4)                   // Shifted mode PRSCH2 for USART_IRCTRL
#define USART_IRCTRL_IRPRSSEL_PRSCH3          (0x00000003UL << 4)                   // Shifted mode PRSCH3 for USART_IRCTRL
#define USART_IRCTRL_IRPRSSEL_PRSCH4          (0x00000004UL << 4)                   // Shifted mode PRSCH4 for USART_IRCTRL
#define USART_IRCTRL_IRPRSSEL_PRSCH5          (0x00000005UL << 4)                   // Shifted mode PRSCH5 for USART_IRCTRL
#define USART_IRCTRL_IRPRSSEL_PRSCH6          (0x00000006UL << 4)                   // Shifted mode PRSCH6 for USART_IRCTRL
#define USART_IRCTRL_IRPRSSEL_PRSCH7          (0x00000007UL << 4)                   // Shifted mode PRSCH7 for USART_IRCTRL

#define USART_IRCTRL_IRPRSEN                  (0x1UL << 7)                          // IrDA PRS Channel Enable
#define USART_IRCTRL_IRPRSEN_MASK              0x80UL                               // Bit mask for USART_IRPRSEN

// Bit fields for USART ROUTE
#define USART_ROUTE_RXPEN                     (0x1UL << 0)                          // RX Pin Enable
#define USART_ROUTE_RXPEN_MASK                 0x1UL                                // Bit mask for USART_RXPEN

#define USART_ROUTE_TXPEN                     (0x1UL << 1)                          // TX Pin Enable
#define USART_ROUTE_TXPEN_MASK                 0x2UL                                // Bit mask for USART_TXPEN

#define USART_ROUTE_CSPEN                     (0x1UL << 2)                          // CS Pin Enable
#define USART_ROUTE_CSPEN_MASK                 0x4UL                                // Bit mask for USART_CSPEN

#define USART_ROUTE_CLKPEN                    (0x1UL << 3)                          // CLK Pin Enable
#define USART_ROUTE_CLKPEN_MASK                0x8UL                                // Bit mask for USART_CLKPEN

#define USART_ROUTE_LOCATION_MASK              0x700UL                              // Bit mask for USART_LOCATION
#define USART_ROUTE_LOCATION_LOC0             (0x00000000UL << 8)                   // Shifted mode LOC0 for USART_ROUTE
#define USART_ROUTE_LOCATION_LOC1             (0x00000001UL << 8)                   // Shifted mode LOC1 for USART_ROUTE
#define USART_ROUTE_LOCATION_LOC2             (0x00000002UL << 8)                   // Shifted mode LOC2 for USART_ROUTE
#define USART_ROUTE_LOCATION_LOC3             (0x00000003UL << 8)                   // Shifted mode LOC3 for USART_ROUTE
#define USART_ROUTE_LOCATION_LOC4             (0x00000004UL << 8)                   // Shifted mode LOC4 for USART_ROUTE
#define USART_ROUTE_LOCATION_LOC5             (0x00000005UL << 8)                   // Shifted mode LOC5 for USART_ROUTE

// Bit fields for USART INPUT
#define USART_INPUT_RXPRSSEL_MASK              0xFUL                                 // Bit mask for USART_RXPRSSEL
#define USART_INPUT_RXPRSSEL_PRSCH0           (0x00000000UL << 0)                    // Shifted mode PRSCH0 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH1           (0x00000001UL << 0)                    // Shifted mode PRSCH1 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH2           (0x00000002UL << 0)                    // Shifted mode PRSCH2 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH3           (0x00000003UL << 0)                    // Shifted mode PRSCH3 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH4           (0x00000004UL << 0)                    // Shifted mode PRSCH4 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH5           (0x00000005UL << 0)                    // Shifted mode PRSCH5 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH6           (0x00000006UL << 0)                    // Shifted mode PRSCH6 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH7           (0x00000007UL << 0)                    // Shifted mode PRSCH7 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH8           (0x00000008UL << 0)                    // Shifted mode PRSCH8 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH9           (0x00000009UL << 0)                    // Shifted mode PRSCH9 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH10          (0x0000000AUL << 0)                    // Shifted mode PRSCH10 for USART_INPUT
#define USART_INPUT_RXPRSSEL_PRSCH11          (0x00000009UL << 0)                    // Shifted mode PRSCH11 for USART_INPUT

#define USART_INPUT_RXPRS                     (0x1UL << 4)                           // PRS RX Enable
#define USART_INPUT_RXPRS_MASK                 0x10UL                                // Bit mask for USART_RXPRS

// Bit fields for USART I2SCTRL
#define _USART_I2SCTRL_RESETVALUE              0x00000000UL                          // Default value for USART_I2SCTRL
#define USART_I2SCTRL_MASK                     0x0000071FUL                          // Mask for USART_I2SCTRL

#define USART_I2SCTRL_EN                      (0x1UL << 0)                           // Enable I2S Mode
#define USART_I2SCTRL_EN_MASK                  0x1UL                                 // Bit mask for USART_EN

#define USART_I2SCTRL_MONO                    (0x1UL << 1)                           // Stero or Mono
#define USART_I2SCTRL_MONO_MASK                0x2UL                                 // Bit mask for USART_MONO

#define USART_I2SCTRL_JUSTIFY                 (0x1UL << 2)                           // Justification of I2S Data
#define USART_I2SCTRL_JUSTIFY_MASK             0x4UL                                 // Bit mask for USART_JUSTIFY
#define USART_I2SCTRL_JUSTIFY_LEFT            (0x00000000UL << 2)                    // Shifted mode LEFT for USART_I2SCTRL
#define USART_I2SCTRL_JUSTIFY_RIGHT           (0x00000001UL << 2)                    // Shifted mode RIGHT for USART_I2SCTRL

#define USART_I2SCTRL_DMASPLIT                (0x1UL << 3)                           // Separate DMA Request For Left/Right Data
#define USART_I2SCTRL_DMASPLIT_MASK            0x8UL                                 // Bit mask for USART_DMASPLIT
#define USART_I2SCTRL_DMASPLIT_DEFAULT        (_USART_I2SCTRL_DMASPLIT_DEFAULT << 3) // Shifted mode DEFAULT for USART_I2SCTRL

#define USART_I2SCTRL_DELAY                   (0x1UL << 4)                           // Delay on I2S data
#define USART_I2SCTRL_DELAY_MASK               0x10UL                                // Bit mask for USART_DELAY
#define USART_I2SCTRL_DELAY_DEFAULT           (_USART_I2SCTRL_DELAY_DEFAULT << 4)    // Shifted mode DEFAULT for USART_I2SCTRL

#define USART_I2SCTRL_FORMAT_MASK              0x700UL                               // Bit mask for USART_FORMAT
#define USART_I2SCTRL_FORMAT_DEFAULT          (_USART_I2SCTRL_FORMAT_DEFAULT << 8)   // Shifted mode DEFAULT for USART_I2SCTRL
#define USART_I2SCTRL_FORMAT_W32D32           (_USART_I2SCTRL_FORMAT_W32D32 << 8)    // Shifted mode W32D32 for USART_I2SCTRL
#define USART_I2SCTRL_FORMAT_W32D24M          (_USART_I2SCTRL_FORMAT_W32D24M << 8)   // Shifted mode W32D24M for USART_I2SCTRL
#define USART_I2SCTRL_FORMAT_W32D24           (_USART_I2SCTRL_FORMAT_W32D24 << 8)    // Shifted mode W32D24 for USART_I2SCTRL
#define USART_I2SCTRL_FORMAT_W32D16           (_USART_I2SCTRL_FORMAT_W32D16 << 8)    // Shifted mode W32D16 for USART_I2SCTRL
#define USART_I2SCTRL_FORMAT_W32D8            (_USART_I2SCTRL_FORMAT_W32D8 << 8)     // Shifted mode W32D8 for USART_I2SCTRL
#define USART_I2SCTRL_FORMAT_W16D16           (_USART_I2SCTRL_FORMAT_W16D16 << 8)    // Shifted mode W16D16 for USART_I2SCTRL
#define USART_I2SCTRL_FORMAT_W16D8            (_USART_I2SCTRL_FORMAT_W16D8 << 8)     // Shifted mode W16D8 for USART_I2SCTRL
#define USART_I2SCTRL_FORMAT_W8D8             (_USART_I2SCTRL_FORMAT_W8D8 << 8)      // Shifted mode W8D8 for USART_I2SCTRL


