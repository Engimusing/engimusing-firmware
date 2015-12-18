#pragma once

#include "io_types.h"
#include <stdint.h>

#define CMU_HFPERCLKDIV_HFPERCLKEN        (0x1UL << 8)        // HFPERCLK Enable
#define CMU_HFPERCLKEN0_GPIO              (0x1UL << 7)        // General purpose Input/Output Clock Enable
#define CMU_HFCORECLKEN0_LE               (0x1UL << 2)        // Low Energy Peripheral Interface Clock Enable
#define CMU_HFCORECLKEN0_DMA              (0x1UL << 1)        // Direct Memory Access Controller Clock Enable
#define CMU_OSCENCMD_LFRCOEN              (0x1UL << 6)        // LFRCO Enable
#define CMU_LFCLKSEL_LFA_LFRCO            (0x00000001UL)      // Shifted mode LFRCO for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFA_HFCORECLKLEDIV2   0x00000003UL       // Mode HFCORECLKLEDIV2 for CMU_LFCLKSEL
#define CMU_LFCLKSEL_LFA_LFRCO            (0x00000001UL)      // Shifted mode LFRCO for CMU_LFCLKSEL
#define CMU_LFACLKEN0_RTC                 (0x00000001UL)      // Real-Time Counter Clock Enable
#define CMU_LFCLKSEL_LFB_HFCORECLKLEDIV2  (0x00000003UL << 2) // Shifted mode HFCORECLKLEDIV2 for CMU_LFCLKSEL

#define CMU_HFRCOCTRL_BAND_21MHZ     (0x00000004UL << 8)  /**< Shifted mode 21MHZ for CMU_HFRCOCTRL */

#define CMU_HFCORECLKDIV_REG       2
#define CMU_DIV_REG_POS            4
#define CMU_HFCORE_CLK_BRANCH      2
#define CMU_CLK_BRANCH_POS         17

//#define cmuClock_CORE  ((CMU_HFCORECLKDIV_REG << CMU_DIV_REG_POS) | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS))

#define CMU_HFPERCLKEN0_TIMER0   (0x1UL << 0)         // Timer 0 Clock Enable
#define CMU_HFPERCLKEN0_TIMER1   (0x1UL << 1)         // Timer 1 Clock Enable
#define CMU_HFPERCLKEN0_ACMP0    (0x1UL << 2)         // Analog Comparator 0 Clock Enable
#define CMU_HFPERCLKEN0_USART1   (0x1UL << 3)         // USART 1 Clock Enable
#define CMU_HFPERCLKEN0_PRS      (0x1UL << 4)         // Peripheral Reflex System Clock Enable
#define CMU_HFPERCLKEN0_IDAC0    (0x1UL << 6)         // Current Digital to Analog Converter 0 Clock Enable
#define CMU_HFPERCLKEN0_GPIO     (0x1UL << 7)         // General purpose Input/Output Clock Enable
#define CMU_HFPERCLKEN0_VCMP     (0x1UL << 8)         // Voltage Comparator Clock Enable
#define CMU_HFPERCLKEN0_ADC0     (0x1UL << 10)        // Analog to Digital Converter 0 Clock Enable
#define CMU_HFPERCLKEN0_I2C0     (0x1UL << 11)        // I2C 0 Clock Enable

#define CMU_LFBCLKEN0_LEUART0    (0x1UL << 0)         // Low Energy UART 0 Clock Enable
#define CMU_LFBCLKEN0_LEUART1    (0x1UL << 1)         // Low Energy UART 1 Clock Enable

typedef struct
{
  __IO uint32_t CTRL;         // CMU Control Register
  __IO uint32_t HFCORECLKDIV; // High Frequency Core Clock Division Register
  __IO uint32_t HFPERCLKDIV;  // High Frequency Peripheral Clock Division Register
  __IO uint32_t HFRCOCTRL;    // HFRCO Control Register
  __IO uint32_t LFRCOCTRL;    // LFRCO Control Register
  __IO uint32_t AUXHFRCOCTRL; // AUXHFRCO Control Register
  __IO uint32_t CALCTRL;      // Calibration Control Register
  __IO uint32_t CALCNT;       // Calibration Counter Register
  __IO uint32_t OSCENCMD;     // Oscillator Enable/Disable Command Register
  __IO uint32_t CMD;          // Command Register
  __IO uint32_t LFCLKSEL;     // Low Frequency Clock Select Register
  __I uint32_t  STATUS;       // Status Register 
  __I uint32_t  IF;           // Interrupt Flag Register 
  __IO uint32_t IFS;          // Interrupt Flag Set Register 
  __IO uint32_t IFC;          // Interrupt Flag Clear Register 
  __IO uint32_t IEN;          // Interrupt Enable Register 
  __IO uint32_t HFCORECLKEN0; // High Frequency Core Clock Enable Register 0 
  __IO uint32_t HFPERCLKEN0;  // High Frequency Peripheral Clock Enable Register 0 
       uint32_t RESERVED0[2]; // Reserved for future use **/
  __I  uint32_t SYNCBUSY;     // Synchronization Busy Register 
  __IO uint32_t FREEZE;       // Freeze Register 
  __IO uint32_t LFACLKEN0;    // Low Frequency A Clock Enable Register 0  (Async Reg) 
       uint32_t RESERVED1[1]; // Reserved for future use **/
  __IO uint32_t LFBCLKEN0;    // Low Frequency B Clock Enable Register 0 (Async Reg) 
       uint32_t RESERVED2[1]; // Reserved for future use **/
  __IO uint32_t LFAPRESC0;    // Low Frequency A Prescaler Register 0 (Async Reg) 
       uint32_t RESERVED3[1]; // Reserved for future use **/
  __IO uint32_t LFBPRESC0;    // Low Frequency B Prescaler Register 0  (Async Reg) 
       uint32_t RESERVED4[1]; // Reserved for future use **/
  __IO uint32_t PCNTCTRL;     // PCNT Control Register 
       uint32_t RESERVED5[1]; // Reserved for future use
  __IO uint32_t ROUTE;        // I/O Routing Register 
  __IO uint32_t LOCK;         // Configuration Lock Register 
} CMU_TypeDef;


#define CMU  ((CMU_TypeDef *) 0x400C8000UL) // CMU base address


#ifdef __cplusplus
extern "C" {
#endif


uint32_t cmu_hfper_freq_get(void);

#ifdef __cplusplus
}
#endif


