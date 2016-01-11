#pragma once

#include "io_types.h"

typedef struct
{
  __IO uint32_t CTRL;   // Channel Control Register
} DMA_CH_TypeDef;

typedef struct
{
  __IO void * __IO SRCEND;     // DMA source address end
  __IO void * __IO DSTEND;     // DMA destination address end
  __IO uint32_t    CTRL;       // DMA control register
  __IO uint32_t    USER;       // DMA padding register, available for user
} DMA_DESCRIPTOR_TypeDef;

typedef struct
{
   __I uint32_t STATUS;         // DMA Status Registers
   __O uint32_t CONFIG;         // DMA Configuration Register
  __IO uint32_t CTRLBASE;       // Channel Control Data Base Pointer Register
   __I uint32_t ALTCTRLBASE;    // Channel Alternate Control Data Base Pointer Register
   __I uint32_t CHWAITSTATUS;   // Channel Wait on Request Status Register
   __O uint32_t CHSWREQ;        // Channel Software Request Register
  __IO uint32_t CHUSEBURSTS;    // Channel Useburst Set Register
   __O uint32_t CHUSEBURSTC;    // Channel Useburst Clear Register
  __IO uint32_t CHREQMASKS;     // Channel Request Mask Set Register
   __O uint32_t CHREQMASKC;     // Channel Request Mask Clear Register
  __IO uint32_t CHENS;          // Channel Enable Set Register
   __O uint32_t CHENC;          // Channel Enable Clear Register
  __IO uint32_t CHALTS;         // Channel Alternate Set Register
   __O uint32_t CHALTC;         // Channel Alternate Clear Register
  __IO uint32_t CHPRIS;         // Channel Priority Set Register
   __O uint32_t CHPRIC;         // Channel Priority Clear Register
       uint32_t RESERVED0[3];   // Reserved for future use
  __IO uint32_t ERRORC;         // Bus Error Clear Register
       uint32_t RESERVED1[880]; // Reserved for future use
   __I uint32_t CHREQSTATUS;    // Channel Request Status
       uint32_t RESERVED2[1];   // Reserved for future use
   __I uint32_t CHSREQSTATUS;   // Channel Single Request Status
       uint32_t RESERVED3[121]; // Reserved for future use
   __I uint32_t IF;             // Interrupt Flag Register
  __IO uint32_t IFS;            // Interrupt Flag Set Register
  __IO uint32_t IFC;            // Interrupt Flag Clear Register
  __IO uint32_t IEN;            // Interrupt Enable register
       uint32_t RESERVED4[60];  // Reserved registers
       DMA_CH_TypeDef CH[4];    // Channel registers
} DMA_TypeDef;

#define DMA                          ((DMA_TypeDef *) 0x400C2000UL)   // DMA base pointer

// Bit fields for DMA STATUS
#define DMA_STATUS_RESETVALUE                          0x10030000UL  // Default value for DMA_STATUS
#define DMA_STATUS_EN                                  (0x1UL << 0)  // DMA Enable Status
#define DMA_STATUS_STATE_MASK                                0xF0UL  // Bit mask for DMA_STATE
#define DMA_STATUS_STATE_DEFAULT                (0x00000000UL << 4)  // Mode DEFAULT for DMA_STATUS
#define DMA_STATUS_STATE_IDLE                   (0x00000000UL << 4)  // Mode IDLE for DMA_STATUS
#define DMA_STATUS_STATE_RDCHCTRLDATA           (0x00000001UL << 4)  // Mode RDCHCTRLDATA for DMA_STATUS
#define DMA_STATUS_STATE_RDSRCENDPTR            (0x00000002UL << 4)  // Mode RDSRCENDPTR for DMA_STATUS
#define DMA_STATUS_STATE_RDDSTENDPTR            (0x00000003UL << 4)  // Mode RDDSTENDPTR for DMA_STATUS
#define DMA_STATUS_STATE_RDSRCDATA              (0x00000004UL << 4)  // Mode RDSRCDATA for DMA_STATUS
#define DMA_STATUS_STATE_WRDSTDATA              (0x00000005UL << 4)  // Mode WRDSTDATA for DMA_STATUS
#define DMA_STATUS_STATE_WAITREQCLR             (0x00000006UL << 4)  // Mode WAITREQCLR for DMA_STATUS
#define DMA_STATUS_STATE_WRCHCTRLDATA           (0x00000007UL << 4)  // Mode WRCHCTRLDATA for DMA_STATUS
#define DMA_STATUS_STATE_STALLED                (0x00000008UL << 4)  // Mode STALLED for DMA_STATUS
#define DMA_STATUS_STATE_DONE                   (0x00000009UL << 4)  // Mode DONE for DMA_STATUS
#define DMA_STATUS_STATE_PERSCATTRANS           (0x0000000AUL << 4)  // Mode PERSCATTRANS for DMA_STATUS
#define DMA_STATUS_CHNUM_MASK                            0x1F0000UL  // Bit mask for DMA_CHNUM
#define DMA_STATUS_CHNUM_DEFAULT               (0x00000003UL << 16)  // Mode DEFAULT for DMA_STATUS

