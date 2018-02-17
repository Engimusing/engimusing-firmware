///
///@file efm_gpio.h
///@brief Header redirect for em_gpio and a few gpio related defines used by the Engimusing Arduino IDE Libraries
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

#include "./emlib/inc/em_gpio.h"

#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3
#define PORTE    4
#define PORTF    5

#define RISING     (0x2)
#define CHANGE     (0x3)
#define FALLING    (0x4)


#define GPIO_MODE_MASK                                          0x0000000FUL  // BIT MASK
#define GPIO_MODE_DISABLED                                      0x00000000UL  // DISABLED
#define GPIO_MODE_INPUT                                         0x00000001UL  // INPUT
#define GPIO_MODE_INPUTPULL                                     0x00000002UL  // INPUTPULL
#define GPIO_MODE_INPUTPULLFILTER                               0x00000003UL  // INPUTPULLFILTER
#define GPIO_MODE_PUSHPULL                                      0x00000004UL  // PUSHPULL
#define GPIO_MODE_PUSHPULLDRIVE                                 0x00000005UL  // PUSHPULLDRIVE
#define GPIO_MODE_WIREDOR                                       0x00000006UL  // WIREDOR
#define GPIO_MODE_WIREDORPULLDOWN                               0x00000007UL  // WIREDORPULLDOWN
#define GPIO_MODE_WIREDAND                                      0x00000008UL  // WIREDAND
#define GPIO_MODE_WIREDANDFILTER                                0x00000009UL  // WIREDANDFILTER
#define GPIO_MODE_WIREDANDPULLUP                                0x0000000AUL  // WIREDANDPULLUP
#define GPIO_MODE_WIREDANDPULLUPFILTER                          0x0000000BUL  // WIREDANDPULLUPFILTER
#define GPIO_MODE_WIREDANDDRIVE                                 0x0000000CUL  // WIREDANDDRIVE
#define GPIO_MODE_WIREDANDDRIVEFILTER                           0x0000000DUL  // WIREDANDDRIVEFILTER
#define GPIO_MODE_WIREDANDDRIVEPULLUP                           0x0000000EUL  // WIREDANDDRIVEPULLUP
#define GPIO_MODE_WIREDANDDRIVEPULLUPFILTER                     0x0000000FUL  // WIREDANDDRIVEPULLUPFILTER

#define DRIVEMODE_STANDARD                                      0x00000000UL
#define DRIVEMODE_LOWEST                                        0x00000001UL
#define DRIVEMODE_HIGH                                          0x00000002UL
#define DRIVEMODE_LOW                                           0x00000003UL

// Unused code below. Can probably be removed. Next time I clean up this file I will remove it.
#if 0

#include "io_types.h"


// GPIO ports identificator
typedef enum
{
  gpioPortA = 0, // Port A
  gpioPortB = 1, // Port B
  gpioPortC = 2, // Port C
  gpioPortD = 3, // Port D
  gpioPortE = 4, // Port E
  gpioPortF = 5  // Port F
} GPIO_Port_TypeDef;


// GPIO Port Typedef
typedef struct
{
  __IO uint32_t CTRL;     // Port Control Register
  __IO uint32_t MODEL;    // Port Pin Mode Low Register
  __IO uint32_t MODEH;    // Port Pin Mode High Register
  __IO uint32_t DOUT;     // Port Data Out Register
  __O uint32_t  DOUTSET;  // Port Data Out Set Register
  __O uint32_t  DOUTCLR;  // Port Data Out Clear Register
  __O uint32_t  DOUTTGL;  // Port Data Out Toggle Register
  __I uint32_t  DIN;      // Port Data In Register
  __IO uint32_t PINLOCKN; // Port Unlocked Pins Register
} GPIO_P_TypeDef;


typedef struct
{
  GPIO_P_TypeDef P[6];          // Port configuration bits 

  uint32_t       RESERVED0[10]; // Reserved for future use
  __IO uint32_t  EXTIPSELL;     // External Interrupt Port Select Low Register
  __IO uint32_t  EXTIPSELH;     // External Interrupt Port Select High Register
  __IO uint32_t  EXTIRISE;      // External Interrupt Rising Edge Trigger Register
  __IO uint32_t  EXTIFALL;      // External Interrupt Falling Edge Trigger Register
  __IO uint32_t  IEN;           // Interrupt Enable Register
  __I uint32_t   IF;            // Interrupt Flag Register
  __IO uint32_t  IFS;           // Interrupt Flag Set Register
  __IO uint32_t  IFC;           // Interrupt Flag Clear Register
  __IO uint32_t  ROUTE;         // I/O Routing Register
  __IO uint32_t  INSENSE;       // Input Sense Register
  __IO uint32_t  LOCK;          // Configuration Lock Register
  __IO uint32_t  CTRL;          // GPIO Control Register
  __IO uint32_t  CMD;           // GPIO Command Register
  __IO uint32_t  EM4WUEN;       // EM4 Wake-up Enable Register
  __IO uint32_t  EM4WUPOL;      // EM4 Wake-up Polarity Register
  __I uint32_t   EM4WUCAUSE;    // EM4 Wake-up Cause Register
} GPIO_TypeDef;



// GPIO Pin Mode
typedef enum
{
  gpioModeDisabled                  = 0x00000000UL, // Input disabled. Pullup if DOUT is set
  gpioModeInput                     = 0x00000001UL, // Input enabled. Filter if DOUT is set
  gpioModeInputPull                 = 0x00000002UL, // Input enabled. DOUT determines pull direction
  gpioModeInputPullFilter           = 0x00000003UL, // Input enabled with filter. DOUT determines pull direction
  gpioModePushPull                  = 0x00000004UL, // Push-pull output
  gpioModePushPullDrive             = 0x00000005UL, // Push-pull output with drive-strength set by DRIVEMODE
  gpioModeWiredOr                   = 0x00000006UL, // Wired-or output
  gpioModeWiredOrPullDown           = 0x00000007UL, // Wired-or output with pull-down
  gpioModeWiredAnd                  = 0x00000008UL, // Open-drain output
  gpioModeWiredAndFilter            = 0x00000009UL, // Open-drain output with filter
  gpioModeWiredAndPullUp            = 0x0000000AUL, // Open-drain output with pullup
  gpioModeWiredAndPullUpFilter      = 0x0000000BUL, // Open-drain output with filter and pullup
  gpioModeWiredAndDrive             = 0x0000000CUL, // Open-drain output drive-strength set by DRIVEMODE
  gpioModeWiredAndDriveFilter       = 0x0000000DUL, // Open-drain output with filter drive-strength set by DRIVEMODE
  gpioModeWiredAndDrivePullUp       = 0x0000000EUL, // Open-drain output with pullup drive-strength set by DRIVEMODE
  gpioModeWiredAndDrivePullUpFilter = 0x0000000FUL  // Open-drain output with filter, pullup drive-strength set by DRIVEMODE
} GPIO_Mode_TypeDef;

// GPIO drive mode
typedef enum
{
  gpioDriveModeStandard = 0x00000000UL, // Default 6mA
  gpioDriveModeLowest   = 0x00000001UL, // 0.5 mA
  gpioDriveModeHigh     = 0x00000002UL, // 20 mA
  gpioDriveModeLow      = 0x00000003UL  // 2 mA
} GPIO_DriveMode_TypeDef;


#define GPIO         ((GPIO_TypeDef *) 0x40006000UL) // GPIO base address

#define GPIO_UNLOCK_CODE                        0xA534        // GPIO unlock code

