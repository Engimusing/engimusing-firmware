/*
  Copyright (c) 2015 Engimusing LLC.  All right reserved.

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

#ifndef _TIMERLP_
#define _TIMERLP_

#include "efm_cmu_config.h"
#include "efm_pin_config.h"
#include "efm_emu.h"
#include "init_efm.h"
#include "wiring_digital.h"
#include "cmsis.h"

// TIMER_CC EFM32ZG TIMER CC
typedef struct
{
  __IO uint32_t CTRL;            // CC Channel Control Register
  __IO uint32_t CCV;             // CC Channel Value Register
  __I uint32_t  CCVP;            // CC Channel Value Peek Register
  __IO uint32_t CCVB;            // CC Channel Buffer Register
} TIMER_CC_TypeDef;

// EFM32ZG_TIMER Register Declaration
typedef struct
{
  __IO uint32_t    CTRL;         // Control Register
  __IO uint32_t    CMD;          // Command Register
  __I uint32_t     STATUS;       // Status Register
  __IO uint32_t    IEN;          // Interrupt Enable Register
  __I uint32_t     IF;           // Interrupt Flag Register
  __IO uint32_t    IFS;          // Interrupt Flag Set Register
  __IO uint32_t    IFC;          // Interrupt Flag Clear Register
  __IO uint32_t    TOP;          // Counter Top Value Register
  __IO uint32_t    TOPB;         // Counter Top Value Buffer Register
  __IO uint32_t    CNT;          // Counter Value Register
  __IO uint32_t    ROUTE;        // I/O Routing Register
  uint32_t         RESERVED0[1]; // Reserved registers
  TIMER_CC_TypeDef CC[3];        // Compare/Capture Channel
} TIMER_TypeDef;

#define TIMER0       ((TIMER_TypeDef *) 0x40010000UL)        // TIMER0 base pointer
#define TIMER1       ((TIMER_TypeDef *) 0x40010400UL)        // TIMER1 base pointer


#define _TIMER_CTRL_MODE_MASK                    0x3UL           // Bit mask for TIMER_MODE
#define TIMER_CTRL_MODE_UP                         0x0           // Shifted mode UP for TIMER_CTRL
#define TIMER_CTRL_MODE_DOWN                       0x1           // Shifted mode DOWN for TIMER_CTRL
#define TIMER_CTRL_MODE_UPDOWN                     0x2           // Shifted mode UPDOWN for TIMER_CTRL
#define TIMER_CTRL_MODE_QDEC                       0x3           // Shifted mode QDEC for TIMER_CTRL
#define TIMER_CTRL_SYNC                    (0x1UL << 3)          // Timer Start/Stop/Reload Synchronization
#define TIMER_CTRL_OSMEN                   (0x1UL << 4)          // One-shot Mode Enable
#define TIMER_CTRL_QDM_X4                  (0x1UL << 5)          // Quadrature Decoder Mode Selection
#define TIMER_CTRL_DEBUGRUN                (0x1UL << 6)          // Debug Mode Run Enable
#define TIMER_CTRL_DMACLRACT               (0x1UL << 7)          // DMA Request Clear on Active

#define _TIMER_CTRL_RISEA_MASK                  0x300UL          // Bit mask for TIMER_RISEA
#define TIMER_CTRL_RISEA_DEFAULT             (0x0 << 8)          // Shifted mode DEFAULT for TIMER_CTRL
#define TIMER_CTRL_RISEA_NONE                (0x0 << 8)          // Shifted mode NONE for TIMER_CTRL
#define TIMER_CTRL_RISEA_START               (0x1 << 8)          // Shifted mode START for TIMER_CTRL
#define TIMER_CTRL_RISEA_STOP                (0x2 << 8)          // Shifted mode STOP for TIMER_CTRL
#define TIMER_CTRL_RISEA_RELOADSTART         (0x3 << 8)          // Shifted mode RELOADSTART for TIMER_CTRL

#define _TIMER_CTRL_FALLA_MASK                  0xC00UL          // Bit mask for TIMER_FALLA
#define TIMER_CTRL_FALLA_DEFAULT            (0x0 << 10)          // Shifted mode DEFAULT for TIMER_CTRL
#define TIMER_CTRL_FALLA_NONE               (0x0 << 10)          // Shifted mode NONE for TIMER_CTRL
#define TIMER_CTRL_FALLA_START              (0x1 << 10)          // Shifted mode START for TIMER_CTRL
#define TIMER_CTRL_FALLA_STOP               (0x2 << 10)          // Shifted mode STOP for TIMER_CTRL
#define TIMER_CTRL_FALLA_RELOADSTART        (0x3 << 10)          // Shifted mode RELOADSTART for TIMER_CTRL

#define TIMER_CTRL_X2CNT                  (0x1UL << 13)          // 2x Count Mode

#define _TIMER_CTRL_CLKSEL_MASK               0x30000UL          // Bit mask for TIMER_CLKSEL
#define TIMER_CTRL_CLKSEL_DEFAULT           (0x0 << 16)          // Shifted mode DEFAULT for TIMER_CTRL
#define TIMER_CTRL_CLKSEL_PRESCHFPERCLK     (0x0 << 16)          // Shifted mode PRESCHFPERCLK for TIMER_CTRL
#define TIMER_CTRL_CLKSEL_CC1               (0x1 << 16)          // Shifted mode CC1 for TIMER_CTRL
#define TIMER_CTRL_CLKSEL_TIMEROUF          (0x2 << 16)          // Shifted mode TIMEROUF for TIMER_CTRL


#define _TIMER_CTRL_PRESC_SHIFT                     24           // Shift for TIMER_PRESC
#define _TIMER_CTRL_PRESC_MASK              0xF000000UL          // Bit mask for TIMER_PRESC
#define TIMER_CTRL_PRESC_DEFAULT            (0x0 << 24)          // Shifted mode DEFAULT for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV1               (0x0 << 24)          // Shifted mode DIV1 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV2               (0x1 << 24)          // Shifted mode DIV2 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV4               (0x2 << 24)          // Shifted mode DIV4 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV8               (0x3 << 24)          // Shifted mode DIV8 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV16              (0x4 << 24)          // Shifted mode DIV16 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV32              (0x5 << 24)          // Shifted mode DIV32 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV64              (0x6 << 24)          // Shifted mode DIV64 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV128             (0x7 << 24)          // Shifted mode DIV128 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV256             (0x8 << 24)          // Shifted mode DIV256 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV512             (0x9 << 24)          // Shifted mode DIV512 for TIMER_CTRL
#define TIMER_CTRL_PRESC_DIV1024            (0xA << 24)          // Shifted mode DIV1024 for TIMER_CTRL

#define TIMER_CTRL_ATI                    (0x1UL << 28)          // Always Track Inputs

#define TIMER_CTRL_RSSCOIST               (0x1UL << 29)          // Reload-Start Sets Compare Ouptut initial State

#define _TIMER_CMD_MASK                            0x3           // Mask for TIMER_CMD
#define TIMER_CMD_START                            0x1           // Start Timer
#define TIMER_CMD_STOP                     (0x1UL << 1)          // Stop Timer


#define _TIMER_CC_CTRL_MODE_MASK                   0x3         // Bit mask for TIMER_MODE
#define TIMER_CC_CTRL_MODE_OFF                     0x0           // Shifted mode OFF for TIMER_CC_CTRL
#define TIMER_CC_CTRL_MODE_INPUTCAPTURE            0x1           // Shifted mode INPUTCAPTURE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_MODE_OUTPUTCOMPARE           0x2           // Shifted mode OUTPUTCOMPARE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_MODE_PWM                     0x3           // Shifted mode PWM for TIMER_CC_CTRL

#define TIMER_CC_CTRL_OUTINV              (0x1UL << 2)           // Output Invert

#define TIMER_CC_CTRL_COIST               (0x1UL << 4)           // Compare Output Initial State

#define _TIMER_CC_CTRL_CMOA_MASK                 0x300           // Bit mask for TIMER_CMOA
#define TIMER_CC_CTRL_CMOA_NONE                    0x0           // Mode NONE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_CMOA_TOGGLE           (0x1 << 8)           // Shifted mode TOGGLE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_CMOA_CLEAR            (0x2 << 8)           // Shifted mode CLEAR for TIMER_CC_CTRL
#define TIMER_CC_CTRL_CMOA_SET              (0x3 << 8)           // Shifted mode SET for TIMER_CC_CTRL

#define _TIMER_CC_CTRL_COFOA_MASK                0xC00
#define TIMER_CC_CTRL_COFOA_NONE                   0x0           // Mode NONE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_COFOA_TOGGLE         (0x1 << 10)           // Shifted mode TOGGLE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_COFOA_CLEAR          (0x2 << 10)           // Shifted mode CLEAR for TIMER_CC_CTRL
#define TIMER_CC_CTRL_COFOA_SET            (0x3 << 10)           // Shifted mode SET for TIMER_CC_CTRL

#define _TIMER_CC_CTRL_CUFOA_MASK               0x3000           // Bit mask for TIMER_CUFOA
#define TIMER_CC_CTRL_CUFOA_NONE                   0x0           // Mode NONE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_CUFOA_TOGGLE         (0x1 << 12)           // Shifted mode TOGGLE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_CUFOA_CLEAR          (0x2 << 12)           // Shifted mode CLEAR for TIMER_CC_CTRL
#define TIMER_CC_CTRL_CUFOA_SET            (0x3 << 12)           // Shifted mode SET for TIMER_CC_CTRL

#define _TIMER_CC_CTRL_PRSSEL_MASK             0x30000           // Bit mask for TIMER_PRSSEL
#define TIMER_CC_CTRL_PRSSEL_PRSCH1        (0x1 << 16)           // Shifted mode PRSCH1 for TIMER_CC_CTRL
#define TIMER_CC_CTRL_PRSSEL_PRSCH2        (0x2 << 16)           // Shifted mode PRSCH2 for TIMER_CC_CTRL
#define TIMER_CC_CTRL_PRSSEL_PRSCH3        (0x3 << 16)           // Shifted mode PRSCH3 for TIMER_CC_CTRL

#define TIMER_CC_CTRL_INSEL              (0x1UL << 20)           // Input Selection

#define TIMER_CC_CTRL_FILT               (0x1UL << 21)           // Digital Filter

#define _TIMER_CC_CTRL_ICEDGE_MASK           0x3000000           // Bit mask for TIMER_ICEDGE
#define TIMER_CC_CTRL_ICEDGE_RISING                0x0           // Shifted mode RISING for TIMER_CC_CTRL
#define TIMER_CC_CTRL_ICEDGE_FALLING       (0x1 << 24)           // Shifted mode FALLING for TIMER_CC_CTRL
#define TIMER_CC_CTRL_ICEDGE_BOTH          (0x2 << 24)           // Shifted mode BOTH for TIMER_CC_CTRL
#define TIMER_CC_CTRL_ICEDGE_NONE          (0x3 << 24)           // Shifted mode NONE for TIMER_CC_CTRL

#define _TIMER_CC_CTRL_ICEVCTRL_MASK         0xC000000           // Bit mask for TIMER_ICEVCTRL
#define TIMER_CC_CTRL_ICEVCTRL_EVERYEDGE   (0x0 << 26)           // Shifted mode EVERYEDGE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_ICEVCTRL_EVERYSECONDEDGE (0x1 << 26)       // Shifted mode EVERYSECONDEDGE for TIMER_CC_CTRL
#define TIMER_CC_CTRL_ICEVCTRL_RISING      (0x2 << 26)           // Shifted mode RISING for TIMER_CC_CTRL
#define TIMER_CC_CTRL_ICEVCTRL_FALLING     (0x3 << 26)           // Shifted mode FALLING for TIMER_CC_CTRL

#define TIMER_CC_CTRL_PRSCONF            (0x1UL << 28)           // PRS Configuration


#define _TIMER_IF_MASK                     0x00000773UL          // Mask for TIMER_IF
#define TIMER_IF_OF                        (0x1UL << 0)          // Overflow Interrupt Flag
#define TIMER_IF_UF                        (0x1UL << 1)          // Underflow Interrupt Flag
#define TIMER_IF_CC0                       (0x1UL << 4)          // CC Channel 0 Interrupt Flag
#define TIMER_IF_CC1                       (0x1UL << 5)          // CC Channel 1 Interrupt Flag
#define TIMER_IF_CC2                       (0x1UL << 6)          // CC Channel 2 Interrupt Flag
#define TIMER_IF_ICBOF0                    (0x1UL << 8)          // CC Channel 0 Input Capture Buffer Overflow IF
#define TIMER_IF_ICBOF1                    (0x1UL << 9)          // CC Channel 1 Input Capture Buffer Overflow IF
#define TIMER_IF_ICBOF2                   (0x1UL << 10)          // CC Channel 2 Input Capture Buffer Overflow IF

#define TIMER_IEN_OF                       (0x1UL << 0)          // Overflow Interrupt Enable
#define TIMER_IEN_UF                       (0x1UL << 1)          // Underflow Interrupt Enable
#define TIMER_IEN_CC0                      (0x1UL << 4)          // CC Channel 0 Interrupt Enable
#define TIMER_IEN_CC1                      (0x1UL << 5)          // CC Channel 1 Interrupt Enable
#define TIMER_IEN_CC2                      (0x1UL << 6)          // CC Channel 2 Interrupt Enable
#define TIMER_IEN_ICBOF0                   (0x1UL << 8)          // CC Channel 0 Input Capture Buffer Overflow IE
#define TIMER_IEN_ICBOF1                   (0x1UL << 9)          // CC Channel 1 Input Capture Buffer Overflow IE
#define TIMER_IEN_ICBOF2                  (0x1UL << 10)          // CC Channel 2 Input Capture Buffer Overflow IE

#define TIMER_ROUTE_CC0PEN                 (0x1UL << 0)          // CC Channel 0 Pin Enable
#define TIMER_ROUTE_CC1PEN                 (0x1UL << 1)          // CC Channel 1 Pin Enable
#define TIMER_ROUTE_CC2PEN                 (0x1UL << 2)          // CC Channel 2 Pin Enable
#define _TIMER_ROUTE_LOCATION_MASK            0x70000UL          // Bit mask for TIMER_LOCATION
#define TIMER_ROUTE_LOCATION_LOC0           (0x0 << 16)          // Shifted mode LOC0 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC1           (0x1 << 16)          // Shifted mode LOC1 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC2           (0x2 << 16)          // Shifted mode LOC2 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC3           (0x3 << 16)          // Shifted mode LOC3 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC4           (0x4 << 16)          // Shifted mode LOC4 for TIMER_ROUTE
#define TIMER_ROUTE_LOCATION_LOC5           (0x5 << 16)          // Shifted mode LOC5 for TIMER_ROUTE

// Variant stuff:

#define MS_PRESCALE_8  2625
#define US_PRESCALE_1    21
#define PULSE_INC      1024

struct timer_counter {
  TIMER_TypeDef *ptr;
  int index;
  volatile uint32_t *wake;
  IRQn_Type IRQn;
};

enum timer_req {
  REQ_TIMER,
  REQ_TIMER0,
  REQ_TIMER1
};

class TimersLP
{
 public:
  TimersLP();
  void delay_ms(uint32_t);
  void delay_us(uint32_t);
  uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout);
  void tone(uint32_t outputPin, uint32_t frequency, uint32_t duration = 0);
  void noTone (uint32_t pin);
  void analogWrite(uint32_t ulPin, uint32_t ulValue, uint32_t prescale=7);
  void noPWM(uint32_t pin);
  uint32_t get_counter_value(int);
  uint32_t get_timer_frequency(void);
  volatile static uint32_t timer0_wake;
  volatile static uint32_t timer1_wake;
  static void (*isr0Callback)();
  static void (*isr1Callback)();
  void disable(int timer);
  uint32_t tone_active(uint8_t pin);
  static bool timer0_free;
  static bool timer1_free;

 private:
  timer_counter enable(void (*isr)(), uint8_t timer_req);
  static uint32_t timer_freq;
};

void wake_only(void);
void tone0_isr(void);
void tone1_isr(void);
uint32_t get_toggle_count0(void);
uint32_t get_toggle_count1(void);
uint32_t get_isr_count(void);

// Library stuff:



#ifdef __cplusplus
extern "C"{

  // Timer modes

  // Measures the length in microseconds of a pulse on the pin
  // state if HIGH measures a positive going pulse
  // if LOW a negative pulse.
  //  --TODO-- Need to characterize start up time
  uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout);


  // Provides a version of pulseIn with a default argument (C++ only)
  uint32_t pulseIn(uint32_t pin, uint32_t state, uint32_t timeout = 1000000L);

  void print_timer_regs(int timer);
} // extern "C"

#endif

#endif /* _TIMERLP_ */