// Bit fields for DMA CONFIG
#define DMA_CONFIG_RESETVALUE                          0x00000000UL  // Default value for DMA_CONFIG
#define DMA_CONFIG_MASK                                0x00000021UL  // Mask for DMA_CONFIG
#define DMA_CONFIG_EN                                  (0x1UL << 0)  // Enable DMA
#define DMA_CONFIG_CHPROT                              (0x1UL << 5)  // Channel Protection Control

// Bit fields for DMA CTRLBASE
#define DMA_CTRLBASE_RESETVALUE                        0x00000000UL  // Default value for DMA_CTRLBASE
#define DMA_CTRLBASE_MASK                              0xFFFFFFFFUL  // Mask for DMA_CTRLBASE

// Bit fields for DMA ALTCTRLBASE
#define DMA_ALTCTRLBASE_RESETVALUE                     0x00000040UL  // Default value for DMA_ALTCTRLBASE
#define DMA_ALTCTRLBASE_MASK                           0xFFFFFFFFUL  // Mask for DMA_ALTCTRLBASE
#define DMA_ALTCTRLBASE_ALTCTRLBASE_DEFAULT            0x00000040UL  // Mode DEFAULT for DMA_ALTCTRLBASE

// Bit fields for DMA CHWAITSTATUS
#define DMA_CHWAITSTATUS_RESETVALUE                    0x0000000FUL  // Default value for DMA_CHWAITSTATUS
#define DMA_CHWAITSTATUS_MASK                          0x0000000FUL  // Mask for DMA_CHWAITSTATUS
#define DMA_CHWAITSTATUS_CH0WAITSTATUS                 (0x1UL << 0)  // Channel 0 Wait on Request Status
#define DMA_CHWAITSTATUS_CH1WAITSTATUS                 (0x1UL << 1)  // Channel 1 Wait on Request Status
#define DMA_CHWAITSTATUS_CH2WAITSTATUS                 (0x1UL << 2)  // Channel 2 Wait on Request Status
#define DMA_CHWAITSTATUS_CH3WAITSTATUS                 (0x1UL << 3)  // Channel 3 Wait on Request Status

// Bit fields for DMA CHSWREQ
#define DMA_CHSWREQ_RESETVALUE                         0x00000000UL  // Default value for DMA_CHSWREQ
#define DMA_CHSWREQ_MASK                               0x0000000FUL  // Mask for DMA_CHSWREQ
#define DMA_CHSWREQ_CH0SWREQ                           (0x1UL << 0)  // Channel 0 Software Request
#define DMA_CHSWREQ_CH1SWREQ                           (0x1UL << 1)  // Channel 1 Software Request
#define DMA_CHSWREQ_CH2SWREQ                           (0x1UL << 2)  // Channel 2 Software Request
#define DMA_CHSWREQ_CH3SWREQ                           (0x1UL << 3)  // Channel 3 Software Request

// Bit fields for DMA CHUSEBURSTS
#define DMA_CHUSEBURSTS_RESETVALUE                     0x00000000UL  // Default value for DMA_CHUSEBURSTS
#define DMA_CHUSEBURSTS_MASK                           0x0000000FUL  // Mask for DMA_CHUSEBURSTS
#define DMA_CHUSEBURSTS_CH0USEBURSTS                   (0x1UL << 0)  // Channel 0 Useburst Set

#define DMA_CHUSEBURSTS_CH0USEBURSTS_DEFAULT           0x00000000UL  // Mode DEFAULT for DMA_CHUSEBURSTS
#define DMA_CHUSEBURSTS_CH0USEBURSTS_SINGLEANDBURST    0x00000000UL  // Mode SINGLEANDBURST for DMA_CHUSEBURSTS
#define DMA_CHUSEBURSTS_CH0USEBURSTS_BURSTONLY         0x00000001UL  // Mode BURSTONLY for DMA_CHUSEBURSTS
#define DMA_CHUSEBURSTS_CH1USEBURSTS                   (0x1UL << 1)  // Channel 1 Useburst Set
#define DMA_CHUSEBURSTS_CH2USEBURSTS                   (0x1UL << 2)  // Channel 2 Useburst Set
#define DMA_CHUSEBURSTS_CH3USEBURSTS                   (0x1UL << 3)  // Channel 3 Useburst Set