#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3
#define PORTE    4
#define PORTF    5

#define RISING     (0x2)
#define CHANGE     (0x3)
#define FALLING    (0x4)

#define GPIO_MODE_MASK                                          0x0000000FUL  // BIT MASK
#define GPIO_MODE_DISABLED                                      0x00000000UL  // DISABLED
#define GPIO_MODE_INPUT                                         0x00000001UL  // INPUT
#define GPIO_MODE_INPUTPULL                                     0x00000002UL  // INPUTPULL
#define GPIO_MODE_INPUTPULLFILTER                               0x00000003UL  // INPUTPULLFILTER
#define GPIO_MODE_PUSHPULL                                      0x00000004UL  // PUSHPULL
#define GPIO_MODE_PUSHPULLDRIVE                                 0x00000005UL  // PUSHPULLDRIVE
#define GPIO_MODE_WIREDOR                                       0x00000006UL  // WIREDOR
#define GPIO_MODE_WIREDORPULLDOWN                               0x00000007UL  // WIREDORPULLDOWN
#define GPIO_MODE_WIREDAND                                      0x00000008UL  // WIREDAND
#define GPIO_MODE_WIREDANDFILTER                                0x00000009UL  // WIREDANDFILTER
#define GPIO_MODE_WIREDANDPULLUP                                0x0000000AUL  // WIREDANDPULLUP
#define GPIO_MODE_WIREDANDPULLUPFILTER                          0x0000000BUL  // WIREDANDPULLUPFILTER
#define GPIO_MODE_WIREDANDDRIVE                                 0x0000000CUL  // WIREDANDDRIVE
#define GPIO_MODE_WIREDANDDRIVEFILTER                           0x0000000DUL  // WIREDANDDRIVEFILTER
#define GPIO_MODE_WIREDANDDRIVEPULLUP                           0x0000000EUL  // WIREDANDDRIVEPULLUP
#define GPIO_MODE_WIREDANDDRIVEPULLUPFILTER                     0x0000000FUL  // WIREDANDDRIVEPULLUPFILTER

#define DRIVEMODE_STANDARD                                      0x00000000UL
#define DRIVEMODE_LOWEST                                        0x00000001UL
#define DRIVEMODE_HIGH                                          0x00000002UL
#define DRIVEMODE_LOW                                           0x00000003UL

// ---------------------------------------------------------------------------------------

// Bit fields for GPIO P_CTRL
#define _GPIO_P_CTRL_DRIVEMODE_MASK                                    0x3UL  // Bit mask for GPIO_DRIVEMODE
#define GPIO_P_CTRL_DRIVEMODE_DEFAULT                           0x00000000UL  // Mode DEFAULT for GPIO_P_CTRL
#define GPIO_P_CTRL_DRIVEMODE_STANDARD                          0x00000000UL  // Mode STANDARD for GPIO_P_CTRL
#define GPIO_P_CTRL_DRIVEMODE_LOWEST                            0x00000001UL  // Mode LOWEST for GPIO_P_CTRL
#define GPIO_P_CTRL_DRIVEMODE_HIGH                              0x00000002UL  // Mode HIGH for GPIO_P_CTRL
#define GPIO_P_CTRL_DRIVEMODE_LOW                               0x00000003UL  // Mode LOW for GPIO_P_CTRL


// Bit fields for GPIO P_MODEL
#define GPIO_P_MODEL_MODE0_MASK                                        0xFUL  // Bit mask for GPIO_MODE0
#define GPIO_P_MODEL_MODE0_DEFAULT                              0x00000000UL  // Mode DEFAULT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_DISABLED                             0x00000000UL  // Mode DISABLED for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_INPUT                                0x00000001UL  // Mode INPUT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_INPUTPULL                            0x00000002UL  // Mode INPUTPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_INPUTPULLFILTER                      0x00000003UL  // Mode INPUTPULLFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_PUSHPULL                             0x00000004UL  // Mode PUSHPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_PUSHPULLDRIVE                        0x00000005UL  // Mode PUSHPULLDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDOR                              0x00000006UL  // Mode WIREDOR for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDORPULLDOWN                      0x00000007UL  // Mode WIREDORPULLDOWN for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDAND                             0x00000008UL  // Mode WIREDAND for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDANDFILTER                       0x00000009UL  // Mode WIREDANDFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDANDPULLUP                       0x0000000AUL  // Mode WIREDANDPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER                 0x0000000BUL  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDANDDRIVE                        0x0000000CUL  // Mode WIREDANDDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDANDDRIVEFILTER                  0x0000000DUL  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDANDDRIVEPULLUP                  0x0000000EUL  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE0_WIREDANDDRIVEPULLUPFILTER            0x0000000FUL  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEL

#define GPIO_P_MODEL_MODE1_MASK                                       0xF0UL  // Bit mask for GPIO_MODE1
#define GPIO_P_MODEL_MODE1_DEFAULT                       (0x00000000UL << 4)  // Mode DEFAULT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_DISABLED                      (0x00000000UL << 4)  // Mode DISABLED for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_INPUT                         (0x00000001UL << 4)  // Mode INPUT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_INPUTPULL                     (0x00000002UL << 4)  // Mode INPUTPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_INPUTPULLFILTER               (0x00000003UL << 4)  // Mode INPUTPULLFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_PUSHPULL                      (0x00000004UL << 4)  // Mode PUSHPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_PUSHPULLDRIVE                 (0x00000005UL << 4)  // Mode PUSHPULLDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDOR                       (0x00000006UL << 4)  // Mode WIREDOR for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDORPULLDOWN               (0x00000007UL << 4)  // Mode WIREDORPULLDOWN for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDAND                      (0x00000008UL << 4)  // Mode WIREDAND for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDANDFILTER                (0x00000009UL << 4)  // Mode WIREDANDFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDANDPULLUP                (0x0000000AUL << 4)  // Mode WIREDANDPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDANDPULLUPFILTER          (0x0000000BUL << 4)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDANDDRIVE                 (0x0000000CUL << 4)  // Mode WIREDANDDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDANDDRIVEFILTER           (0x0000000DUL << 4)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDANDDRIVEPULLUP           (0x0000000EUL << 4)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE1_WIREDANDDRIVEPULLUPFILTER     (0x0000000FUL << 4)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEL


#define GPIO_P_MODEL_MODE2_MASK                                      0xF00UL  // Bit mask for GPIO_MODE2
#define GPIO_P_MODEL_MODE2_DEFAULT                       (0x00000000UL << 8)  // Mode DEFAULT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_DISABLED                      (0x00000000UL << 8)  // Mode DISABLED for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_INPUT                         (0x00000001UL << 8)  // Mode INPUT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_INPUTPULL                     (0x00000002UL << 8)  // Mode INPUTPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_INPUTPULLFILTER               (0x00000003UL << 8)  // Mode INPUTPULLFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_PUSHPULL                      (0x00000004UL << 8)  // Mode PUSHPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_PUSHPULLDRIVE                 (0x00000005UL << 8)  // Mode PUSHPULLDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDOR                       (0x00000006UL << 8)  // Mode WIREDOR for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDORPULLDOWN               (0x00000007UL << 8)  // Mode WIREDORPULLDOWN for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDAND                      (0x00000008UL << 8)  // Mode WIREDAND for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDANDFILTER                (0x00000009UL << 8)  // Mode WIREDANDFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDANDPULLUP                (0x0000000AUL << 8)  // Mode WIREDANDPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDANDPULLUPFILTER          (0x0000000BUL << 8)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDANDDRIVE                 (0x0000000CUL << 8)  // Mode WIREDANDDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDANDDRIVEFILTER           (0x0000000DUL << 8)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDANDDRIVEPULLUP           (0x0000000EUL << 8)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE2_WIREDANDDRIVEPULLUPFILTER     (0x0000000FUL << 8)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEL

#define GPIO_P_MODEL_MODE3_MASK                                     0xF000UL  // Bit mask for GPIO_MODE3
#define GPIO_P_MODEL_MODE3_DEFAULT                      (0x00000000UL << 12)  // Mode DEFAULT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_DISABLED                     (0x00000000UL << 12)  // Mode DISABLED for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_INPUT                        (0x00000001UL << 12)  // Mode INPUT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_INPUTPULL                    (0x00000002UL << 12)  // Mode INPUTPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_INPUTPULLFILTER              (0x00000003UL << 12)  // Mode INPUTPULLFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_PUSHPULL                     (0x00000004UL << 12)  // Mode PUSHPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_PUSHPULLDRIVE                (0x00000005UL << 12)  // Mode PUSHPULLDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDOR                      (0x00000006UL << 12)  // Mode WIREDOR for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDORPULLDOWN              (0x00000007UL << 12)  // Mode WIREDORPULLDOWN for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDAND                     (0x00000008UL << 12)  // Mode WIREDAND for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDANDFILTER               (0x00000009UL << 12)  // Mode WIREDANDFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDANDPULLUP               (0x0000000AUL << 12)  // Mode WIREDANDPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDANDPULLUPFILTER         (0x0000000BUL << 12)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDANDDRIVE                (0x0000000CUL << 12)  // Mode WIREDANDDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDANDDRIVEFILTER          (0x0000000DUL << 12)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDANDDRIVEPULLUP          (0x0000000EUL << 12)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE3_WIREDANDDRIVEPULLUPFILTER    (0x0000000FUL << 12)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEL

#define GPIO_P_MODEL_MODE4_MASK                                    0xF0000UL  // Bit mask for GPIO_MODE4
#define GPIO_P_MODEL_MODE4_DEFAULT                      (0x00000000UL << 16)  // Mode DEFAULT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_DISABLED                     (0x00000000UL << 16)  // Mode DISABLED for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_INPUT                        (0x00000001UL << 16)  // Mode INPUT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_INPUTPULL                    (0x00000002UL << 16)  // Mode INPUTPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_INPUTPULLFILTER              (0x00000003UL << 16)  // Mode INPUTPULLFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_PUSHPULL                     (0x00000004UL << 16)  // Mode PUSHPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_PUSHPULLDRIVE                (0x00000005UL << 16)  // Mode PUSHPULLDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDOR                      (0x00000006UL << 16)  // Mode WIREDOR for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDORPULLDOWN              (0x00000007UL << 16)  // Mode WIREDORPULLDOWN for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDAND                     (0x00000008UL << 16)  // Mode WIREDAND for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDANDFILTER               (0x00000009UL << 16)  // Mode WIREDANDFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDANDPULLUP               (0x0000000AUL << 16)  // Mode WIREDANDPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDANDPULLUPFILTER         (0x0000000BUL << 16)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDANDDRIVE                (0x0000000CUL << 16)  // Mode WIREDANDDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDANDDRIVEFILTER          (0x0000000DUL << 16)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDANDDRIVEPULLUP          (0x0000000EUL << 16)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE4_WIREDANDDRIVEPULLUPFILTER    (0x0000000FUL << 16)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEL

#define GPIO_P_MODEL_MODE5_MASK                                   0xF00000UL  // Bit mask for GPIO_MODE5
#define GPIO_P_MODEL_MODE5_DEFAULT                      (0x00000000UL << 20)  // Mode DEFAULT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_DISABLED                     (0x00000000UL << 20)  // Mode DISABLED for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_INPUT                        (0x00000001UL << 20)  // Mode INPUT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_INPUTPULL                    (0x00000002UL << 20)  // Mode INPUTPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_INPUTPULLFILTER              (0x00000003UL << 20)  // Mode INPUTPULLFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_PUSHPULL                     (0x00000004UL << 20)  // Mode PUSHPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_PUSHPULLDRIVE                (0x00000005UL << 20)  // Mode PUSHPULLDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDOR                      (0x00000006UL << 20)  // Mode WIREDOR for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDORPULLDOWN              (0x00000007UL << 20)  // Mode WIREDORPULLDOWN for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDAND                     (0x00000008UL << 20)  // Mode WIREDAND for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDANDFILTER               (0x00000009UL << 20)  // Mode WIREDANDFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDANDPULLUP               (0x0000000AUL << 20)  // Mode WIREDANDPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDANDPULLUPFILTER         (0x0000000BUL << 20)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDANDDRIVE                (0x0000000CUL << 20)  // Mode WIREDANDDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDANDDRIVEFILTER          (0x0000000DUL << 20)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDANDDRIVEPULLUP          (0x0000000EUL << 20)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE5_WIREDANDDRIVEPULLUPFILTER    (0x0000000FUL << 20)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEL

#define GPIO_P_MODEL_MODE6_MASK                                  0xF000000UL  // Bit mask for GPIO_MODE6
#define GPIO_P_MODEL_MODE6_DEFAULT                      (0x00000000UL << 24)  // Mode DEFAULT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_DISABLED                     (0x00000000UL << 24)  // Mode DISABLED for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_INPUT                        (0x00000001UL << 24)  // Mode INPUT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_INPUTPULL                    (0x00000002UL << 24)  // Mode INPUTPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_INPUTPULLFILTER              (0x00000003UL << 24)  // Mode INPUTPULLFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_PUSHPULL                     (0x00000004UL << 24)  // Mode PUSHPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_PUSHPULLDRIVE                (0x00000005UL << 24)  // Mode PUSHPULLDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDOR                      (0x00000006UL << 24)  // Mode WIREDOR for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDORPULLDOWN              (0x00000007UL << 24)  // Mode WIREDORPULLDOWN for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDAND                     (0x00000008UL << 24)  // Mode WIREDAND for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDANDFILTER               (0x00000009UL << 24)  // Mode WIREDANDFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDANDPULLUP               (0x0000000AUL << 24)  // Mode WIREDANDPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDANDPULLUPFILTER         (0x0000000BUL << 24)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDANDDRIVE                (0x0000000CUL << 24)  // Mode WIREDANDDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDANDDRIVEFILTER          (0x0000000DUL << 24)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDANDDRIVEPULLUP          (0x0000000EUL << 24)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE6_WIREDANDDRIVEPULLUPFILTER    (0x0000000FUL << 24)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEL

#define GPIO_P_MODEL_MODE7_MASK                         (0xF0000000UL << 28)  // Bit mask for GPIO_MODE7
#define GPIO_P_MODEL_MODE7_DEFAULT                      (0x00000000UL << 28)  // Mode DEFAULT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_DISABLED                     (0x00000000UL << 28)  // Mode DISABLED for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_INPUT                        (0x00000001UL << 28)  // Mode INPUT for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_INPUTPULL                    (0x00000002UL << 28)  // Mode INPUTPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_INPUTPULLFILTER              (0x00000003UL << 28)  // Mode INPUTPULLFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_PUSHPULL                     (0x00000004UL << 28)  // Mode PUSHPULL for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_PUSHPULLDRIVE                (0x00000005UL << 28)  // Mode PUSHPULLDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDOR                      (0x00000006UL << 28)  // Mode WIREDOR for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDORPULLDOWN              (0x00000007UL << 28)  // Mode WIREDORPULLDOWN for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDAND                     (0x00000008UL << 28)  // Mode WIREDAND for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDANDFILTER               (0x00000009UL << 28)  // Mode WIREDANDFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDANDPULLUP               (0x0000000AUL << 28)  // Mode WIREDANDPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDANDPULLUPFILTER         (0x0000000BUL << 28)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDANDDRIVE                (0x0000000CUL << 28)  // Mode WIREDANDDRIVE for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDANDDRIVEFILTER          (0x0000000DUL << 28)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDANDDRIVEPULLUP          (0x0000000EUL << 28)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEL
#define GPIO_P_MODEL_MODE7_WIREDANDDRIVEPULLUPFILTER    (0x0000000FUL << 28)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEL

// Bit fields for GPIO P_MODEH
#define GPIO_P_MODEH_MODE8_MASK                                        0xFUL  // Bit mask for GPIO_MODE8
#define GPIO_P_MODEH_MODE8_DEFAULT                              0x00000000UL  // Mode DEFAULT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_DISABLED                             0x00000000UL  // Mode DISABLED for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_INPUT                                0x00000001UL  // Mode INPUT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_INPUTPULL                            0x00000002UL  // Mode INPUTPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_INPUTPULLFILTER                      0x00000003UL  // Mode INPUTPULLFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_PUSHPULL                             0x00000004UL  // Mode PUSHPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_PUSHPULLDRIVE                        0x00000005UL  // Mode PUSHPULLDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDOR                              0x00000006UL  // Mode WIREDOR for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDORPULLDOWN                      0x00000007UL  // Mode WIREDORPULLDOWN for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDAND                             0x00000008UL  // Mode WIREDAND for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDANDFILTER                       0x00000009UL  // Mode WIREDANDFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDANDPULLUP                       0x0000000AUL  // Mode WIREDANDPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDANDPULLUPFILTER                 0x0000000BUL  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDANDDRIVE                        0x0000000CUL  // Mode WIREDANDDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDANDDRIVEFILTER                  0x0000000DUL  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDANDDRIVEPULLUP                  0x0000000EUL  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE8_WIREDANDDRIVEPULLUPFILTER            0x0000000FUL  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEH

#define GPIO_P_MODEH_MODE9_MASK                                       0xF0UL  // Bit mask for GPIO_MODE9
#define GPIO_P_MODEH_MODE9_DEFAULT                       (0x00000000UL << 4)  // Mode DEFAULT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_DISABLED                      (0x00000000UL << 4)  // Mode DISABLED for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_INPUT                         (0x00000001UL << 4)  // Mode INPUT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_INPUTPULL                     (0x00000002UL << 4)  // Mode INPUTPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_INPUTPULLFILTER               (0x00000003UL << 4)  // Mode INPUTPULLFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_PUSHPULL                      (0x00000004UL << 4)  // Mode PUSHPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_PUSHPULLDRIVE                 (0x00000005UL << 4)  // Mode PUSHPULLDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDOR                       (0x00000006UL << 4)  // Mode WIREDOR for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDORPULLDOWN               (0x00000007UL << 4)  // Mode WIREDORPULLDOWN for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDAND                      (0x00000008UL << 4)  // Mode WIREDAND for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDANDFILTER                (0x00000009UL << 4)  // Mode WIREDANDFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDANDPULLUP                (0x0000000AUL << 4)  // Mode WIREDANDPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDANDPULLUPFILTER          (0x0000000BUL << 4)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDANDDRIVE                 (0x0000000CUL << 4)  // Mode WIREDANDDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDANDDRIVEFILTER           (0x0000000DUL << 4)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDANDDRIVEPULLUP           (0x0000000EUL << 4)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE9_WIREDANDDRIVEPULLUPFILTER     (0x0000000FUL << 4)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEH

#define GPIO_P_MODEH_MODE10_MASK                                     0xF00UL  // Bit mask for GPIO_MODE10
#define GPIO_P_MODEH_MODE10_DEFAULT                      (0x00000000UL << 8)  // Mode DEFAULT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_DISABLED                     (0x00000000UL << 8)  // Mode DISABLED for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_INPUT                        (0x00000001UL << 8)  // Mode INPUT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_INPUTPULL                    (0x00000002UL << 8)  // Mode INPUTPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_INPUTPULLFILTER              (0x00000003UL << 8)  // Mode INPUTPULLFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_PUSHPULL                     (0x00000004UL << 8)  // Mode PUSHPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_PUSHPULLDRIVE                (0x00000005UL << 8)  // Mode PUSHPULLDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDOR                      (0x00000006UL << 8)  // Mode WIREDOR for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDORPULLDOWN              (0x00000007UL << 8)  // Mode WIREDORPULLDOWN for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDAND                     (0x00000008UL << 8)  // Mode WIREDAND for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDANDFILTER               (0x00000009UL << 8)  // Mode WIREDANDFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDANDPULLUP               (0x0000000AUL << 8)  // Mode WIREDANDPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDANDPULLUPFILTER         (0x0000000BUL << 8)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDANDDRIVE                (0x0000000CUL << 8)  // Mode WIREDANDDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDANDDRIVEFILTER          (0x0000000DUL << 8)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDANDDRIVEPULLUP          (0x0000000EUL << 8)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE10_WIREDANDDRIVEPULLUPFILTER    (0x0000000FUL << 8)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEH

#define GPIO_P_MODEH_MODE11_MASK                                    0xF000UL  // Bit mask for GPIO_MODE11
#define GPIO_P_MODEH_MODE11_DEFAULT                     (0x00000000UL << 12)  // Mode DEFAULT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_DISABLED                    (0x00000000UL << 12)  // Mode DISABLED for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_INPUT                       (0x00000001UL << 12)  // Mode INPUT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_INPUTPULL                   (0x00000002UL << 12)  // Mode INPUTPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_INPUTPULLFILTER             (0x00000003UL << 12)  // Mode INPUTPULLFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_PUSHPULL                    (0x00000004UL << 12)  // Mode PUSHPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_PUSHPULLDRIVE               (0x00000005UL << 12)  // Mode PUSHPULLDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDOR                     (0x00000006UL << 12)  // Mode WIREDOR for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDORPULLDOWN             (0x00000007UL << 12)  // Mode WIREDORPULLDOWN for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDAND                    (0x00000008UL << 12)  // Mode WIREDAND for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDANDFILTER              (0x00000009UL << 12)  // Mode WIREDANDFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDANDPULLUP              (0x0000000AUL << 12)  // Mode WIREDANDPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDANDPULLUPFILTER        (0x0000000BUL << 12)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDANDDRIVE               (0x0000000CUL << 12)  // Mode WIREDANDDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDANDDRIVEFILTER         (0x0000000DUL << 12)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDANDDRIVEPULLUP         (0x0000000EUL << 12)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE11_WIREDANDDRIVEPULLUPFILTER   (0x0000000FUL << 12)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEH

