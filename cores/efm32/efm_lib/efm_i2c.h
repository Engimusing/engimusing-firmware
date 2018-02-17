///
///@file efm_i2c.h
///@brief Defines used for accessing the I2C peripheral 
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

#include "io_types.h"
#include "cmsis.h"

typedef struct
{
  __IO uint32_t CTRL;      // Control Register
  __IO uint32_t CMD;       // Command Register
  __I uint32_t  STATE;     // State Register
  __I uint32_t  STATUS;    // Status Register
  __IO uint32_t CLKDIV;    // Clock Division Register
  __IO uint32_t SADDR;     // Slave Address Register
  __IO uint32_t SADDRMASK; // Slave Address Mask Register
  __I uint32_t  RXDATA;    // Receive Buffer Data Register
  __I uint32_t  RXDATAP;   // Receive Buffer Data Peek Register
  __IO uint32_t TXDATA;    // Transmit Buffer Data Register
  __I uint32_t  IF;        // Interrupt Flag Register
  __IO uint32_t IFS;       // Interrupt Flag Set Register
  __IO uint32_t IFC;       // Interrupt Flag Clear Register
  __IO uint32_t IEN;       // Interrupt Enable Register
  __IO uint32_t ROUTE;     // I/O Routing Register
} I2C_TypeDef;

#define I2C0         ((I2C_TypeDef *) 0x4000A000UL)             // I2C0 base pointer
#define I2C1         ((I2C_TypeDef *) 0x4000A400UL)             // I2C1 base pointer


// Bit fields for I2C CTRL
#define I2C_CTRL_EN                       (0x1UL << 0)          // I2C Enable
#define I2C_CTRL_EN_MASK                   0x1UL                // Bit mask for I2C_EN
#define I2C_CTRL_SLAVE                    (0x1UL << 1)          // Addressable as Slave
#define I2C_CTRL_SLAVE_MASK                0x2UL                // Bit mask for I2C_SLAVE
#define I2C_CTRL_AUTOACK                  (0x1UL << 2)          // Automatic Acknowledge
#define I2C_CTRL_AUTOACK_MASK              0x4UL                // Bit mask for I2C_AUTOACK
#define I2C_CTRL_AUTOSE                   (0x1UL << 3)          // Automatic STOP when Empty
#define I2C_CTRL_AUTOSE_MASK               0x8UL                // Bit mask for I2C_AUTOSE
#define I2C_CTRL_AUTOSN                   (0x1UL << 4)          // Automatic STOP on NACK
#define I2C_CTRL_AUTOSN_MASK               0x10UL               // Bit mask for I2C_AUTOSN
#define I2C_CTRL_ARBDIS                   (0x1UL << 5)          // Arbitration Disable
#define I2C_CTRL_ARBDIS_MASK               0x20UL               // Bit mask for I2C_ARBDIS
#define I2C_CTRL_GCAMEN                   (0x1UL << 6)          // General Call Address Match Enable
#define I2C_CTRL_GCAMEN_MASK               0x40UL               // Bit mask for I2C_GCAMEN

#define I2C_CTRL_CLHR_MASK                 0x300UL              // Bit mask for I2C_CLHR
#define I2C_CTRL_CLHR_STANDARD            (0x00000000UL << 8)   // Shifted mode STANDARD for I2C_CTRL
#define I2C_CTRL_CLHR_ASYMMETRIC          (0x00000001UL << 8)   // Shifted mode ASYMMETRIC for I2C_CTRL
#define I2C_CTRL_CLHR_FAST                (0x00000002UL << 8)   // Shifted mode FAST for I2C_CTRL

#define I2C_CTRL_BITO_MASK                 0x3000UL             // Bit mask for I2C_BITO
#define I2C_CTRL_BITO_OFF                 (0x00000000UL << 12)  // Shifted mode OFF for I2C_CTRL
#define I2C_CTRL_BITO_40PCC               (0x00000001UL << 12)  // Shifted mode 40PCC for I2C_CTRL
#define I2C_CTRL_BITO_80PCC               (0x00000002UL << 12)  // Shifted mode 80PCC for I2C_CTRL
#define I2C_CTRL_BITO_160PCC              (0x00000003UL << 12)  // Shifted mode 160PCC for I2C_CTRL