// Bit fields for DMA CHUSEBURSTC
#define _DMA_CHUSEBURSTC_RESETVALUE                     0x00000000UL  // Default value for DMA_CHUSEBURSTC
#define _DMA_CHUSEBURSTC_MASK                           0x0000000FUL  // Mask for DMA_CHUSEBURSTC
#define DMA_CHUSEBURSTC_CH0USEBURSTC                    (0x1UL << 0)  // Channel 0 Useburst Clear
#define DMA_CHUSEBURSTC_CH1USEBURSTC                    (0x1UL << 1)  // Channel 1 Useburst Clear
#define DMA_CHUSEBURSTC_CH2USEBURSTC                    (0x1UL << 2)  // Channel 2 Useburst Clear
#define DMA_CHUSEBURSTC_CH3USEBURSTC                    (0x1UL << 3)  // Channel 3 Useburst Clear

// Bit fields for DMA CHREQMASKS
#define _DMA_CHREQMASKS_RESETVALUE                      0x00000000UL  // Default value for DMA_CHREQMASKS
#define _DMA_CHREQMASKS_MASK                            0x0000000FUL  // Mask for DMA_CHREQMASKS
#define DMA_CHREQMASKS_CH0REQMASKS                      (0x1UL << 0)  // Channel 0 Request Mask Set
#define DMA_CHREQMASKS_CH1REQMASKS                      (0x1UL << 1)  // Channel 1 Request Mask Set
#define DMA_CHREQMASKS_CH2REQMASKS                      (0x1UL << 2)  // Channel 2 Request Mask Set
#define DMA_CHREQMASKS_CH3REQMASKS                      (0x1UL << 3)  // Channel 3 Request Mask Set

// Bit fields for DMA CHREQMASKC
#define _DMA_CHREQMASKC_RESETVALUE                      0x00000000UL  // Default value for DMA_CHREQMASKC
#define _DMA_CHREQMASKC_MASK                            0x0000000FUL  // Mask for DMA_CHREQMASKC
#define DMA_CHREQMASKC_CH0REQMASKC                      (0x1UL << 0)  // Channel 0 Request Mask Clear
#define DMA_CHREQMASKC_CH1REQMASKC                      (0x1UL << 1)  // Channel 1 Request Mask Clear
#define DMA_CHREQMASKC_CH2REQMASKC                      (0x1UL << 2)  // Channel 2 Request Mask Clear
#define DMA_CHREQMASKC_CH3REQMASKC                      (0x1UL << 3)  // Channel 3 Request Mask Clear

// Bit fields for DMA CHENS
#define _DMA_CHENS_RESETVALUE                           0x00000000UL  // Default value for DMA_CHENS
#define _DMA_CHENS_MASK                                 0x0000000FUL  // Mask for DMA_CHENS
#define DMA_CHENS_CH0ENS                                (0x1UL << 0)  // Channel 0 Enable Set
#define DMA_CHENS_CH1ENS                                (0x1UL << 1)  // Channel 1 Enable Set
#define DMA_CHENS_CH2ENS                                (0x1UL << 2)  // Channel 2 Enable Set
#define DMA_CHENS_CH3ENS                                (0x1UL << 3)  // Channel 3 Enable Set

// Bit fields for DMA CHENC
#define _DMA_CHENC_RESETVALUE                           0x00000000UL  // Default value for DMA_CHENC
#define _DMA_CHENC_MASK                                 0x0000000FUL  // Mask for DMA_CHENC
#define DMA_CHENC_CH0ENC                                (0x1UL << 0)  // Channel 0 Enable Clear
#define DMA_CHENC_CH1ENC                                (0x1UL << 1)  // Channel 1 Enable Clear
#define DMA_CHENC_CH2ENC                                (0x1UL << 2)  // Channel 2 Enable Clear
#define DMA_CHENC_CH3ENC                                (0x1UL << 3)  // Channel 3 Enable Clear

// Bit fields for DMA CHALTS
#define _DMA_CHALTS_RESETVALUE                          0x00000000UL  // Default value for DMA_CHALTS
#define _DMA_CHALTS_MASK                                0x0000000FUL  // Mask for DMA_CHALTS
#define DMA_CHALTS_CH0ALTS                              (0x1UL << 0)  // Channel 0 Alternate Structure Set
#define DMA_CHALTS_CH1ALTS                              (0x1UL << 1)  // Channel 1 Alternate Structure Set
#define DMA_CHALTS_CH2ALTS                              (0x1UL << 2)  // Channel 2 Alternate Structure Set
#define DMA_CHALTS_CH3ALTS                              (0x1UL << 3)  // Channel 3 Alternate Structure Set

