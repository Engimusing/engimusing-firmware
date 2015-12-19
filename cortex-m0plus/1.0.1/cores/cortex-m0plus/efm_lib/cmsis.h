#pragma once

#include "io_types.h"

  // Interrupt Number Definition
typedef enum IRQn
{
/******  Cortex-M0+ Processor Exceptions Numbers *****************************************/
  NonMaskableInt_IRQn = -14,                /*!< 2 Non Maskable Interrupt                */
  HardFault_IRQn      = -13,                /*!< 3 Cortex-M0+ Hard Fault Interrupt       */
  SVCall_IRQn         = -5,                 /*!< 11 Cortex-M0+ SV Call Interrupt         */
  PendSV_IRQn         = -2,                 /*!< 14 Cortex-M0+ Pend SV Interrupt         */
  SysTick_IRQn        = -1,                 /*!< 15 Cortex-M0+ System Tick Interrupt     */

/******  EFM32ZG Peripheral Interrupt Numbers *********************************************/
  DMA_IRQn            = 0,  /*!< 16+0 EFM32 DMA Interrupt */
  GPIO_EVEN_IRQn      = 1,  /*!< 16+1 EFM32 GPIO_EVEN Interrupt */
  TIMER0_IRQn         = 2,  /*!< 16+2 EFM32 TIMER0 Interrupt */
  ACMP0_IRQn          = 3,  /*!< 16+3 EFM32 ACMP0 Interrupt */
  ADC0_IRQn           = 4,  /*!< 16+4 EFM32 ADC0 Interrupt */
  I2C0_IRQn           = 5,  /*!< 16+5 EFM32 I2C0 Interrupt */
  GPIO_ODD_IRQn       = 6,  /*!< 16+6 EFM32 GPIO_ODD Interrupt */
  TIMER1_IRQn         = 7,  /*!< 16+7 EFM32 TIMER1 Interrupt */
  USART1_RX_IRQn      = 8,  /*!< 16+8 EFM32 USART1_RX Interrupt */
  USART1_TX_IRQn      = 9,  /*!< 16+9 EFM32 USART1_TX Interrupt */
  LEUART0_IRQn        = 10, /*!< 16+10 EFM32 LEUART0 Interrupt */
  PCNT0_IRQn          = 11, /*!< 16+11 EFM32 PCNT0 Interrupt */
  RTC_IRQn            = 12, /*!< 16+12 EFM32 RTC Interrupt */
  CMU_IRQn            = 13, /*!< 16+13 EFM32 CMU Interrupt */
  VCMP_IRQn           = 14, /*!< 16+14 EFM32 VCMP Interrupt */
  MSC_IRQn            = 15, /*!< 16+15 EFM32 MSC Interrupt */
  AES_IRQn            = 16, /*!< 16+16 EFM32 AES Interrupt */
} IRQn_Type;

  // Structure type to access the Nested Vectored Interrupt Controller (NVIC).
typedef struct
{
  __IO uint32_t ISER[1];                 // Offset: 0x000 (R/W)  Interrupt Set Enable Register
       uint32_t RESERVED0[31];
  __IO uint32_t ICER[1];                 // Offset: 0x080 (R/W)  Interrupt Clear Enable Register
       uint32_t RSERVED1[31];
  __IO uint32_t ISPR[1];                 // Offset: 0x100 (R/W)  Interrupt Set Pending Register
       uint32_t RESERVED2[31];
  __IO uint32_t ICPR[1];                 // Offset: 0x180 (R/W)  Interrupt Clear Pending Register
       uint32_t RESERVED3[31];
       uint32_t RESERVED4[64];
  __IO uint32_t IP[8];                   // Offset: 0x300 (R/W)  Interrupt Priority Register
}  NVIC_Type;


// Structure type to access the System Control Block (SCB).
typedef struct
{
  __I  uint32_t CPUID;     // Offset: 0x000 (R/ )  CPUID Base Register
  __IO uint32_t ICSR;      // Offset: 0x004 (R/W)  Interrupt Control and State Register
  __IO uint32_t VTOR;      // Offset: 0x008 (R/W)  Vector Table Offset Register
  __IO uint32_t AIRCR;     // Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register
  __IO uint32_t SCR;       // Offset: 0x010 (R/W)  System Control Register
  __IO uint32_t CCR;       // Offset: 0x014 (R/W)  Configuration Control Register
       uint32_t RESERVED1;
  __IO uint32_t SHP[2];    // Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED
  __IO uint32_t SHCSR;     // Offset: 0x024 (R/W)  System Handler Control and State Register
} SCB_Type;

  // Structure type to access the System Timer (SysTick).