#define I2C_CTRL_GIBITO                   (0x1UL << 15)         // Go Idle on Bus Idle Timeout
#define I2C_CTRL_GIBITO_MASK               0x8000UL             // Bit mask for I2C_GIBITO

#define I2C_CTRL_CLTO_MASK                 0x70000UL            // Bit mask for I2C_CLTO
#define I2C_CTRL_CLTO_OFF                 (0x00000000UL << 16)  // Shifted mode OFF for I2C_CTRL
#define I2C_CTRL_CLTO_40PCC               (0x00000001UL << 16)  // Shifted mode 40PCC for I2C_CTRL
#define I2C_CTRL_CLTO_80PCC               (0x00000002UL << 16)  // Shifted mode 80PCC for I2C_CTRL
#define I2C_CTRL_CLTO_160PCC              (0x00000003UL << 16)  // Shifted mode 160PCC for I2C_CTRL
#define I2C_CTRL_CLTO_320PPC              (0x00000004UL << 16)  // Shifted mode 320PPC for I2C_CTRL
#define I2C_CTRL_CLTO_1024PPC             (0x00000005UL << 16)  // Shifted mode 1024PPC for I2C_CTRL

// Bit fields for I2C CMD
#define I2C_CMD_START                     (0x1UL << 0)          // Send start condition
#define I2C_CMD_START_MASK                 0x1UL                // Bit mask for I2C_START
#define I2C_CMD_STOP                      (0x1UL << 1)          // Send stop condition
#define I2C_CMD_STOP_MASK                  0x2UL                // Bit mask for I2C_STOP
#define I2C_CMD_ACK                       (0x1UL << 2)          // Send ACK
#define I2C_CMD_ACK_MASK                   0x4UL                // Bit mask for I2C_ACK
#define I2C_CMD_NACK                      (0x1UL << 3)          // Send NACK
#define I2C_CMD_NACK_MASK                  0x8UL                // Bit mask for I2C_NACK
#define I2C_CMD_CONT                      (0x1UL << 4)          // Continue transmission
#define I2C_CMD_CONT_MASK                  0x10UL               // Bit mask for I2C_CONT
#define I2C_CMD_ABORT                     (0x1UL << 5)          // Abort transmission
#define I2C_CMD_ABORT_MASK                 0x20UL               // Bit mask for I2C_ABORT
#define I2C_CMD_CLEARTX                   (0x1UL << 6)          // Clear TX
#define I2C_CMD_CLEARTX_MASK               0x40UL               // Bit mask for I2C_CLEARTX
#define I2C_CMD_CLEARPC                   (0x1UL << 7)          // Clear Pending Commands
#define I2C_CMD_CLEARPC_MASK               0x80UL               // Bit mask for I2C_CLEARPC

// Bit fields for I2C STATE
#define I2C_STATE_BUSY                    (0x1UL << 0)          // Bus Busy
#define I2C_STATE_BUSY_MASK                0x1UL                // Bit mask for I2C_BUSY
#define I2C_STATE_MASTER                  (0x1UL << 1)          // Master
#define I2C_STATE_MASTER_MASK              0x2UL                // Bit mask for I2C_MASTER
#define I2C_STATE_TRANSMITTER             (0x1UL << 2)          // Transmitter
#define I2C_STATE_TRANSMITTER_MASK         0x4UL                // Bit mask for I2C_TRANSMITTER
#define I2C_STATE_NACKED                  (0x1UL << 3)          // Nack Received
#define I2C_STATE_NACKED_MASK              0x8UL                // Bit mask for I2C_NACKED
#define I2C_STATE_BUSHOLD                 (0x1UL << 4)          // Bus Held
#define I2C_STATE_BUSHOLD_MASK             0x10UL               // Bit mask for I2C_BUSHOLD