// Bit fields for DMA CHALTC
#define _DMA_CHALTC_RESETVALUE                          0x00000000UL  // Default value for DMA_CHALTC
#define _DMA_CHALTC_MASK                                0x0000000FUL  // Mask for DMA_CHALTC
#define DMA_CHALTC_CH0ALTC                              (0x1UL << 0)  // Channel 0 Alternate Clear
#define DMA_CHALTC_CH1ALTC                              (0x1UL << 1)  // Channel 1 Alternate Clear
#define DMA_CHALTC_CH2ALTC                              (0x1UL << 2)  // Channel 2 Alternate Clear
#define DMA_CHALTC_CH3ALTC                              (0x1UL << 3)  // Channel 3 Alternate Clear

// Bit fields for DMA CHPRIS
#define _DMA_CHPRIS_RESETVALUE                          0x00000000UL  // Default value for DMA_CHPRIS
#define _DMA_CHPRIS_MASK                                0x0000000FUL  // Mask for DMA_CHPRIS
#define DMA_CHPRIS_CH0PRIS                              (0x1UL << 0)  // Channel 0 High Priority Set
#define DMA_CHPRIS_CH1PRIS                              (0x1UL << 1)  // Channel 1 High Priority Set
#define DMA_CHPRIS_CH2PRIS                              (0x1UL << 2)  // Channel 2 High Priority Set
#define DMA_CHPRIS_CH3PRIS                              (0x1UL << 3)  // Channel 3 High Priority Set

// Bit fields for DMA CHPRIC
#define _DMA_CHPRIC_RESETVALUE                          0x00000000UL  // Default value for DMA_CHPRIC
#define _DMA_CHPRIC_MASK                                0x0000000FUL  // Mask for DMA_CHPRIC
#define DMA_CHPRIC_CH0PRIC                              (0x1UL << 0)  // Channel 0 High Priority Clear
#define DMA_CHPRIC_CH1PRIC                              (0x1UL << 1)  // Channel 1 High Priority Clear
#define DMA_CHPRIC_CH2PRIC                              (0x1UL << 2)  // Channel 2 High Priority Clear
#define DMA_CHPRIC_CH3PRIC                              (0x1UL << 3)  // Channel 3 High Priority Clear

// Bit fields for DMA ERRORC
#define _DMA_ERRORC_RESETVALUE                          0x00000000UL  // Default value for DMA_ERRORC
#define _DMA_ERRORC_MASK                                0x00000001UL  // Mask for DMA_ERRORC
#define DMA_ERRORC_ERRORC                               (0x1UL << 0)  // Bus Error Clear

// Bit fields for DMA CHREQSTATUS
#define _DMA_CHREQSTATUS_RESETVALUE                     0x00000000UL  // Default value for DMA_CHREQSTATUS
#define _DMA_CHREQSTATUS_MASK                           0x0000000FUL  // Mask for DMA_CHREQSTATUS
#define DMA_CHREQSTATUS_CH0REQSTATUS                    (0x1UL << 0)  // Channel 0 Request Status
#define DMA_CHREQSTATUS_CH1REQSTATUS                    (0x1UL << 1)  // Channel 1 Request Status
#define DMA_CHREQSTATUS_CH2REQSTATUS                    (0x1UL << 2)  // Channel 2 Request Status
#define DMA_CHREQSTATUS_CH3REQSTATUS                    (0x1UL << 3)  // Channel 3 Request Status

// Bit fields for DMA CHSREQSTATUS
#define _DMA_CHSREQSTATUS_RESETVALUE                    0x00000000UL  // Default value for DMA_CHSREQSTATUS
#define _DMA_CHSREQSTATUS_MASK                          0x0000000FUL  // Mask for DMA_CHSREQSTATUS
#define DMA_CHSREQSTATUS_CH0SREQSTATUS                  (0x1UL << 0)  // Channel 0 Single Request Status
#define DMA_CHSREQSTATUS_CH1SREQSTATUS                  (0x1UL << 1)  // Channel 1 Single Request Status
#define DMA_CHSREQSTATUS_CH2SREQSTATUS                  (0x1UL << 2)  // Channel 2 Single Request Status
#define DMA_CHSREQSTATUS_CH3SREQSTATUS                  (0x1UL << 3)  // Channel 3 Single Request Status