typedef struct
{
  __IO uint32_t CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
  __IO uint32_t VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
  __I  uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
} SysTick_Type;

#define SCS_BASE          (0xE000E000UL)          // System Control Space Base Address

  // Memory mapping of Cortex-M0+ Hardware
#define SCS_BASE               (0xE000E000UL)                  // System Control Space Base Address
#define SysTick_BASE           (SCS_BASE +  0x0010UL)          // SysTick Base Address
#define NVIC_BASE              (SCS_BASE +  0x0100UL)          // NVIC Base Address
#define SCB_BASE               (SCS_BASE +  0x0D00UL)          // System Control Block Base Address
#define SCB                    ((SCB_Type*)     SCB_BASE)      // SCB configuration struct
#define SysTick                ((SysTick_Type*) SysTick_BASE)  // SysTick configuration struct
#define NVIC                   ((NVIC_Type*)    NVIC_BASE)     // NVIC configuration struct
#define SCB_ICSR_PENDSTSET_Msk (1UL << 26)                     // SCB ICSR: PENDSTSET Mask

  // Interrupt Priorities are WORD accessible only under ARMv6M
  // The following MACROS handle generation of the register offset and byte masks
#define _BIT_SHIFT(IRQn)         (  (((uint32_t)(IRQn)       )    &  0x03) * 8 )
#define _SHP_IDX(IRQn)           ( ((((uint32_t)(IRQn) & 0x0F)-8) >>    2)     )
#define _IP_IDX(IRQn)            (   ((uint32_t)(IRQn)            >>    2)     )

#define __NVIC_PRIO_BITS          2   // NVIC interrupt priority bits


#define SysTick_LOAD_RELOAD_Msk      0x00FFFFFFUL        /*!< SysTick LOAD: RELOAD Mask */
#define SysTick_CTRL_CLKSOURCE_Msk   (1UL << 2)          /*!< SysTick CTRL: CLKSOURCE Mask */
#define SysTick_CTRL_TICKINT_Msk     (1UL << 1)          /*!< SysTick CTRL: TICKINT Mask */
#define SysTick_CTRL_ENABLE_Msk        1UL               /*!< SysTick CTRL: ENABLE Mask */



__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1) > SysTick_LOAD_RELOAD_Msk)  return (1);      // Reload value impossible
  SysTick->LOAD  = ticks - 1;                                  // set reload register
  // set Priority for Systick Interrupt
  SCB->SHP[_SHP_IDX(SysTick_IRQn)] = (SCB->SHP[_SHP_IDX(SysTick_IRQn)] & ~(0xFF << _BIT_SHIFT(SysTick_IRQn))) |
    (((((1<<__NVIC_PRIO_BITS) - 1) << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(SysTick_IRQn));

  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}

__STATIC_INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  NVIC->ICPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); // Clear pending interrupt
}

__STATIC_INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  NVIC->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); // Enable interrupt
}

__STATIC_INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  NVIC->ICER[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); // Disable interrupt
}

__STATIC_INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority) // Set priority
{
  if(IRQn < 0) {
    SCB->SHP[_SHP_IDX(IRQn)] = (SCB->SHP[_SHP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))) |
        (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(IRQn)); }
  else {
    NVIC->IP[_IP_IDX(IRQn)] = (NVIC->IP[_IP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))) |
        (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(IRQn)); }
}

__STATIC_INLINE uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {  // get priority for Cortex-M0 system interrupts
    return((uint32_t)(((SCB->SHP[_SHP_IDX(IRQn)] >> _BIT_SHIFT(IRQn) ) & 0xFF) >> (8 - __NVIC_PRIO_BITS)));  }
  else {         // get priority for device specific interrupts
    return((uint32_t)(((NVIC->IP[ _IP_IDX(IRQn)] >> _BIT_SHIFT(IRQn) ) & 0xFF) >> (8 - __NVIC_PRIO_BITS)));  }
}

// SCB CPUID Register Definitions
#define SCB_CPUID_IMPLEMENTER_Msk       (0xFFUL << 24)      // SCB CPUID: IMPLEMENTER Mask
#define SCB_CPUID_VARIANT_Msk            (0xFUL << 20)      // SCB CPUID: VARIANT Mask
#define SCB_CPUID_ARCHITECTURE_Msk       (0xFUL << 16)      // SCB CPUID: ARCHITECTURE Mask
#define SCB_CPUID_PARTNO_Msk            (0xFFFUL << 4)      // SCB CPUID: PARTNO Mask
#define SCB_CPUID_REVISION_Msk            (0xFUL << 0)      // SCB CPUID: REVISION Mask