#define I2C_STATE_STATE_MASK               0xE0UL               // Bit mask for I2C_STATE
#define I2C_STATE_STATE_IDLE              (0x00000000UL << 5)   // Shifted mode IDLE for I2C_STATE
#define I2C_STATE_STATE_WAIT              (0x00000001UL << 5)   // Shifted mode WAIT for I2C_STATE
#define I2C_STATE_STATE_START             (0x00000002UL << 5)   // Shifted mode START for I2C_STATE
#define I2C_STATE_STATE_ADDR              (0x00000003UL << 5)   // Shifted mode ADDR for I2C_STATE
#define I2C_STATE_STATE_ADDRACK           (0x00000004UL << 5)   // Shifted mode ADDRACK for I2C_STATE
#define I2C_STATE_STATE_DATA              (0x00000005UL << 5)   // Shifted mode DATA for I2C_STATE
#define I2C_STATE_STATE_DATAACK           (0x00000006UL << 5)   // Shifted mode DATAACK for I2C_STATE

// Bit fields for I2C STATUS
#define I2C_STATUS_PSTART                 (0x1UL << 0)          // Pending START
#define I2C_STATUS_PSTART_MASK             0x1UL                // Bit mask for I2C_PSTART
#define I2C_STATUS_PSTOP                  (0x1UL << 1)          // Pending STOP
#define I2C_STATUS_PSTOP_MASK              0x2UL                // Bit mask for I2C_PSTOP
#define I2C_STATUS_PACK                   (0x1UL << 2)          // Pending ACK
#define I2C_STATUS_PACK_MASK               0x4UL                // Bit mask for I2C_PACK
#define I2C_STATUS_PNACK                  (0x1UL << 3)          // Pending NACK
#define I2C_STATUS_PNACK_MASK              0x8UL                // Bit mask for I2C_PNACK
#define I2C_STATUS_PCONT                  (0x1UL << 4)          // Pending continue
#define I2C_STATUS_PCONT_MASK              0x10UL               // Bit mask for I2C_PCONT
#define I2C_STATUS_PABORT                 (0x1UL << 5)          // Pending abort
#define I2C_STATUS_PABORT_MASK             0x20UL               // Bit mask for I2C_PABORT
#define I2C_STATUS_TXC                    (0x1UL << 6)          // TX Complete
#define I2C_STATUS_TXC_MASK                0x40UL               // Bit mask for I2C_TXC
#define I2C_STATUS_TXBL                   (0x1UL << 7)          // TX Buffer Level
#define I2C_STATUS_TXBL_MASK               0x80UL               // Bit mask for I2C_TXBL
#define I2C_STATUS_RXDATAV                (0x1UL << 8)          // RX Data Valid
#define I2C_STATUS_RXDATAV_MASK            0x100UL              // Bit mask for I2C_RXDATAV

// Bit fields for I2C CLKDIV
#define I2C_CLKDIV_DIV_MASK                0x1FFUL              // Bit mask for I2C_DIV

// Bit fields for I2C SADDR
#define I2C_SADDR_ADDR_MASK                0xFEUL               // Bit mask for I2C_ADDR

// Bit fields for I2C SADDRMASK
#define I2C_SADDRMASK_MASK_MASK            0xFEUL               // Bit mask for I2C_MASK

// Bit fields for I2C RXDATA
#define I2C_RXDATA_RXDATA_MASK             0xFFUL               // Bit mask for I2C_RXDATA

// Bit fields for I2C RXDATAP
#define I2C_RXDATAP_RXDATAP_MASK           0xFFUL               // Bit mask for I2C_RXDATAP

// Bit fields for I2C TXDATA
#define I2C_TXDATA_TXDATA_MASK             0xFFUL               // Bit mask for I2C_TXDATA

