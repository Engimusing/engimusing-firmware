#pragma once

#include "io_types.h"

typedef struct
{
  __IO uint32_t CTRL;         // Memory System Control Register
  __IO uint32_t READCTRL;     // Read Control Register
  __IO uint32_t WRITECTRL;    // Write Control Register
  __IO uint32_t WRITECMD;     // Write Command Register
  __IO uint32_t ADDRB;        // Page Erase/Write Address Buffer
       uint32_t RESERVED0[1]; // Reserved for future use **/
  __IO uint32_t WDATA;        // Write Data Register
   __I uint32_t STATUS;       // Status Register
       uint32_t RESERVED1[3]; // Reserved for future use **/
   __I uint32_t IF;           // Interrupt Flag Register
  __IO uint32_t IFS;          // Interrupt Flag Set Register
  __IO uint32_t IFC;          // Interrupt Flag Clear Register
  __IO uint32_t IEN;          // Interrupt Enable Register
  __IO uint32_t LOCK;         // Configuration Lock Register
  __IO uint32_t CMD;          // Command Register
   __I uint32_t CACHEHITS;    // Cache Hits Performance Counter
   __I uint32_t CACHEMISSES;  // Cache Misses Performance Counter
       uint32_t RESERVED2[1]; // Reserved for future use **/
  __IO uint32_t TIMEBASE;     // Flash Write and Erase Timebase
  __IO uint32_t MASSLOCK;     // Mass Erase Lock Register
  __IO uint32_t IRQLATENCY;   // Irq Latency Register
} MSC_TypeDef;

#define MSC                ((MSC_TypeDef *) 0x400C0000)   // MSC base pointer

#define MSC_UNLOCK_CODE                          0x1B71    // MSC unlock code

// Bit fields for MSC CTRL
#define MSC_CTRL_RESETVALUE                0x00000001UL    // Default value for MSC_CTRL
#define MSC_CTRL_MASK                      0x00000001UL    // Mask for MSC_CTRL
#define MSC_CTRL_BUSFAULT                  (0x1UL << 0)    // Bus Fault Response Enable

// Bit fields for MSC READCTRL
#define MSC_READCTRL_RESETVALUE            0x00000001UL    // Default value for MSC_READCTRL
#define MSC_READCTRL_MASK                  0x0000009FUL    // Mask for MSC_READCTRL

#define MSC_READCTRL_MODE_MASK                    0x7UL    // Bit mask for MSC_MODE
#define MSC_READCTRL_MODE_WS0              0x00000000UL    // Mode WS0 for MSC_READCTRL
#define MSC_READCTRL_MODE_WS1              0x00000001UL    // Mode WS1 for MSC_READCTRL

#define MSC_READCTRL_IFCDIS                (0x1UL << 3)    // Internal Flash Cache Disable
#define MSC_READCTRL_AIDIS                 (0x1UL << 4)    // Automatic Invalidate Disable
#define MSC_READCTRL_RAMCEN                (0x1UL << 7)    // RAM Cache Enable

// Bit fields for MSC WRITECTRL
#define MSC_WRITECTRL_RESETVALUE           0x00000000UL    // Default value for MSC_WRITECTRL
#define MSC_WRITECTRL_MASK                 0x00000003UL    // Mask for MSC_WRITECTRL
#define MSC_WRITECTRL_WREN                 (0x1UL << 0)    // Enable Write/Erase Controller
#define MSC_WRITECTRL_IRQERASEABORT        (0x1UL << 1)    // Abort Page Erase on Interrupt