// SCB Interrupt Control State Register Definitions
#define SCB_ICSR_NMIPENDSET_Msk            (1UL << 31)      // SCB ICSR: NMIPENDSET Mask
#define SCB_ICSR_PENDSVSET_Msk             (1UL << 28)      // SCB ICSR: PENDSVSET Mask
#define SCB_ICSR_PENDSVCLR_Msk             (1UL << 27)      // SCB ICSR: PENDSVCLR Mask
#define SCB_ICSR_PENDSTSET_Msk             (1UL << 26)      // SCB ICSR: PENDSTSET Mask
#define SCB_ICSR_PENDSTCLR_Msk             (1UL << 25)      // SCB ICSR: PENDSTCLR Mask
#define SCB_ICSR_ISRPREEMPT_Msk            (1UL << 23)      // SCB ICSR: ISRPREEMPT Mask
#define SCB_ICSR_ISRPENDING_Msk            (1UL << 22)      // SCB ICSR: ISRPENDING Mask
#define SCB_ICSR_VECTPENDING_Msk       (0x1FFUL << 12)      // SCB ICSR: VECTPENDING Mask
#define SCB_ICSR_VECTACTIVE_Msk         (0x1FFUL << 0)      // SCB ICSR: VECTACTIVE Mask

// SCB Interrupt Control State Register Definitions
#define SCB_VTOR_TBLOFF_Msk          (0xFFFFFFUL << 8)      // SCB VTOR: TBLOFF Mask

// SCB Application Interrupt and Reset Control Register Definitions
#define SCB_AIRCR_VECTKEY_Msk         (0xFFFFUL << 16)      // SCB AIRCR: VECTKEY Mask
#define SCB_AIRCR_VECTKEYSTAT_Msk     (0xFFFFUL << 16)      // SCB AIRCR: VECTKEYSTAT Mask
#define SCB_AIRCR_ENDIANESS_Msk            (1UL << 15)      // SCB AIRCR: ENDIANESS Mask
#define SCB_AIRCR_SYSRESETREQ_Msk           (1UL << 2)      // SCB AIRCR: SYSRESETREQ Mask
#define SCB_AIRCR_VECTCLRACTIVE_Msk         (1UL << 1)      // SCB AIRCR: VECTCLRACTIVE Mask

// SCB System Control Register Definitions
#define SCB_SCR_SEVONPEND_Msk               (1UL << 4)      // SCB SCR: SEVONPEND Mask
#define SCB_SCR_SLEEPDEEP_Msk               (1UL << 2)      // SCB SCR: SLEEPDEEP Mask
#define SCB_SCR_SLEEPONEXIT_Msk             (1UL << 1)      // SCB SCR: SLEEPONEXIT Mask

// SCB Configuration Control Register Definitions
#define SCB_CCR_STKALIGN_Msk                (1UL << 9)      // SCB CCR: STKALIGN Mask
#define SCB_CCR_UNALIGN_TRP_Msk             (1UL << 3)      // SCB CCR: UNALIGN_TRP Mask

// SCB System Handler Control and State Register Definitions
#define SCB_SHCSR_SVCALLPENDED_Msk         (1UL << 15)      // SCB SHCSR: SVCALLPENDED Mask


// Macros from core_cmInstr.h
// GNU gcc specific functions

// Define macros for porting to both thumb1 and thumb2.
// For thumb1, use low register (r0-r7), specified by constrant "l"
// Otherwise, use general registers, specified by constrant "r" */
#if defined (__thumb__) && !defined (__thumb2__)
#define __CMSIS_GCC_OUT_REG(r) "=l" (r)
#define __CMSIS_GCC_USE_REG(r) "l" (r)
#else
#define __CMSIS_GCC_OUT_REG(r) "=r" (r)
#define __CMSIS_GCC_USE_REG(r) "r" (r)
#endif

//    No Operation does nothing. This instruction can be used for code alignment purposes.
__attribute__( ( always_inline ) ) __STATIC_INLINE void __NOP(void)
{
  __ASM volatile ("nop");
}

//    Wait For Interrupt is a hint instruction that suspends execution
//    until one of a number of events occurs.
__attribute__( ( always_inline ) ) __STATIC_INLINE void __WFI(void)
{
  __ASM volatile ("wfi");
}

//    Wait For Event is a hint instruction that permits the processor to enter
//    a low-power state until one of a number of events occurs.
__attribute__( ( always_inline ) ) __STATIC_INLINE void __WFE(void)
{
  __ASM volatile ("wfe");
}