// Bit fields for I2C IF
#define I2C_IF_START                      (0x1UL << 0)          // START condition Interrupt Flag
#define I2C_IF_START_MASK                  0x1UL                // Bit mask for I2C_START
#define I2C_IF_RSTART                     (0x1UL << 1)          // Repeated START condition Interrupt Flag
#define I2C_IF_RSTART_MASK                 0x2UL                // Bit mask for I2C_RSTART
#define I2C_IF_ADDR                       (0x1UL << 2)          // Address Interrupt Flag
#define I2C_IF_ADDR_MASK                   0x4UL                // Bit mask for I2C_ADDR
#define I2C_IF_TXC                        (0x1UL << 3)          // Transfer Completed Interrupt Flag
#define I2C_IF_TXC_MASK                    0x8UL                // Bit mask for I2C_TXC
#define I2C_IF_TXBL                       (0x1UL << 4)          // Transmit Buffer Level Interrupt Flag
#define I2C_IF_TXBL_MASK                   0x10UL               // Bit mask for I2C_TXBL
#define I2C_IF_RXDATAV                    (0x1UL << 5)          // Receive Data Valid Interrupt Flag
#define I2C_IF_RXDATAV_MASK                0x20UL               // Bit mask for I2C_RXDATAV
#define I2C_IF_ACK                        (0x1UL << 6)          // Acknowledge Received Interrupt Flag
#define I2C_IF_ACK_MASK                    0x40UL               // Bit mask for I2C_ACK
#define I2C_IF_NACK                       (0x1UL << 7)          // Not Acknowledge Received Interrupt Flag
#define I2C_IF_NACK_MASK                   0x80UL               // Bit mask for I2C_NACK
#define I2C_IF_MSTOP                      (0x1UL << 8)          // Master STOP Condition Interrupt Flag
#define I2C_IF_MSTOP_MASK                  0x100UL              // Bit mask for I2C_MSTOP
#define I2C_IF_ARBLOST                    (0x1UL << 9)          // Arbitration Lost Interrupt Flag
#define I2C_IF_ARBLOST_MASK                0x200UL              // Bit mask for I2C_ARBLOST
#define I2C_IF_BUSERR                     (0x1UL << 10)         // Bus Error Interrupt Flag
#define I2C_IF_BUSERR_MASK                 0x400UL              // Bit mask for I2C_BUSERR
#define I2C_IF_BUSHOLD                    (0x1UL << 11)         // Bus Held Interrupt Flag
#define I2C_IF_BUSHOLD_MASK                0x800UL              // Bit mask for I2C_BUSHOLD
#define I2C_IF_TXOF                       (0x1UL << 12)         // Transmit Buffer Overflow Interrupt Flag
#define I2C_IF_TXOF_MASK                   0x1000UL             // Bit mask for I2C_TXOF
#define I2C_IF_RXUF                       (0x1UL << 13)         // Receive Buffer Underflow Interrupt Flag
#define I2C_IF_RXUF_MASK                   0x2000UL             // Bit mask for I2C_RXUF
#define I2C_IF_BITO                       (0x1UL << 14)         // Bus Idle Timeout Interrupt Flag
#define I2C_IF_BITO_MASK                   0x4000UL             // Bit mask for I2C_BITO
#define I2C_IF_CLTO                       (0x1UL << 15)         // Clock Low Timeout Interrupt Flag
#define I2C_IF_CLTO_MASK                   0x8000UL             // Bit mask for I2C_CLTO
#define I2C_IF_SSTOP                      (0x1UL << 16)         // Slave STOP condition Interrupt Flag
#define I2C_IF_SSTOP_MASK                  0x10000UL            // Bit mask for I2C_SSTOP