#define GPIO_P_MODEH_MODE12_MASK                                   0xF0000UL  // Bit mask for GPIO_MODE12
#define GPIO_P_MODEH_MODE12_DEFAULT                     (0x00000000UL << 16)  // Mode DEFAULT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_DISABLED                    (0x00000000UL << 16)  // Mode DISABLED for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_INPUT                       (0x00000001UL << 16)  // Mode INPUT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_INPUTPULL                   (0x00000002UL << 16)  // Mode INPUTPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_INPUTPULLFILTER             (0x00000003UL << 16)  // Mode INPUTPULLFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_PUSHPULL                    (0x00000004UL << 16)  // Mode PUSHPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_PUSHPULLDRIVE               (0x00000005UL << 16)  // Mode PUSHPULLDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDOR                     (0x00000006UL << 16)  // Mode WIREDOR for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDORPULLDOWN             (0x00000007UL << 16)  // Mode WIREDORPULLDOWN for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDAND                    (0x00000008UL << 16)  // Mode WIREDAND for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDANDFILTER              (0x00000009UL << 16)  // Mode WIREDANDFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDANDPULLUP              (0x0000000AUL << 16)  // Mode WIREDANDPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDANDPULLUPFILTER        (0x0000000BUL << 16)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDANDDRIVE               (0x0000000CUL << 16)  // Mode WIREDANDDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDANDDRIVEFILTER         (0x0000000DUL << 16)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDANDDRIVEPULLUP         (0x0000000EUL << 16)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE12_WIREDANDDRIVEPULLUPFILTER   (0x0000000FUL << 16)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEH

#define GPIO_P_MODEH_MODE13_MASK                                  0xF00000UL  // Bit mask for GPIO_MODE13
#define GPIO_P_MODEH_MODE13_DEFAULT                     (0x00000000UL << 20)  // Mode DEFAULT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_DISABLED                    (0x00000000UL << 20)  // Mode DISABLED for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_INPUT                       (0x00000001UL << 20)  // Mode INPUT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_INPUTPULL                   (0x00000002UL << 20)  // Mode INPUTPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_INPUTPULLFILTER             (0x00000003UL << 20)  // Mode INPUTPULLFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_PUSHPULL                    (0x00000004UL << 20)  // Mode PUSHPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_PUSHPULLDRIVE               (0x00000005UL << 20)  // Mode PUSHPULLDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDOR                     (0x00000006UL << 20)  // Mode WIREDOR for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDORPULLDOWN             (0x00000007UL << 20)  // Mode WIREDORPULLDOWN for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDAND                    (0x00000008UL << 20)  // Mode WIREDAND for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDANDFILTER              (0x00000009UL << 20)  // Mode WIREDANDFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDANDPULLUP              (0x0000000AUL << 20)  // Mode WIREDANDPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDANDPULLUPFILTER        (0x0000000BUL << 20)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDANDDRIVE               (0x0000000CUL << 20)  // Mode WIREDANDDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDANDDRIVEFILTER         (0x0000000DUL << 20)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDANDDRIVEPULLUP         (0x0000000EUL << 20)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE13_WIREDANDDRIVEPULLUPFILTER   (0x0000000FUL << 20)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEH

#define GPIO_P_MODEH_MODE14_MASK                                 0xF000000UL  // Bit mask for GPIO_MODE14
#define GPIO_P_MODEH_MODE14_DEFAULT                     (0x00000000UL << 24)  // Mode DEFAULT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_DISABLED                    (0x00000000UL << 24)  // Mode DISABLED for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_INPUT                       (0x00000001UL << 24)  // Mode INPUT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_INPUTPULL                   (0x00000002UL << 24)  // Mode INPUTPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_INPUTPULLFILTER             (0x00000003UL << 24)  // Mode INPUTPULLFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_PUSHPULL                    (0x00000004UL << 24)  // Mode PUSHPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_PUSHPULLDRIVE               (0x00000005UL << 24)  // Mode PUSHPULLDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDOR                     (0x00000006UL << 24)  // Mode WIREDOR for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDORPULLDOWN             (0x00000007UL << 24)  // Mode WIREDORPULLDOWN for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDAND                    (0x00000008UL << 24)  // Mode WIREDAND for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDANDFILTER              (0x00000009UL << 24)  // Mode WIREDANDFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDANDPULLUP              (0x0000000AUL << 24)  // Mode WIREDANDPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDANDPULLUPFILTER        (0x0000000BUL << 24)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDANDDRIVE               (0x0000000CUL << 24)  // Mode WIREDANDDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDANDDRIVEFILTER         (0x0000000DUL << 24)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDANDDRIVEPULLUP         (0x0000000EUL << 24)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE14_WIREDANDDRIVEPULLUPFILTER   (0x0000000FUL << 24)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEH

#define GPIO_P_MODEH_MODE15_MASK                                0xF0000000UL  // Bit mask for GPIO_MODE15
#define GPIO_P_MODEH_MODE15_DEFAULT                     (0x00000000UL << 28)  // Mode DEFAULT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_DISABLED                    (0x00000000UL << 28)  // Mode DISABLED for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_INPUT                       (0x00000001UL << 28)  // Mode INPUT for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_INPUTPULL                   (0x00000002UL << 28)  // Mode INPUTPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_INPUTPULLFILTER             (0x00000003UL << 28)  // Mode INPUTPULLFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_PUSHPULL                    (0x00000004UL << 28)  // Mode PUSHPULL for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_PUSHPULLDRIVE               (0x00000005UL << 28)  // Mode PUSHPULLDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDOR                     (0x00000006UL << 28)  // Mode WIREDOR for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDORPULLDOWN             (0x00000007UL << 28)  // Mode WIREDORPULLDOWN for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDAND                    (0x00000008UL << 28)  // Mode WIREDAND for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDANDFILTER              (0x00000009UL << 28)  // Mode WIREDANDFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDANDPULLUP              (0x0000000AUL << 28)  // Mode WIREDANDPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDANDPULLUPFILTER        (0x0000000BUL << 28)  // Mode WIREDANDPULLUPFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDANDDRIVE               (0x0000000CUL << 28)  // Mode WIREDANDDRIVE for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDANDDRIVEFILTER         (0x0000000DUL << 28)  // Mode WIREDANDDRIVEFILTER for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDANDDRIVEPULLUP         (0x0000000EUL << 28)  // Mode WIREDANDDRIVEPULLUP for GPIO_P_MODEH
#define GPIO_P_MODEH_MODE15_WIREDANDDRIVEPULLUPFILTER   (0x0000000FUL << 28)  // Mode WIREDANDDRIVEPULLUPFILTER for GPIO_P_MODEH

// Bit fields for GPIO P_DOUT
#define GPIO_P_DOUT_RESETVALUE                                  0x00000000UL  // Default value for GPIO_P_DOUT
#define GPIO_P_DOUT_MASK                                        0x0000FFFFUL  // Mask for GPIO_P_DOUT
#define GPIO_P_DOUT_DOUT_SHIFT                                             0  // Shift value for GPIO_DOUT
#define GPIO_P_DOUT_DOUT_MASK                                       0xFFFFUL  // Bit mask for GPIO_DOUT
#define GPIO_P_DOUT_DOUT_DEFAULT                                0x00000000UL  // Mode DEFAULT for GPIO_P_DOUT

// Bit fields for GPIO P_DOUTSET
#define GPIO_P_DOUTSET_RESETVALUE                               0x00000000UL  // Default value for GPIO_P_DOUTSET
#define GPIO_P_DOUTSET_MASK                                     0x0000FFFFUL  // Mask for GPIO_P_DOUTSET
#define GPIO_P_DOUTSET_DOUTSET_SHIFT                                       0  // Shift value for GPIO_DOUTSET
#define GPIO_P_DOUTSET_DOUTSET_MASK                                 0xFFFFUL  // Bit mask for GPIO_DOUTSET
#define GPIO_P_DOUTSET_DOUTSET_DEFAULT                          0x00000000UL  // Mode DEFAULT for GPIO_P_DOUTSET

