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


#ifndef __EFM_PIN_CONFIG_H
#define __EFM_PIN_CONFIG_H

#include <stdint.h>
#include "io_types.h"
#include "wiring_constants.h"

#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3
#define PORTE    4
#define PORTF    5

#define RISING     (0x2)
#define CHANGE     (0x3)
#define FALLING    (0x4)

#define GPIO_MODE_MASK                          0x0000000FUL  // BIT MASK
#define GPIO_MODE_DISABLED                      0x00000000UL  // DISABLED
#define GPIO_MODE_INPUT                         0x00000001UL  // INPUT
#define GPIO_MODE_INPUTPULL                     0x00000002UL  // INPUTPULL
#define GPIO_MODE_INPUTPULLFILTER               0x00000003UL  // INPUTPULLFILTER
#define GPIO_MODE_PUSHPULL                      0x00000004UL  // PUSHPULL
#define GPIO_MODE_PUSHPULLDRIVE                 0x00000005UL  // PUSHPULLDRIVE
#define GPIO_MODE_WIREDOR                       0x00000006UL  // WIREDOR
#define GPIO_MODE_WIREDORPULLDOWN               0x00000007UL  // WIREDORPULLDOWN
#define GPIO_MODE_WIREDAND                      0x00000008UL  // WIREDAND
#define GPIO_MODE_WIREDANDFILTER                0x00000009UL  // WIREDANDFILTER
#define GPIO_MODE_WIREDANDPULLUP                0x0000000AUL  // WIREDANDPULLUP
#define GPIO_MODE_WIREDANDPULLUPFILTER          0x0000000BUL  // WIREDANDPULLUPFILTER
#define GPIO_MODE_WIREDANDDRIVE                 0x0000000CUL  // WIREDANDDRIVE
#define GPIO_MODE_WIREDANDDRIVEFILTER           0x0000000DUL  // WIREDANDDRIVEFILTER
#define GPIO_MODE_WIREDANDDRIVEPULLUP           0x0000000EUL  // WIREDANDDRIVEPULLUP
#define GPIO_MODE_WIREDANDDRIVEPULLUPFILTER     0x0000000FUL  // WIREDANDDRIVEPULLUPFILTER

#define DRIVEMODE_STANDARD                      0x00000000UL
#define DRIVEMODE_LOWEST                        0x00000001UL
#define DRIVEMODE_HIGH                          0x00000002UL
#define DRIVEMODE_LOW                           0x00000003UL

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
  gpioModeDisabled                  = 0x00000000UL,  // Input disabled. Pullup if DOUT is set
  gpioModeInput                     = 0x00000001UL,  // Input enabled. Filter if DOUT is set
  gpioModeInputPull                 = 0x00000002UL,  // Input enabled. DOUT determines pull direction
  gpioModeInputPullFilter           = 0x00000003UL,  // Input enabled with filter. DOUT determines pull direction
  gpioModePushPull                  = 0x00000004UL,  // Push-pull output
  gpioModePushPullDrive             = 0x00000005UL,  // Push-pull output with drive-strength set by DRIVEMODE
  gpioModeWiredOr                   = 0x00000006UL,  // Wired-or output
  gpioModeWiredOrPullDown           = 0x00000007UL,  // Wired-or output with pull-down
  gpioModeWiredAnd                  = 0x00000008UL,  // Open-drain output
  gpioModeWiredAndFilter            = 0x00000009UL,  // Open-drain output with filter
  gpioModeWiredAndPullUp            = 0x0000000AUL,  // Open-drain output with pullup
  gpioModeWiredAndPullUpFilter      = 0x0000000BUL,  // Open-drain output with filter and pullup
  gpioModeWiredAndDrive             = 0x0000000CUL,  // Open-drain output drive-strength set by DRIVEMODE
  gpioModeWiredAndDriveFilter       = 0x0000000DUL,  // Open-drain output with filter drive-strength set by DRIVEMODE
  gpioModeWiredAndDrivePullUp       = 0x0000000EUL,  // Open-drain output with pullup drive-strength set by DRIVEMODE
  gpioModeWiredAndDrivePullUpFilter = 0x0000000FUL  // Open-drain output with filter, pullup drive-strength set by DRIVEMODE
} GPIO_Mode_TypeDef;

/** GPIO drive mode. */
typedef enum
{
  gpioDriveModeStandard = 0x00000000UL, // Default 6mA
  gpioDriveModeLowest   = 0x00000001UL, // 0.5 mA
  gpioDriveModeHigh     = 0x00000002UL, // 20 mA
  gpioDriveModeLow      = 0x00000003UL  // 2 mA
} GPIO_DriveMode_TypeDef;


#define GPIO         ((GPIO_TypeDef *) 0x40006000UL) // GPIO base address


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

  void GPIO_config(uint32_t port, uint32_t pin, uint32_t ulMode);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  // __EFM_PIN_CONFIG_H