// Bit fields for I2C IFS
#define I2C_IFS_START                     (0x1UL << 0)           // Set START Interrupt Flag
#define I2C_IFS_START_MASK                 0x1UL                 // Bit mask for I2C_START
#define I2C_IFS_RSTART                    (0x1UL << 1)           // Set Repeated START Interrupt Flag
#define I2C_IFS_RSTART_MASK                0x2UL                 // Bit mask for I2C_RSTART
#define I2C_IFS_ADDR                      (0x1UL << 2)           // Set Address Interrupt Flag
#define I2C_IFS_ADDR_MASK                  0x4UL                 // Bit mask for I2C_ADDR
#define I2C_IFS_TXC                       (0x1UL << 3)           // Set Transfer Completed Interrupt Flag
#define I2C_IFS_TXC_MASK                   0x8UL                 // Bit mask for I2C_TXC
#define I2C_IFS_ACK                       (0x1UL << 6)           // Set Acknowledge Received Interrupt Flag
#define I2C_IFS_ACK_MASK                   0x40UL                // Bit mask for I2C_ACK
#define I2C_IFS_NACK                      (0x1UL << 7)           // Set Not Acknowledge Received Interrupt Flag
#define I2C_IFS_NACK_MASK                  0x80UL                // Bit mask for I2C_NACK
#define I2C_IFS_MSTOP                     (0x1UL << 8)           // Set MSTOP Interrupt Flag
#define I2C_IFS_MSTOP_MASK                 0x100UL               // Bit mask for I2C_MSTOP
#define I2C_IFS_ARBLOST                   (0x1UL << 9)           // Set Arbitration Lost Interrupt Flag
#define I2C_IFS_ARBLOST_MASK               0x200UL               // Bit mask for I2C_ARBLOST
#define I2C_IFS_BUSERR                    (0x1UL << 10)          // Set Bus Error Interrupt Flag
#define I2C_IFS_BUSERR_MASK                0x400UL               // Bit mask for I2C_BUSERR
#define I2C_IFS_BUSHOLD                   (0x1UL << 11)          // Set Bus Held Interrupt Flag
#define I2C_IFS_BUSHOLD_MASK               0x800UL               // Bit mask for I2C_BUSHOLD
#define I2C_IFS_TXOF                      (0x1UL << 12)          // Set Transmit Buffer Overflow Interrupt Flag
#define I2C_IFS_TXOF_MASK                  0x1000UL              // Bit mask for I2C_TXOF
#define I2C_IFS_RXUF                      (0x1UL << 13)          // Set Receive Buffer Underflow Interrupt Flag
#define I2C_IFS_RXUF_MASK                  0x2000UL              // Bit mask for I2C_RXUF
#define I2C_IFS_BITO                      (0x1UL << 14)          // Set Bus Idle Timeout Interrupt Flag
#define I2C_IFS_BITO_MASK                  0x4000UL              // Bit mask for I2C_BITO
#define I2C_IFS_CLTO                      (0x1UL << 15)          // Set Clock Low Interrupt Flag
#define I2C_IFS_CLTO_MASK                  0x8000UL              // Bit mask for I2C_CLTO
#define I2C_IFS_SSTOP                     (0x1UL << 16)          // Set SSTOP Interrupt Flag
#define I2C_IFS_SSTOP_MASK                 0x10000UL             // Bit mask for I2C_SSTOP