// Bit fields for GPIO P_DOUTCLR
#define GPIO_P_DOUTCLR_RESETVALUE                               0x00000000UL  // Default value for GPIO_P_DOUTCLR
#define GPIO_P_DOUTCLR_MASK                                     0x0000FFFFUL  // Mask for GPIO_P_DOUTCLR
#define GPIO_P_DOUTCLR_DOUTCLR_SHIFT                                       0  // Shift value for GPIO_DOUTCLR
#define GPIO_P_DOUTCLR_DOUTCLR_MASK                                 0xFFFFUL  // Bit mask for GPIO_DOUTCLR
#define GPIO_P_DOUTCLR_DOUTCLR_DEFAULT                          0x00000000UL  // Mode DEFAULT for GPIO_P_DOUTCLR

// Bit fields for GPIO P_DOUTTGL
#define GPIO_P_DOUTTGL_RESETVALUE                               0x00000000UL  // Default value for GPIO_P_DOUTTGL
#define GPIO_P_DOUTTGL_MASK                                     0x0000FFFFUL  // Mask for GPIO_P_DOUTTGL
#define GPIO_P_DOUTTGL_DOUTTGL_SHIFT                                       0  // Shift value for GPIO_DOUTTGL
#define GPIO_P_DOUTTGL_DOUTTGL_MASK                                 0xFFFFUL  // Bit mask for GPIO_DOUTTGL
#define GPIO_P_DOUTTGL_DOUTTGL_DEFAULT                          0x00000000UL  // Mode DEFAULT for GPIO_P_DOUTTGL

// Bit fields for GPIO P_DIN
#define GPIO_P_DIN_RESETVALUE                                   0x00000000UL  // Default value for GPIO_P_DIN
#define GPIO_P_DIN_MASK                                         0x0000FFFFUL  // Mask for GPIO_P_DIN
#define GPIO_P_DIN_DIN_SHIFT                                               0  // Shift value for GPIO_DIN
#define GPIO_P_DIN_DIN_MASK                                         0xFFFFUL  // Bit mask for GPIO_DIN
#define GPIO_P_DIN_DIN_DEFAULT                                  0x00000000UL  // Mode DEFAULT for GPIO_P_DIN

// Bit fields for GPIO P_PINLOCKN
#define GPIO_P_PINLOCKN_RESETVALUE                              0x0000FFFFUL  // Default value for GPIO_P_PINLOCKN
#define GPIO_P_PINLOCKN_MASK                                    0x0000FFFFUL  // Mask for GPIO_P_PINLOCKN
#define GPIO_P_PINLOCKN_PINLOCKN_SHIFT                                     0  // Shift value for GPIO_PINLOCKN
#define GPIO_P_PINLOCKN_PINLOCKN_MASK                               0xFFFFUL  // Bit mask for GPIO_PINLOCKN
#define GPIO_P_PINLOCKN_PINLOCKN_DEFAULT                        0x0000FFFFUL  // Mode DEFAULT for GPIO_P_PINLOCKN

// Bit fields for GPIO EXTIPSELL
#define GPIO_EXTIPSELL_RESETVALUE                               0x00000000UL  // Default value for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_MASK                                     0x77777777UL  // Mask for GPIO_EXTIPSELL

#define GPIO_EXTIPSELL_EXTIPSEL0_MASK                                  0x7UL  // Bit mask for GPIO_EXTIPSEL0
#define GPIO_EXTIPSELL_EXTIPSEL0_DEFAULT                 (0x00000000UL << 0)  // Mode DEFAULT for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTA                   (0x00000000UL << 0)  // Mode PORTA for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTB                   (0x00000001UL << 0)  // Mode PORTB for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTC                   (0x00000002UL << 0)  // Mode PORTC for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTD                   (0x00000003UL << 0)  // Mode PORTD for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTE                   (0x00000004UL << 0)  // Mode PORTE for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTF                   (0x00000005UL << 0)  // Mode PORTF for GPIO_EXTIPSELL

#define GPIO_EXTIPSELL_EXTIPSEL1_MASK                                 0x70UL  // Bit mask for GPIO_EXTIPSEL1
#define GPIO_EXTIPSELL_EXTIPSEL1_DEFAULT                 (0x00000000UL << 4)  // Mode DEFAULT for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTA                   (0x00000000UL << 4)  // Mode PORTA for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTB                   (0x00000001UL << 4)  // Mode PORTB for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTC                   (0x00000002UL << 4)  // Mode PORTC for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTD                   (0x00000003UL << 4)  // Mode PORTD for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTE                   (0x00000004UL << 4)  // Mode PORTE for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTF                   (0x00000005UL << 4)  // Mode PORTF for GPIO_EXTIPSELL

#define GPIO_EXTIPSELL_EXTIPSEL2_MASK                                0x700UL  // Bit mask for GPIO_EXTIPSEL2
#define GPIO_EXTIPSELL_EXTIPSEL2_DEFAULT                 (0x00000000UL << 8)  // Mode DEFAULT for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTA                   (0x00000000UL << 8)  // Mode PORTA for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTB                   (0x00000001UL << 8)  // Mode PORTB for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTC                   (0x00000002UL << 8)  // Mode PORTC for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTD                   (0x00000003UL << 8)  // Mode PORTD for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTE                   (0x00000004UL << 8)  // Mode PORTE for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTF                   (0x00000005UL << 8)  // Mode PORTF for GPIO_EXTIPSELL

#define GPIO_EXTIPSELL_EXTIPSEL3_MASK                               0x7000UL  // Bit mask for GPIO_EXTIPSEL3
#define GPIO_EXTIPSELL_EXTIPSEL3_DEFAULT                (0x00000000UL << 12)  // Mode DEFAULT for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTA                  (0x00000000UL << 12)  // Mode PORTA for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTB                  (0x00000001UL << 12)  // Mode PORTB for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTC                  (0x00000002UL << 12)  // Mode PORTC for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTD                  (0x00000003UL << 12)  // Mode PORTD for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTE                  (0x00000004UL << 12)  // Mode PORTE for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTF                  (0x00000005UL << 12)  // Mode PORTF for GPIO_EXTIPSELL

#define GPIO_EXTIPSELL_EXTIPSEL4_MASK                              0x70000UL  // Bit mask for GPIO_EXTIPSEL4
#define GPIO_EXTIPSELL_EXTIPSEL4_DEFAULT                (0x00000000UL << 16)  // Mode DEFAULT for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTA                  (0x00000000UL << 16)  // Mode PORTA for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTB                  (0x00000001UL << 16)  // Mode PORTB for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTC                  (0x00000002UL << 16)  // Mode PORTC for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTD                  (0x00000003UL << 16)  // Mode PORTD for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTE                  (0x00000004UL << 16)  // Mode PORTE for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTF                  (0x00000005UL << 16)  // Mode PORTF for GPIO_EXTIPSELL

#define GPIO_EXTIPSELL_EXTIPSEL5_MASK                             0x700000UL  // Bit mask for GPIO_EXTIPSEL5
#define GPIO_EXTIPSELL_EXTIPSEL5_DEFAULT                (0x00000000UL << 20)  // Mode DEFAULT for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTA                  (0x00000000UL << 20)  // Mode PORTA for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTB                  (0x00000001UL << 20)  // Mode PORTB for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTC                  (0x00000002UL << 20)  // Mode PORTC for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTD                  (0x00000003UL << 20)  // Mode PORTD for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTE                  (0x00000004UL << 20)  // Mode PORTE for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTF                  (0x00000005UL << 20)  // Mode PORTF for GPIO_EXTIPSELL