// Bit fields for MSC WRITECMD
#define MSC_WRITECMD_RESETVALUE            0x00000000UL    // Default value for MSC_WRITECMD
#define MSC_WRITECMD_MASK                  0x0000113FUL    // Mask for MSC_WRITECMD
#define MSC_WRITECMD_LADDRIM               (0x1UL << 0)    // Load MSC_ADDRB into ADDR
#define MSC_WRITECMD_ERASEPAGE             (0x1UL << 1)    // Erase Page
#define MSC_WRITECMD_WRITEEND              (0x1UL << 2)    // End Write Mode
#define MSC_WRITECMD_WRITEONCE             (0x1UL << 3)    // Word Write-Once Trigger
#define MSC_WRITECMD_WRITETRIG             (0x1UL << 4)    // Word Write Sequence Trigger
#define MSC_WRITECMD_ERASEABORT            (0x1UL << 5)    // Abort erase sequence
#define MSC_WRITECMD_ERASEMAIN0            (0x1UL << 8)    // Mass erase region 0
#define MSC_WRITECMD_CLEARWDATA           (0x1UL << 12)    // Clear WDATA state

// Bit fields for MSC ADDRB
#define MSC_ADDRB_RESETVALUE               0x00000000UL    // Default value for MSC_ADDRB
#define MSC_ADDRB_MASK                     0xFFFFFFFFUL    // Mask for MSC_ADDRB

// Bit fields for MSC WDATA
#define MSC_WDATA_RESETVALUE               0x00000000UL    // Default value for MSC_WDATA
#define MSC_WDATA_MASK                     0xFFFFFFFFUL    // Mask for MSC_WDATA

// Bit fields for MSC STATUS
#define MSC_STATUS_RESETVALUE              0x00000008UL    // Default value for MSC_STATUS
#define MSC_STATUS_MASK                    0x0000007FUL    // Mask for MSC_STATUS
#define MSC_STATUS_BUSY                    (0x1UL << 0)    // Erase/Write Busy
#define MSC_STATUS_LOCKED                  (0x1UL << 1)    // Access Locked
#define MSC_STATUS_INVADDR                 (0x1UL << 2)    // Invalid Write Address or Erase Page
#define MSC_STATUS_WDATAREADY              (0x1UL << 3)    // WDATA Write Ready
#define MSC_STATUS_WORDTIMEOUT             (0x1UL << 4)    // Flash Write Word Timeout
#define MSC_STATUS_ERASEABORTED            (0x1UL << 5)    // The Current Flash Erase Operation Aborted
#define MSC_STATUS_PCRUNNING               (0x1UL << 6)    // Performance Counters Running

// Bit fields for MSC IF
#define MSC_IF_RESETVALUE                  0x00000000UL    // Default value for MSC_IF
#define MSC_IF_MASK                        0x0000000FUL    // Mask for MSC_IF
#define MSC_IF_ERASE                       (0x1UL << 0)    // Erase Done Interrupt Read Flag
#define MSC_IF_WRITE                       (0x1UL << 1)    // Write Done Interrupt Read Flag
#define MSC_IF_CHOF                        (0x1UL << 2)    // Cache Hits Overflow Interrupt Flag
#define MSC_IF_CMOF                        (0x1UL << 3)    // Cache Misses Overflow Interrupt Flag

// Bit fields for MSC IFS
#define MSC_IFS_RESETVALUE                 0x00000000UL    // Default value for MSC_IFS
#define MSC_IFS_MASK                       0x0000000FUL    // Mask for MSC_IFS
#define MSC_IFS_ERASE                      (0x1UL << 0)    // Erase Done Interrupt Set
#define MSC_IFS_WRITE                      (0x1UL << 1)    // Write Done Interrupt Set
#define MSC_IFS_CHOF                       (0x1UL << 2)    // Cache Hits Overflow Interrupt Set
#define MSC_IFS_CMOF                       (0x1UL << 3)    // Cache Misses Overflow Interrupt Set

// Bit fields for MSC IFC
#define MSC_IFC_RESETVALUE                 0x00000000UL    // Default value for MSC_IFC
#define MSC_IFC_MASK                       0x0000000FUL    // Mask for MSC_IFC
#define MSC_IFC_ERASE                      (0x1UL << 0)    // Erase Done Interrupt Clear
#define MSC_IFC_WRITE                      (0x1UL << 1)    // Write Done Interrupt Clear
#define MSC_IFC_CHOF                       (0x1UL << 2)    // Cache Hits Overflow Interrupt Clear
#define MSC_IFC_CMOF                       (0x1UL << 3)    // Cache Misses Overflow Interrupt Clear