// Bit fields for I2C IFC
#define I2C_IFC_START                     (0x1UL << 0)           // Clear START Interrupt Flag
#define I2C_IFC_START_MASK                 0x1UL                 // Bit mask for I2C_START
#define I2C_IFC_RSTART                    (0x1UL << 1)           // Clear Repeated START Interrupt Flag
#define I2C_IFC_RSTART_MASK                0x2UL                 // Bit mask for I2C_RSTART
#define I2C_IFC_ADDR                      (0x1UL << 2)           // Clear Address Interrupt Flag
#define I2C_IFC_ADDR_MASK                  0x4UL                 // Bit mask for I2C_ADDR
#define I2C_IFC_TXC                       (0x1UL << 3)           // Clear Transfer Completed Interrupt Flag
#define I2C_IFC_TXC_MASK                   0x8UL                 // Bit mask for I2C_TXC
#define I2C_IFC_ACK                       (0x1UL << 6)           // Clear Acknowledge Received Interrupt Flag
#define I2C_IFC_ACK_MASK                   0x40UL                // Bit mask for I2C_ACK
#define I2C_IFC_NACK                      (0x1UL << 7)           // Clear Not Acknowledge Received Interrupt Flag
#define I2C_IFC_NACK_MASK                  0x80UL                // Bit mask for I2C_NACK
#define I2C_IFC_MSTOP                     (0x1UL << 8)           // Clear MSTOP Interrupt Flag
#define I2C_IFC_MSTOP_MASK                 0x100UL               // Bit mask for I2C_MSTOP
#define I2C_IFC_ARBLOST                   (0x1UL << 9)           // Clear Arbitration Lost Interrupt Flag
#define I2C_IFC_ARBLOST_MASK               0x200UL               // Bit mask for I2C_ARBLOST
#define I2C_IFC_BUSERR                    (0x1UL << 10)          // Clear Bus Error Interrupt Flag
#define I2C_IFC_BUSERR_MASK                0x400UL               // Bit mask for I2C_BUSERR
#define I2C_IFC_BUSHOLD                   (0x1UL << 11)          // Clear Bus Held Interrupt Flag
#define I2C_IFC_BUSHOLD_MASK               0x800UL               // Bit mask for I2C_BUSHOLD
#define I2C_IFC_TXOF                      (0x1UL << 12)          // Clear Transmit Buffer Overflow Interrupt Flag
#define I2C_IFC_TXOF_MASK                  0x1000UL              // Bit mask for I2C_TXOF
#define I2C_IFC_RXUF                      (0x1UL << 13)          // Clear Receive Buffer Underflow Interrupt Flag
#define I2C_IFC_RXUF_MASK                  0x2000UL              // Bit mask for I2C_RXUF
#define I2C_IFC_BITO                      (0x1UL << 14)          // Clear Bus Idle Timeout Interrupt Flag
#define I2C_IFC_BITO_MASK                  0x4000UL              // Bit mask for I2C_BITO
#define I2C_IFC_CLTO                      (0x1UL << 15)          // Clear Clock Low Interrupt Flag
#define I2C_IFC_CLTO_MASK                  0x8000UL              // Bit mask for I2C_CLTO
#define I2C_IFC_SSTOP                     (0x1UL << 16)          // Clear SSTOP Interrupt Flag
#define I2C_IFC_SSTOP_MASK                 0x10000UL             // Bit mask for I2C_SSTOP

// Bit fields for I2C IEN
#define I2C_IEN_START                     (0x1UL << 0)           // START Condition Interrupt Enable
#define I2C_IEN_START_MASK                 0x1UL                 // Bit mask for I2C_START
#define I2C_IEN_RSTART                    (0x1UL << 1)           // Repeated START condition Interrupt Enable
#define I2C_IEN_RSTART_MASK                0x2UL                 // Bit mask for I2C_RSTART
#define I2C_IEN_ADDR                      (0x1UL << 2)           // Address Interrupt Enable
#define I2C_IEN_ADDR_MASK                  0x4UL                 // Bit mask for I2C_ADDR
#define I2C_IEN_TXC                       (0x1UL << 3)           // Transfer Completed Interrupt Enable
#define I2C_IEN_TXC_MASK                   0x8UL                 // Bit mask for I2C_TXC
#define I2C_IEN_TXBL                      (0x1UL << 4)           // Transmit Buffer level Interrupt Enable
#define I2C_IEN_TXBL_MASK                  0x10UL                // Bit mask for I2C_TXBL
#define I2C_IEN_RXDATAV                   (0x1UL << 5)           // Receive Data Valid Interrupt Enable
#define I2C_IEN_RXDATAV_MASK               0x20UL                // Bit mask for I2C_RXDATAV
#define I2C_IEN_ACK                       (0x1UL << 6)           // Acknowledge Received Interrupt Enable
#define I2C_IEN_ACK_MASK                   0x40UL                // Bit mask for I2C_ACK
#define I2C_IEN_NACK                      (0x1UL << 7)           // Not Acknowledge Received Interrupt Enable
#define I2C_IEN_NACK_MASK                  0x80UL                // Bit mask for I2C_NACK
#define I2C_IEN_MSTOP                     (0x1UL << 8)           // MSTOP Interrupt Enable
#define I2C_IEN_MSTOP_MASK                 0x100UL               // Bit mask for I2C_MSTOP
#define I2C_IEN_ARBLOST                   (0x1UL << 9)           // Arbitration Lost Interrupt Enable
#define I2C_IEN_ARBLOST_MASK               0x200UL               // Bit mask for I2C_ARBLOST
#define I2C_IEN_BUSERR                    (0x1UL << 10)          // Bus Error Interrupt Enable
#define I2C_IEN_BUSERR_MASK                0x400UL               // Bit mask for I2C_BUSERR
#define I2C_IEN_BUSHOLD                   (0x1UL << 11)          // Bus Held Interrupt Enable
#define I2C_IEN_BUSHOLD_MASK               0x800UL               // Bit mask for I2C_BUSHOLD