#define GPIO_EXTIPSELL_EXTIPSEL6_MASK                            0x7000000UL  // Bit mask for GPIO_EXTIPSEL6
#define GPIO_EXTIPSELL_EXTIPSEL6_DEFAULT                (0x00000000UL << 24)  // Mode DEFAULT for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTA                  (0x00000000UL << 24)  // Mode PORTA for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTB                  (0x00000001UL << 24)  // Mode PORTB for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTC                  (0x00000002UL << 24)  // Mode PORTC for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTD                  (0x00000003UL << 24)  // Mode PORTD for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTE                  (0x00000004UL << 24)  // Mode PORTE for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTF                  (0x00000005UL << 24)  // Mode PORTF for GPIO_EXTIPSELL

#define GPIO_EXTIPSELL_EXTIPSEL7_MASK                           0x70000000UL  // Bit mask for GPIO_EXTIPSEL7
#define GPIO_EXTIPSELL_EXTIPSEL7_DEFAULT                (0x00000000UL << 28)  // Mode DEFAULT for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTA                  (0x00000000UL << 28)  // Mode PORTA for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTB                  (0x00000001UL << 28)  // Mode PORTB for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTC                  (0x00000002UL << 28)  // Mode PORTC for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTD                  (0x00000003UL << 28)  // Mode PORTD for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTE                  (0x00000004UL << 28)  // Mode PORTE for GPIO_EXTIPSELL
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTF                  (0x00000005UL << 28)  // Mode PORTF for GPIO_EXTIPSELL

// Bit fields for GPIO EXTIPSELH
#define GPIO_EXTIPSELH_RESETVALUE                               0x00000000UL  // Default value for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_MASK                                     0x77777777UL  // Mask for GPIO_EXTIPSELH

#define GPIO_EXTIPSELH_EXTIPSEL8_MASK                                  0x7UL  // Bit mask for GPIO_EXTIPSEL8
#define GPIO_EXTIPSELH_EXTIPSEL8_DEFAULT                 (0x00000000UL << 0)  // Mode DEFAULT for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTA                   (0x00000000UL << 0)  // Mode PORTA for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTB                   (0x00000001UL << 0)  // Mode PORTB for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTC                   (0x00000002UL << 0)  // Mode PORTC for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTD                   (0x00000003UL << 0)  // Mode PORTD for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTE                   (0x00000004UL << 0)  // Mode PORTE for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL8_PORTF                   (0x00000005UL << 0)  // Mode PORTF for GPIO_EXTIPSELH

#define GPIO_EXTIPSELH_EXTIPSEL9_MASK                                 0x70UL  // Bit mask for GPIO_EXTIPSEL9
#define GPIO_EXTIPSELH_EXTIPSEL9_DEFAULT                 (0x00000000UL << 4)  // Mode DEFAULT for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTA                   (0x00000000UL << 4)  // Mode PORTA for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTB                   (0x00000001UL << 4)  // Mode PORTB for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTC                   (0x00000002UL << 4)  // Mode PORTC for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTD                   (0x00000003UL << 4)  // Mode PORTD for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTE                   (0x00000004UL << 4)  // Mode PORTE for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL9_PORTF                   (0x00000005UL << 4)  // Mode PORTF for GPIO_EXTIPSELH

#define GPIO_EXTIPSELH_EXTIPSEL10_MASK                               0x700UL  // Bit mask for GPIO_EXTIPSEL10
#define GPIO_EXTIPSELH_EXTIPSEL10_DEFAULT                (0x00000000UL << 8)  // Mode DEFAULT for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTA                  (0x00000000UL << 8)  // Mode PORTA for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTB                  (0x00000001UL << 8)  // Mode PORTB for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTC                  (0x00000002UL << 8)  // Mode PORTC for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTD                  (0x00000003UL << 8)  // Mode PORTD for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTE                  (0x00000004UL << 8)  // Mode PORTE for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL10_PORTF                  (0x00000005UL << 8)  // Mode PORTF for GPIO_EXTIPSELH

#define GPIO_EXTIPSELH_EXTIPSEL11_MASK                              0x7000UL  // Bit mask for GPIO_EXTIPSEL11
#define GPIO_EXTIPSELH_EXTIPSEL11_DEFAULT               (0x00000000UL << 12)  // Mode DEFAULT for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTA                 (0x00000000UL << 12)  // Mode PORTA for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTB                 (0x00000001UL << 12)  // Mode PORTB for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTC                 (0x00000002UL << 12)  // Mode PORTC for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTD                 (0x00000003UL << 12)  // Mode PORTD for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTE                 (0x00000004UL << 12)  // Mode PORTE for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL11_PORTF                 (0x00000005UL << 12)  // Mode PORTF for GPIO_EXTIPSELH

#define GPIO_EXTIPSELH_EXTIPSEL12_MASK                             0x70000UL  // Bit mask for GPIO_EXTIPSEL12
#define GPIO_EXTIPSELH_EXTIPSEL12_DEFAULT               (0x00000000UL << 16)  // Mode DEFAULT for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTA                 (0x00000000UL << 16)  // Mode PORTA for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTB                 (0x00000001UL << 16)  // Mode PORTB for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTC                 (0x00000002UL << 16)  // Mode PORTC for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTD                 (0x00000003UL << 16)  // Mode PORTD for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTE                 (0x00000004UL << 16)  // Mode PORTE for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL12_PORTF                 (0x00000005UL << 16)  // Mode PORTF for GPIO_EXTIPSELH

#define GPIO_EXTIPSELH_EXTIPSEL13_MASK                            0x700000UL  // Bit mask for GPIO_EXTIPSEL13
#define GPIO_EXTIPSELH_EXTIPSEL13_DEFAULT               (0x00000000UL << 20)  // Mode DEFAULT for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTA                 (0x00000000UL << 20)  // Mode PORTA for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTB                 (0x00000001UL << 20)  // Mode PORTB for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTC                 (0x00000002UL << 20)  // Mode PORTC for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTD                 (0x00000003UL << 20)  // Mode PORTD for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTE                 (0x00000004UL << 20)  // Mode PORTE for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL13_PORTF                 (0x00000005UL << 20)  // Mode PORTF for GPIO_EXTIPSELH

#define GPIO_EXTIPSELH_EXTIPSEL14_MASK                           0x7000000UL  // Bit mask for GPIO_EXTIPSEL14
#define GPIO_EXTIPSELH_EXTIPSEL14_DEFAULT               (0x00000000UL << 24)  // Mode DEFAULT for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTA                 (0x00000000UL << 24)  // Mode PORTA for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTB                 (0x00000001UL << 24)  // Mode PORTB for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTC                 (0x00000002UL << 24)  // Mode PORTC for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTD                 (0x00000003UL << 24)  // Mode PORTD for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTE                 (0x00000004UL << 24)  // Mode PORTE for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL14_PORTF                 (0x00000005UL << 24)  // Mode PORTF for GPIO_EXTIPSELH

#define GPIO_EXTIPSELH_EXTIPSEL15_MASK                          0x70000000UL  // Bit mask for GPIO_EXTIPSEL15
#define GPIO_EXTIPSELH_EXTIPSEL15_DEFAULT               (0x00000000UL << 28)  // Mode DEFAULT for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTA                 (0x00000000UL << 28)  // Mode PORTA for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTB                 (0x00000001UL << 28)  // Mode PORTB for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTC                 (0x00000002UL << 28)  // Mode PORTC for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTD                 (0x00000003UL << 28)  // Mode PORTD for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTE                 (0x00000004UL << 28)  // Mode PORTE for GPIO_EXTIPSELH
#define GPIO_EXTIPSELH_EXTIPSEL15_PORTF                 (0x00000005UL << 28)  // Mode PORTF for GPIO_EXTIPSELH