// Bit fields for DMA IF
#define _DMA_IF_RESETVALUE                              0x00000000UL  // Default value for DMA_IF
#define _DMA_IF_MASK                                    0x8000000FUL  // Mask for DMA_IF
#define DMA_IF_CH0DONE                                  (0x1UL << 0)  // DMA Channel 0 Complete Interrupt Flag
#define DMA_IF_CH1DONE                                  (0x1UL << 1)  // DMA Channel 1 Complete Interrupt Flag
#define DMA_IF_CH2DONE                                  (0x1UL << 2)  // DMA Channel 2 Complete Interrupt Flag
#define DMA_IF_CH3DONE                                  (0x1UL << 3)  // DMA Channel 3 Complete Interrupt Flag
#define DMA_IF_ERR                                     (0x1UL << 31)  // DMA Error Interrupt Flag

// Bit fields for DMA IFS
#define _DMA_IFS_RESETVALUE                             0x00000000UL  // Default value for DMA_IFS
#define _DMA_IFS_MASK                                   0x8000000FUL  // Mask for DMA_IFS
#define DMA_IFS_CH0DONE                                 (0x1UL << 0)  // DMA Channel 0 Complete Interrupt Flag Set
#define DMA_IFS_CH1DONE                                 (0x1UL << 1)  // DMA Channel 1 Complete Interrupt Flag Set
#define DMA_IFS_CH2DONE                                 (0x1UL << 2)  // DMA Channel 2 Complete Interrupt Flag Set
#define DMA_IFS_CH3DONE                                 (0x1UL << 3)  // DMA Channel 3 Complete Interrupt Flag Set
#define DMA_IFS_ERR                                    (0x1UL << 31)  // DMA Error Interrupt Flag Set

// Bit fields for DMA IFC
#define _DMA_IFC_RESETVALUE                             0x00000000UL  // Default value for DMA_IFC
#define _DMA_IFC_MASK                                   0x8000000FUL  // Mask for DMA_IFC
#define DMA_IFC_CH0DONE                                 (0x1UL << 0)  // DMA Channel 0 Complete Interrupt Flag Clear
#define DMA_IFC_CH1DONE                                 (0x1UL << 1)  // DMA Channel 1 Complete Interrupt Flag Clear
#define DMA_IFC_CH2DONE                                 (0x1UL << 2)  // DMA Channel 2 Complete Interrupt Flag Clear
#define DMA_IFC_CH3DONE                                 (0x1UL << 3)  // DMA Channel 3 Complete Interrupt Flag Clear
#define DMA_IFC_ERR                                    (0x1UL << 31)  // DMA Error Interrupt Flag Clear

// Bit fields for DMA IEN
#define _DMA_IEN_RESETVALUE                             0x00000000UL  // Default value for DMA_IEN
#define _DMA_IEN_MASK                                   0x8000000FUL  // Mask for DMA_IEN
#define DMA_IEN_CH0DONE                                 (0x1UL << 0)  // DMA Channel 0 Complete Interrupt Enable
#define DMA_IEN_CH1DONE                                 (0x1UL << 1)  // DMA Channel 1 Complete Interrupt Enable
#define DMA_IEN_CH2DONE                                 (0x1UL << 2)  // DMA Channel 2 Complete Interrupt Enable
#define DMA_IEN_CH3DONE                                 (0x1UL << 3)  // DMA Channel 3 Complete Interrupt Enable
#define DMA_IEN_ERR                                    (0x1UL << 31)  // DMA Error Interrupt Flag Enable

// Bit fields for DMA CH_CTRL
#define DMA_CH_CTRL_RESETVALUE                          0x00000000UL  // Default value for DMA_CH_CTRL
#define DMA_CH_CTRL_MASK                                0x003F000FUL  // Mask for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_MASK                                0xFUL  // Bit mask for DMA_SIGSEL
#define DMA_CH_CTRL_SIGSEL_ADC0SINGLE                   0x00000000UL  // Mode ADC0SINGLE for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_USART1RXDATAV                0x00000000UL  // Mode USART1RXDATAV for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_LEUART0RXDATAV               0x00000000UL  // Mode LEUART0RXDATAV for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_I2C0RXDATAV                  0x00000000UL  // Mode I2C0RXDATAV for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_TIMER0UFOF                   0x00000000UL  // Mode TIMER0UFOF for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_TIMER1UFOF                   0x00000000UL  // Mode TIMER1UFOF for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_MSCWDATA                     0x00000000UL  // Mode MSCWDATA for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_AESDATAWR                    0x00000000UL  // Mode AESDATAWR for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_ADC0SCAN                     0x00000001UL  // Mode ADC0SCAN for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_USART1TXBL                   0x00000001UL  // Mode USART1TXBL for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_LEUART0TXBL                  0x00000001UL  // Mode LEUART0TXBL for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_I2C0TXBL                     0x00000001UL  // Mode I2C0TXBL for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_TIMER0CC0                    0x00000001UL  // Mode TIMER0CC0 for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_TIMER1CC0                    0x00000001UL  // Mode TIMER1CC0 for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_AESXORDATAWR                 0x00000001UL  // Mode AESXORDATAWR for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_USART1TXEMPTY                0x00000002UL  // Mode USART1TXEMPTY for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_LEUART0TXEMPTY               0x00000002UL  // Mode LEUART0TXEMPTY for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_TIMER0CC1                    0x00000002UL  // Mode TIMER0CC1 for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_TIMER1CC1                    0x00000002UL  // Mode TIMER1CC1 for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_AESDATARD                    0x00000002UL  // Mode AESDATARD for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_USART1RXDATAVRIGHT           0x00000003UL  // Mode USART1RXDATAVRIGHT for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_TIMER0CC2                    0x00000003UL  // Mode TIMER0CC2 for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_TIMER1CC2                    0x00000003UL  // Mode TIMER1CC2 for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_AESKEYWR                     0x00000003UL  // Mode AESKEYWR for DMA_CH_CTRL
#define DMA_CH_CTRL_SIGSEL_USART1TXBLRIGHT              0x00000004UL  // Mode USART1TXBLRIGHT for DMA_CH_CTRL