//    Send Event is a hint instruction. It causes an event to be signaled to the CPU.
__attribute__( ( always_inline ) ) __STATIC_INLINE void __SEV(void)
{
  __ASM volatile ("sev");
}

//    Instruction Synchronization Barrier flushes the pipeline in the processor,
//    so that all instructions following the ISB are fetched from cache or
//    memory, after the instruction has been completed.
__attribute__( ( always_inline ) ) __STATIC_INLINE void __ISB(void)
{
  __ASM volatile ("isb");
}

//    This function acts as a special kind of Data Memory Barrier.
//    It completes when all explicit memory accesses before this instruction complete.
__attribute__( ( always_inline ) ) __STATIC_INLINE void __DSB(void)
{
  __ASM volatile ("dsb");
}

//    This function ensures the apparent order of the explicit memory operations before
//    and after the instruction, without ensuring their completion.
__attribute__( ( always_inline ) ) __STATIC_INLINE void __DMB(void)
{
  __ASM volatile ("dmb");
}

//  Reverse byte order (32 bit) - This function reverses the byte order in integer value.
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __REV(uint32_t value)
{
#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
  return __builtin_bswap32(value);
#else
  uint32_t result;

  __ASM volatile ("rev %0, %1" : __CMSIS_GCC_OUT_REG (result) : __CMSIS_GCC_USE_REG (value) );
  return(result);
#endif
}

// Reverse byte order (16 bit) - This function reverses the byte order in two unsigned short values.
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __REV16(uint32_t value)
{
  uint32_t result;

  __ASM volatile ("rev16 %0, %1" : __CMSIS_GCC_OUT_REG (result) : __CMSIS_GCC_USE_REG (value) );
  return(result);
}

// Reverse byte order in signed short value with sign extension to integer.
__attribute__( ( always_inline ) ) __STATIC_INLINE int32_t __REVSH(int32_t value)
{
#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
  return (short)__builtin_bswap16(value);
#else
  uint32_t result;

  __ASM volatile ("revsh %0, %1" : __CMSIS_GCC_OUT_REG (result) : __CMSIS_GCC_USE_REG (value) );
  return(result);
#endif
}

// Rotate Right (immediate) of unsigned value (32 bit) in a register rotated by a variable number of bits.
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  return (op1 >> op2) | (op1 << (32 - op2)); 
}

// Breakpoint - This function causes the processor to enter Debug state.
// Debug tools can use this to investigate system state when the instruction at a particular address is reached.
#define __BKPT(value)                       __ASM volatile ("bkpt "#value)

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*******************************************************************************
 **************************   GLOBAL VARIABLES   *******************************
 ******************************************************************************/

extern uint32_t SystemCoreClock;    /**< System Clock Frequency (Core Clock) */

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/* Interrupt routines - prototypes */
void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void DMA_IRQHandler(void);
void GPIO_EVEN_IRQHandler(void);
void TIMER0_IRQHandler(void);
void ACMP0_IRQHandler(void);
void ADC0_IRQHandler(void);
void I2C0_IRQHandler(void);
void GPIO_ODD_IRQHandler(void);
void TIMER1_IRQHandler(void);
void USART1_RX_IRQHandler(void);
void USART1_TX_IRQHandler(void);
void LEUART0_IRQHandler(void);
void PCNT0_IRQHandler(void);
void RTC_IRQHandler(void);
void CMU_IRQHandler(void);
void VCMP_IRQHandler(void);
void MSC_IRQHandler(void);
void AES_IRQHandler(void);

uint32_t SystemCoreClockGet(void);

/**************************************************************************//**
 * @brief
 *   Update CMSIS SystemCoreClock variable.
 *
 * @details
 *   CMSIS defines a global variable SystemCoreClock that shall hold the
 *   core frequency in Hz. If the core frequency is dynamically changed, the
 *   variable must be kept updated in order to be CMSIS compliant.
 *
 *   Notice that if only changing core clock frequency through the EFM32 CMU
 *   API, this variable will be kept updated. This function is only provided
 *   for CMSIS compliance and if a user modifies the the core clock outside
 *   the CMU API.
 *****************************************************************************/
static __INLINE void SystemCoreClockUpdate(void)
{
  SystemCoreClockGet();
}

void SystemInit(void);
uint32_t SystemHFClockGet(void);
uint32_t SystemHFXOClockGet(void);
void SystemHFXOClockSet(uint32_t freq);
uint32_t SystemLFRCOClockGet(void);
uint32_t SystemULFRCOClockGet(void);
uint32_t SystemLFXOClockGet(void);
void SystemLFXOClockSet(uint32_t freq);

#ifdef __cplusplus
}
#endif