#define I2C_IEN_TXOF                      (0x1UL << 12)          // Transmit Buffer Overflow Interrupt Enable
#define I2C_IEN_TXOF_MASK                  0x1000UL              // Bit mask for I2C_TXOF

#define I2C_IEN_RXUF                      (0x1UL << 13)          // Receive Buffer Underflow Interrupt Enable
#define I2C_IEN_RXUF_MASK                  0x2000UL              // Bit mask for I2C_RXUF

#define I2C_IEN_BITO                      (0x1UL << 14)          // Bus Idle Timeout Interrupt Enable
#define I2C_IEN_BITO_MASK                  0x4000UL              // Bit mask for I2C_BITO

#define I2C_IEN_CLTO                      (0x1UL << 15)          // Clock Low Interrupt Enable
#define I2C_IEN_CLTO_MASK                  0x8000UL              // Bit mask for I2C_CLTO

#define I2C_IEN_SSTOP                     (0x1UL << 16)          // SSTOP Interrupt Enable
#define I2C_IEN_SSTOP_MASK                 0x10000UL             // Bit mask for I2C_SSTOP

// Bit fields for I2C ROUTE
#define I2C_ROUTE_SDAPEN                  (0x1UL << 0)           // SDA Pin Enable
#define I2C_ROUTE_SDAPEN_MASK              0x1UL                 // Bit mask for I2C_SDAPEN

#define I2C_ROUTE_SCLPEN                  (0x1UL << 1)           // SCL Pin Enable
#define I2C_ROUTE_SCLPEN_MASK              0x2UL                 // Bit mask for I2C_SCLPEN

#define I2C_ROUTE_LOCATION_MASK            0x700UL               // Bit mask for I2C_LOCATION
#define I2C_ROUTE_LOCATION_LOC0           (0x00000000UL << 8)    // Shifted mode LOC0 for I2C_ROUTE
#define I2C_ROUTE_LOCATION_LOC1           (0x00000001UL << 8)    // Shifted mode LOC1 for I2C_ROUTE
#define I2C_ROUTE_LOCATION_LOC2           (0x00000002UL << 8)    // Shifted mode LOC2 for I2C_ROUTE
#define I2C_ROUTE_LOCATION_LOC3           (0x00000003UL << 8)    // Shifted mode LOC3 for I2C_ROUTE
#define I2C_ROUTE_LOCATION_LOC4           (0x00000004UL << 8)    // Shifted mode LOC4 for I2C_ROUTE
#define I2C_ROUTE_LOCATION_LOC5           (0x00000005UL << 8)    // Shifted mode LOC5 for I2C_ROUTE
#define I2C_ROUTE_LOCATION_LOC6           (0x00000006UL << 8)    // Shifted mode LOC6 for I2C_ROUTE