#define DMA_CH_CTRL_SOURCESEL_MASK                        0x3F0000UL  // Bit mask for DMA_SOURCESEL
#define DMA_CH_CTRL_SOURCESEL_NONE              (0x00000000UL << 16)  // Mode NONE for DMA_CH_CTRL
#define DMA_CH_CTRL_SOURCESEL_ADC0              (0x00000008UL << 16)  // Mode ADC0 for DMA_CH_CTRL
#define DMA_CH_CTRL_SOURCESEL_USART1            (0x0000000DUL << 16)  // Mode USART1 for DMA_CH_CTRL
#define DMA_CH_CTRL_SOURCESEL_LEUART0           (0x00000010UL << 16)  // Mode LEUART0 for DMA_CH_CTRL
#define DMA_CH_CTRL_SOURCESEL_I2C0              (0x00000014UL << 16)  // Mode I2C0 for DMA_CH_CTRL
#define DMA_CH_CTRL_SOURCESEL_TIMER0            (0x00000018UL << 16)  // Mode TIMER0 for DMA_CH_CTRL
#define DMA_CH_CTRL_SOURCESEL_TIMER1            (0x00000019UL << 16)  // Mode TIMER1 for DMA_CH_CTRL
#define DMA_CH_CTRL_SOURCESEL_MSC               (0x00000030UL << 16)  // Mode MSC for DMA_CH_CTRL
#define DMA_CH_CTRL_SOURCESEL_AES               (0x00000031UL << 16)  // Mode AES for DMA_CH_CTRL