// Bit fields for MSC IEN
#define MSC_IEN_RESETVALUE                 0x00000000UL    // Default value for MSC_IEN
#define MSC_IEN_MASK                       0x0000000FUL    // Mask for MSC_IEN
#define MSC_IEN_ERASE                      (0x1UL << 0)    // Erase Done Interrupt Enable
#define MSC_IEN_WRITE                      (0x1UL << 1)    // Write Done Interrupt Enable
#define MSC_IEN_CHOF                       (0x1UL << 2)    // Cache Hits Overflow Interrupt Enable
#define MSC_IEN_CMOF                       (0x1UL << 3)    // Cache Misses Overflow Interrupt Enable

// Bit fields for MSC LOCK
#define MSC_LOCK_RESETVALUE                0x00000000UL    // Default value for MSC_LOCK
#define MSC_LOCK_MASK                      0x0000FFFFUL    // Mask for MSC_LOCK
#define MSC_LOCK_LOCKKEY_MASK                  0xFFFFUL    // Bit mask for MSC_LOCKKEY

// Bit fields for MSC CMD
#define MSC_CMD_RESETVALUE                 0x00000000UL    // Default value for MSC_CMD
#define MSC_CMD_MASK                       0x00000007UL    // Mask for MSC_CMD
#define MSC_CMD_INVCACHE                   (0x1UL << 0)    // Invalidate Instruction Cache
#define MSC_CMD_STARTPC                    (0x1UL << 1)    // Start Performance Counters
#define MSC_CMD_STOPPC                     (0x1UL << 2)    // Stop Performance Counters

// Bit fields for MSC CACHEHITS
#define MSC_CACHEHITS_RESETVALUE          0x00000000UL     // Default value for MSC_CACHEHITS
#define MSC_CACHEHITS_MASK                0x000FFFFFUL     // Mask for MSC_CACHEHITS

// Bit fields for MSC CACHEMISSES
#define MSC_CACHEMISSES_RESETVALUE        0x00000000UL     // Default value for MSC_CACHEMISSES
#define MSC_CACHEMISSES_MASK              0x000FFFFFUL     // Mask for MSC_CACHEMISSES

// Bit fields for MSC TIMEBASE
#define MSC_TIMEBASE_RESETVALUE           0x00000010UL     // Default value for MSC_TIMEBASE
#define MSC_TIMEBASE_MASK                 0x0001003FUL     // Mask for MSC_TIMEBASE

#define MSC_TIMEBASE_BASE_MASK                  0x3FUL     // Bit mask for MSC_BASE
#define MSC_TIMEBASE_BASE_DEFAULT         0x00000010UL     // Mode DEFAULT for MSC_TIMEBASE

#define MSC_TIMEBASE_PERIOD_DEFAULT         (0x0 << 16)    // Shifted mode DEFAULT for MSC_TIMEBASE
#define MSC_TIMEBASE_PERIOD_1US             (0x0 << 16)    // Shifted mode 1US for MSC_TIMEBASE
#define MSC_TIMEBASE_PERIOD_5US             (0x1 << 16)    // Shifted mode 5US for MSC_TIMEBASE

// Bit fields for MSC MASSLOCK
#define MSC_MASSLOCK_RESETVALUE            0x00000001UL    // Default value for MSC_MASSLOCK
#define MSC_MASSLOCK_MASK                  0x0000FFFFUL    // Mask for MSC_MASSLOCK

// Bit fields for MSC IRQLATENCY
#define MSC_IRQLATENCY_RESETVALUE          0x00000000UL    // Default value for MSC_IRQLATENCY
#define MSC_IRQLATENCY_MASK                0x000000FFUL    // Mask for MSC_IRQLATENCY