// Bit fields for GPIO EXTIRISE
#define GPIO_EXTIRISE_EXTIRISE_MASK                                 0xFFFFUL  // Bit mask for GPIO_EXTIRISE
#define GPIO_EXTIRISE_EXTIRISE_DEFAULT                          0x00000000UL  // Mode DEFAULT for GPIO_EXTIRISE

// Bit fields for GPIO EXTIFALL
#define GPIO_EXTIFALL_EXTIFALL_MASK                                 0xFFFFUL  // Bit mask for GPIO_EXTIFALL
#define GPIO_EXTIFALL_EXTIFALL_DEFAULT                          0x00000000UL  // Mode DEFAULT for GPIO_EXTIFALL

// Bit fields for GPIO IEN
#define GPIO_IEN_EXT_MASK                                           0xFFFFUL  // Bit mask for GPIO_EXT
#define GPIO_IEN_EXT_DEFAULT                                    0x00000000UL  // Mode DEFAULT for GPIO_IEN

// Bit fields for GPIO IF
#define GPIO_IF_EXT_MASK                                            0xFFFFUL  // Bit mask for GPIO_EXT
#define GPIO_IF_EXT_DEFAULT                                     0x00000000UL  // Mode DEFAULT for GPIO_IF

// Bit fields for GPIO IFS
#define GPIO_IFS_MASK                                           0x0000FFFFUL  // Mask for GPIO_IFS
#define GPIO_IFS_EXT_DEFAULT                                    0x00000000UL  // Mode DEFAULT for GPIO_IFS

// Bit fields for GPIO IFC
#define GPIO_IFC_EXT_MASK                                           0xFFFFUL  // Bit mask for GPIO_EXT
#define GPIO_IFC_EXT_DEFAULT                                    0x00000000UL  // Mode DEFAULT for GPIO_IFC

// Bit fields for GPIO ROUTE
#define GPIO_ROUTE_MASK                                         0x00000003UL  // Mask for GPIO_ROUTE
#define GPIO_ROUTE_SWCLKPEN                                     (0x1UL << 0)  // Serial Wire Clock Pin Enable
#define GPIO_ROUTE_SWDIOPEN                                     (0x1UL << 1)  // Serial Wire Data Pin Enable

// Bit fields for GPIO INSENSE
#define GPIO_INSENSE_MASK                                       0x00000003UL  // Mask for GPIO_INSENSE
#define GPIO_INSENSE_INT                                        (0x1UL << 0)  // Interrupt Sense Enable
#define GPIO_INSENSE_PRS                                        (0x1UL << 1)  // PRS Sense Enable

// Bit fields for GPIO LOCK
#define GPIO_LOCK_LOCKKEY_MASK                                      0xFFFFUL  // Bit mask for GPIO_LOCKKEY
#define GPIO_LOCK_LOCKKEY_LOCK                                  0x00000000UL  // Mode LOCK for GPIO_LOCK
#define GPIO_LOCK_LOCKKEY_UNLOCKED                              0x00000000UL  // Mode UNLOCKED for GPIO_LOCK
#define GPIO_LOCK_LOCKKEY_LOCKED                                0x00000001UL  // Mode LOCKED for GPIO_LOCK
#define GPIO_LOCK_LOCKKEY_UNLOCK                                0x0000A534UL  // Mode UNLOCK for GPIO_LOCK

// Bit fields for GPIO CTRL
#define GPIO_CTRL_EM4RET                                             (0x1UL)  // Enable EM4 retention

// Bit fields for GPIO CMD
#define GPIO_CMD_EM4WUCLR                                            (0x1UL)  // EM4 Wake-up clear

// Bit fields for GPIO EM4WUEN
#define GPIO_EM4WUEN_EM4WUEN_MASK                                     0x3FUL  // Bit mask for GPIO_EM4WUEN
#define GPIO_EM4WUEN_EM4WUEN_DEFAULT                            0x00000000UL  // Mode DEFAULT for GPIO_EM4WUEN
#define GPIO_EM4WUEN_EM4WUEN_A0                                 0x00000001UL  // Mode A0 for GPIO_EM4WUEN
#define GPIO_EM4WUEN_EM4WUEN_C9                                 0x00000004UL  // Mode C9 for GPIO_EM4WUEN
#define GPIO_EM4WUEN_EM4WUEN_F1                                 0x00000008UL  // Mode F1 for GPIO_EM4WUEN
#define GPIO_EM4WUEN_EM4WUEN_F2                                 0x00000010UL  // Mode F2 for GPIO_EM4WUEN
#define GPIO_EM4WUEN_EM4WUEN_E13                                0x00000020UL  // Mode E13 for GPIO_EM4WUEN

// Bit fields for GPIO EM4WUPOL
#define GPIO_EM4WUPOL_EM4WUPOL_MASK                                   0x3FUL  // Bit mask for GPIO_EM4WUPOL
#define GPIO_EM4WUPOL_EM4WUPOL_DEFAULT                          0x00000000UL  // Mode DEFAULT for GPIO_EM4WUPOL
#define GPIO_EM4WUPOL_EM4WUPOL_A0                               0x00000001UL  // Mode A0 for GPIO_EM4WUPOL
#define GPIO_EM4WUPOL_EM4WUPOL_C9                               0x00000004UL  // Mode C9 for GPIO_EM4WUPOL
#define GPIO_EM4WUPOL_EM4WUPOL_F1                               0x00000008UL  // Mode F1 for GPIO_EM4WUPOL
#define GPIO_EM4WUPOL_EM4WUPOL_F2                               0x00000010UL  // Mode F2 for GPIO_EM4WUPOL
#define GPIO_EM4WUPOL_EM4WUPOL_E13                              0x00000020UL  // Mode E13 for GPIO_EM4WUPOL

// Bit fields for GPIO EM4WUCAUSE
#define GPIO_EM4WUCAUSE_EM4WUCAUSE_MASK                               0x3FUL  // Bit mask for GPIO_EM4WUCAUSE
#define GPIO_EM4WUCAUSE_EM4WUCAUSE_DEFAULT                      0x00000000UL  // Mode DEFAULT for GPIO_EM4WUCAUSE
#define GPIO_EM4WUCAUSE_EM4WUCAUSE_A0                           0x00000001UL  // Mode A0 for GPIO_EM4WUCAUSE
#define GPIO_EM4WUCAUSE_EM4WUCAUSE_C9                           0x00000004UL  // Mode C9 for GPIO_EM4WUCAUSE
#define GPIO_EM4WUCAUSE_EM4WUCAUSE_F1                           0x00000008UL  // Mode F1 for GPIO_EM4WUCAUSE
#define GPIO_EM4WUCAUSE_EM4WUCAUSE_F2                           0x00000010UL  // Mode F2 for GPIO_EM4WUCAUSE
#define GPIO_EM4WUCAUSE_EM4WUCAUSE_E13                          0x00000020UL  // Mode E13 for GPIO_EM4WUCAUSE

__STATIC_INLINE void GPIO_PinOutSet(GPIO_Port_TypeDef port, unsigned int pin)   {GPIO->P[port].DOUTSET = 1 << pin;}
__STATIC_INLINE void GPIO_PinOutClear(GPIO_Port_TypeDef port, unsigned int pin) {GPIO->P[port].DOUTCLR = 1 << pin;}

#endif 