#define _DMA_CTRL_DST_INC_MASK                          0xC0000000UL  // Data increment for destination, bit mask
#define _DMA_CTRL_DST_INC_SHIFT                                   30  // Data increment for destination, shift value
#define _DMA_CTRL_DST_INC_BYTE                                  0x00  // Byte/8-bit increment
#define _DMA_CTRL_DST_INC_HALFWORD                              0x01  // Half word/16-bit increment
#define _DMA_CTRL_DST_INC_WORD                                  0x02  // Word/32-bit increment
#define _DMA_CTRL_DST_INC_NONE                                  0x03  // No increment
#define DMA_CTRL_DST_INC_BYTE                           0x00000000UL  // Byte/8-bit increment
#define DMA_CTRL_DST_INC_HALFWORD                       0x40000000UL  // Half word/16-bit increment
#define DMA_CTRL_DST_INC_WORD                           0x80000000UL  // Word/32-bit increment
#define DMA_CTRL_DST_INC_NONE                           0xC0000000UL  // No increment
#define _DMA_CTRL_DST_SIZE_MASK                         0x30000000UL  // Data size for destination - MUST be the same as source, bit mask
#define _DMA_CTRL_DST_SIZE_SHIFT                                  28  // Data size for destination - MUST be the same as source, shift value
#define _DMA_CTRL_DST_SIZE_BYTE                                 0x00  // Byte/8-bit data size
#define _DMA_CTRL_DST_SIZE_HALFWORD                             0x01  // Half word/16-bit data size
#define _DMA_CTRL_DST_SIZE_WORD                                 0x02  // Word/32-bit data size
#define _DMA_CTRL_DST_SIZE_RSVD                                 0x03  // Reserved
#define DMA_CTRL_DST_SIZE_BYTE                          0x00000000UL  // Byte/8-bit data size
#define DMA_CTRL_DST_SIZE_HALFWORD                      0x10000000UL  // Half word/16-bit data size
#define DMA_CTRL_DST_SIZE_WORD                          0x20000000UL  // Word/32-bit data size
#define DMA_CTRL_DST_SIZE_RSVD                          0x30000000UL  // Reserved - do not use
#define _DMA_CTRL_SRC_INC_MASK                          0x0C000000UL  // Data increment for source, bit mask
#define _DMA_CTRL_SRC_INC_SHIFT                                   26  // Data increment for source, shift value
#define _DMA_CTRL_SRC_INC_BYTE                                  0x00  // Byte/8-bit increment
#define _DMA_CTRL_SRC_INC_HALFWORD                              0x01  // Half word/16-bit increment
#define _DMA_CTRL_SRC_INC_WORD                                  0x02  // Word/32-bit increment
#define _DMA_CTRL_SRC_INC_NONE                                  0x03  // No increment
#define DMA_CTRL_SRC_INC_BYTE                           0x00000000UL  // Byte/8-bit increment
#define DMA_CTRL_SRC_INC_HALFWORD                       0x04000000UL  // Half word/16-bit increment
#define DMA_CTRL_SRC_INC_WORD                           0x08000000UL  // Word/32-bit increment
#define DMA_CTRL_SRC_INC_NONE                           0x0C000000UL  // No increment
#define _DMA_CTRL_SRC_SIZE_MASK                         0x03000000UL  // Data size for source - MUST be the same as destination, bit mask
#define _DMA_CTRL_SRC_SIZE_SHIFT                                  24  // Data size for source - MUST be the same as destination, shift value
#define _DMA_CTRL_SRC_SIZE_BYTE                                 0x00  // Byte/8-bit data size
#define _DMA_CTRL_SRC_SIZE_HALFWORD                             0x01  // Half word/16-bit data size
#define _DMA_CTRL_SRC_SIZE_WORD                                 0x02  // Word/32-bit data size
#define _DMA_CTRL_SRC_SIZE_RSVD                                 0x03  // Reserved
#define DMA_CTRL_SRC_SIZE_BYTE                          0x00000000UL  // Byte/8-bit data size
#define DMA_CTRL_SRC_SIZE_HALFWORD                      0x01000000UL  // Half word/16-bit data size
#define DMA_CTRL_SRC_SIZE_WORD                          0x02000000UL  // Word/32-bit data size
#define DMA_CTRL_SRC_SIZE_RSVD                          0x03000000UL  // Reserved - do not use
#define _DMA_CTRL_DST_PROT_CTRL_MASK                    0x00E00000UL  // Protection flag for destination, bit mask
#define _DMA_CTRL_DST_PROT_CTRL_SHIFT                             21  // Protection flag for destination, shift value
#define DMA_CTRL_DST_PROT_PRIVILEGED                    0x00200000UL  // Privileged mode for destination
#define DMA_CTRL_DST_PROT_NON_PRIVILEGED                0x00000000UL  // Non-privileged mode for estination
#define _DMA_CTRL_SRC_PROT_CTRL_MASK                    0x001C0000UL  // Protection flag for source, bit mask
#define _DMA_CTRL_SRC_PROT_CTRL_SHIFT                             18  // Protection flag for source, shift value
#define DMA_CTRL_SRC_PROT_PRIVILEGED                    0x00040000UL  // Privileged mode for destination
#define DMA_CTRL_SRC_PROT_NON_PRIVILEGED                0x00000000UL  // Non-privileged mode for estination
#define _DMA_CTRL_PROT_NON_PRIVILEGED                           0x00  // Protection bits to indicate non-privileged access
#define _DMA_CTRL_PROT_PRIVILEGED                               0x01  // Protection bits to indicate privileged access
#define _DMA_CTRL_R_POWER_MASK                          0x0003C000UL  // DMA arbitration mask
#define _DMA_CTRL_R_POWER_SHIFT                                   14  // Number of DMA cycles before controller does new arbitration in 2^R
#define _DMA_CTRL_R_POWER_1                                     0x00  // Arbitrate after each transfer
#define _DMA_CTRL_R_POWER_2                                     0x01  // Arbitrate after every 2 transfers
#define _DMA_CTRL_R_POWER_4                                     0x02  // Arbitrate after every 4 transfers
#define _DMA_CTRL_R_POWER_8                                     0x03  // Arbitrate after every 8 transfers
#define _DMA_CTRL_R_POWER_16                                    0x04  // Arbitrate after every 16 transfers
#define _DMA_CTRL_R_POWER_32                                    0x05  // Arbitrate after every 32 transfers
#define _DMA_CTRL_R_POWER_64                                    0x06  // Arbitrate after every 64 transfers
#define _DMA_CTRL_R_POWER_128                                   0x07  // Arbitrate after every 128 transfers
#define _DMA_CTRL_R_POWER_256                                   0x08  // Arbitrate after every 256 transfers
#define _DMA_CTRL_R_POWER_512                                   0x09  // Arbitrate after every 512 transfers
#define _DMA_CTRL_R_POWER_1024                                  0x0a  // Arbitrate after every 1024 transfers
#define DMA_CTRL_R_POWER_1                              0x00000000UL  // Arbitrate after each transfer
#define DMA_CTRL_R_POWER_2                              0x00004000UL  // Arbitrate after every 2 transfers
#define DMA_CTRL_R_POWER_4                              0x00008000UL  // Arbitrate after every 4 transfers
#define DMA_CTRL_R_POWER_8                              0x0000c000UL  // Arbitrate after every 8 transfers
#define DMA_CTRL_R_POWER_16                             0x00010000UL  // Arbitrate after every 16 transfers
#define DMA_CTRL_R_POWER_32                             0x00014000UL  // Arbitrate after every 32 transfers
#define DMA_CTRL_R_POWER_64                             0x00018000UL  // Arbitrate after every 64 transfers
#define DMA_CTRL_R_POWER_128                            0x0001c000UL  // Arbitrate after every 128 transfers
#define DMA_CTRL_R_POWER_256                            0x00020000UL  // Arbitrate after every 256 transfers
#define DMA_CTRL_R_POWER_512                            0x00024000UL  // Arbitrate after every 512 transfers
#define DMA_CTRL_R_POWER_1024                           0x00028000UL  // Arbitrate after every 1024 transfers
#define _DMA_CTRL_N_MINUS_1_MASK                        0x00003FF0UL  // Number of DMA transfers minus 1, bit mask. See PL230 documentation
#define _DMA_CTRL_N_MINUS_1_SHIFT                                  4  // Number of DMA transfers minus 1, shift mask. See PL230 documentation
#define _DMA_CTRL_NEXT_USEBURST_MASK                    0x00000008UL  // DMA useburst_set[C] is 1 when using scatter-gather DMA and using alternate data
#define _DMA_CTRL_NEXT_USEBURST_SHIFT                              3  // DMA useburst shift
#define _DMA_CTRL_CYCLE_CTRL_MASK                       0x00000007UL  // DMA Cycle control bit mask - basic/auto/ping-poing/scath-gath
#define _DMA_CTRL_CYCLE_CTRL_SHIFT                                 0  // DMA Cycle control bit shift
#define _DMA_CTRL_CYCLE_CTRL_INVALID                            0x00  // Invalid cycle type
#define _DMA_CTRL_CYCLE_CTRL_BASIC                              0x01  // Basic cycle type
#define _DMA_CTRL_CYCLE_CTRL_AUTO                               0x02  // Auto cycle type
#define _DMA_CTRL_CYCLE_CTRL_PINGPONG                           0x03  // PingPong cycle type
#define _DMA_CTRL_CYCLE_CTRL_MEM_SCATTER_GATHER                 0x04  // Memory scatter gather cycle type
#define _DMA_CTRL_CYCLE_CTRL_MEM_SCATTER_GATHER_ALT             0x05  // Memory scatter gather using alternate structure
#define _DMA_CTRL_CYCLE_CTRL_PER_SCATTER_GATHER                 0x06  // Peripheral scatter gather cycle type
#define _DMA_CTRL_CYCLE_CTRL_PER_SCATTER_GATHER_ALT             0x07  // Peripheral scatter gather cycle type using alternate structure
#define DMA_CTRL_CYCLE_CTRL_INVALID                     0x00000000UL  // Invalid cycle type
#define DMA_CTRL_CYCLE_CTRL_BASIC                       0x00000001UL  // Basic cycle type
#define DMA_CTRL_CYCLE_CTRL_AUTO                        0x00000002UL  // Auto cycle type
#define DMA_CTRL_CYCLE_CTRL_PINGPONG                    0x00000003UL  // PingPong cycle type
#define DMA_CTRL_CYCLE_CTRL_MEM_SCATTER_GATHER         0x000000004UL  // Memory scatter gather cycle type
#define DMA_CTRL_CYCLE_CTRL_MEM_SCATTER_GATHER_ALT     0x000000005UL  // Memory scatter gather using alternate structure
#define DMA_CTRL_CYCLE_CTRL_PER_SCATTER_GATHER         0x000000006UL  // Peripheral scatter gather cycle type
#define DMA_CTRL_CYCLE_CTRL_PER_SCATTER_GATHER_ALT     0x000000007UL  // Peripheral scatter gather cycle type using alternate structure
