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

#pragma once

#include "./emlib/inc/em_adc.h"

#define ADC_SINGLECTRL_INPUTSEL_TEMPSENS             (0x8)
#define ADC_SINGLECTRL_INPUTSEL_VDD_DIV3             (0x9)
#define ADC_SINGLECTRL_INPUTSEL_VREFDIV2             (0xC)

//#include "Arduino.h"
//#include "io_types.h"

struct temperature {
  int16_t tenthsC ;
  int16_t tenthsF ;
  int8_t  wholeC;
  uint8_t fracC;
  int8_t  wholeF;
  uint8_t fracF;
};

struct uPvdd {
  uint16_t mVolts;
  uint8_t wholeVDD;
  uint8_t fracVDD;
};


class AnalogLP
{
 public:
  AnalogLP();
  uint32_t analogRead(uint32_t sel);
  uint32_t analogReadPin(uint8_t pin);
  uint32_t analogReadVDDsample(void);
  uPvdd    analogReadVDD(void);
  temperature analogReadTemp(void);
  void analogReference(uint32_t ref);
  void analogReadResolution(uint8_t bits);
  void commVDD(void);
  void commTemperature(void);
  void commTempVDD(void);
  void commTemperatureCelcius(void);
  void commTemperatureFarenheit(void);
 private:
  uint32_t adc_reference;
  uint32_t adc_resolution;
  uint32_t adc_oversampling;
  temperature tempval;
  uPvdd vddval;
};

#ifdef __cplusplus
extern "C"{
  void print_adc_regs(void);

} // extern "C"

#endif


/*typedef struct
{
  __IO uint32_t CTRL;         // Control Register
  __IO uint32_t CMD;          // Command Register
  __I uint32_t  STATUS;       // Status Register
  __IO uint32_t SINGLECTRL;   // Single Sample Control Register
  __IO uint32_t SCANCTRL;     // Scan Control Register
  __IO uint32_t IEN;          // Interrupt Enable Register
  __I uint32_t  IF;           // Interrupt Flag Register
  __IO uint32_t IFS;          // Interrupt Flag Set Register
  __IO uint32_t IFC;          // Interrupt Flag Clear Register
  __I uint32_t  SINGLEDATA;   // Single Conversion Result Data
  __I uint32_t  SCANDATA;     // Scan Conversion Result Data
  __I uint32_t  SINGLEDATAP;  // Single Conversion Result Data Peek Register
  __I uint32_t  SCANDATAP;    // Scan Sequence Result Data Peek Register
  __IO uint32_t CAL;          // Calibration Register

  uint32_t      RESERVED0[1]; // Reserved for future use
  __IO uint32_t BIASPROG;     // Bias Programming Register
} ADC_TypeDef;

#define ADC0         ((ADC_TypeDef *) 0x40002000UL)                   // ADC0 base pointer

// Bit fields for ADC CTRL
#define _ADC_CTRL_WARMUPMODE_MASK                     0x3             // Bit mask for ADC_WARMUPMODE
#define ADC_CTRL_WARMUPMODE_NORMAL                    0x0             // Mode NORMAL for ADC_CTRL
#define ADC_CTRL_WARMUPMODE_FASTBG                    0x1             // Mode FASTBG for ADC_CTRL
#define ADC_CTRL_WARMUPMODE_KEEPSCANREFWARM           0x2             // Mode KEEPSCANREFWARM for ADC_CTRL
#define ADC_CTRL_WARMUPMODE_KEEPADCWARM               0x3             // Mode KEEPADCWARM for ADC_CTRL
#define ADC_CTRL_TAILGATE                    (0x1UL << 3)             // Conversion Tailgating
#define _ADC_CTRL_LPFMODE_MASK                       0x30             // Bit mask for ADC_LPFMODE
#define _ADC_CTRL_LPFMODE_SHIFT                        4              // Shift value for ADC_LPFMODE
#define ADC_CTRL_LPFMODE_BYPASS                (0x0 << 4)             // Shifted mode BYPASS for ADC_CTRL
#define ADC_CTRL_LPFMODE_DECAP                 (0x1 << 4)             // Shifted mode DECAP for ADC_CTRL
#define ADC_CTRL_LPFMODE_RCFILT                (0x2 << 4)             // Shifted mode RCFILT for ADC_CTRL
#define _ADC_CTRL_PRESC_MASK                       0x7F00             // Bit mask for ADC_PRESC
#define _ADC_CTRL_PRESC_SHIFT                           8             // Shift value for ADC_PRESC
#define _ADC_CTRL_TIMEBASE_MASK                  0x7F0000             // Bit mask for ADC_TIMEBASE
#define _ADC_CTRL_TIMEBASE_SHIFT                       16             // Shift value for ADC_TIMEBASE
#define _ADC_CTRL_OVSRSEL_MASK                  0xF000000             // Bit mask for ADC_OVSRSEL
#define _ADC_CTRL_OVSRSEL_MASK                  0xF000000             // Bit mask for ADC_OVSRSEL
#define _ADC_CTRL_OVSRSEL_SHIFT                        24             // Shift value for ADC_OVSRSEL
#define ADC_CTRL_OVSRSEL_X2                   (0x0 << 24)             // Shifted mode X2 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X4                   (0x1 << 24)             // Shifted mode X4 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X8                   (0x2 << 24)             // Shifted mode X8 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X16                  (0x3 << 24)             // Shifted mode X16 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X32                  (0x4 << 24)             // Shifted mode X32 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X64                  (0x5 << 24)             // Shifted mode X64 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X128                 (0x6 << 24)             // Shifted mode X128 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X256                 (0x7 << 24)             // Shifted mode X256 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X512                 (0x8 << 24)             // Shifted mode X512 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X1024                (0x9 << 24)             // Shifted mode X1024 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X2048                (0xA << 24)             // Shifted mode X2048 for ADC_CTRL
#define ADC_CTRL_OVSRSEL_X4096                (0xB << 24)             // Shifted mode X4096 for ADC_CTRL
#define ADC_CTRL_CHCONIDLE                    (0x1 << 28)             // Input channel connected when ADC is IDLE

// Bit fields for ADC CMD
#define ADC_CMD_SINGLESTART                  (0x1UL << 0)             // Single Conversion Start
#define ADC_CMD_SINGLESTOP                   (0x1UL << 1)             // Single Conversion Stop
#define ADC_CMD_SCANSTART                    (0x1UL << 2)             // Scan Sequence Start
#define ADC_CMD_SCANSTOP                     (0x1UL << 3)             // Scan Sequence Stop

// Bit fields for ADC STATUS
#define ADC_STATUS_SINGLEACT                 (0x1UL << 0)             // Single Conversion Active
#define ADC_STATUS_SCANACT                   (0x1UL << 1)             // Scan Conversion Active
#define ADC_STATUS_SINGLEREFWARM             (0x1UL << 8)             // Single Reference Warmed Up
#define ADC_STATUS_SCANREFWARM               (0x1UL << 9)             // Scan Reference Warmed Up
#define ADC_STATUS_WARM                     (0x1UL << 12)             // ADC Warmed Up
#define ADC_STATUS_SINGLEDV                 (0x1UL << 16)             // Single Sample Data Valid
#define ADC_STATUS_SCANDV                   (0x1UL << 17)             // Scan Data Valid
#define _ADC_STATUS_SCANDATASRC_MASK            0x7000000             // Bit mask for ADC_SCANDATASRC
#define _ADC_STATUS_SCANDATASRC_SHIFT                  24             // Shift value for ADC_SCANDATASRC
#define ADC_STATUS_SCANDATASRC_CH0            (0x0 << 24)             // Shifted mode CH0 for ADC_STATUS
#define ADC_STATUS_SCANDATASRC_CH1            (0x1 << 24)             // Shifted mode CH1 for ADC_STATUS
#define ADC_STATUS_SCANDATASRC_CH2            (0x2 << 24)             // Shifted mode CH2 for ADC_STATUS
#define ADC_STATUS_SCANDATASRC_CH3            (0x3 << 24)             // Shifted mode CH3 for ADC_STATUS
#define ADC_STATUS_SCANDATASRC_CH4            (0x4 << 24)             // Shifted mode CH4 for ADC_STATUS
#define ADC_STATUS_SCANDATASRC_CH5            (0x5 << 24)             // Shifted mode CH5 for ADC_STATUS
#define ADC_STATUS_SCANDATASRC_CH6            (0x6 << 24)             // Shifted mode CH6 for ADC_STATUS
#define ADC_STATUS_SCANDATASRC_CH7            (0x7 << 24)             // Shifted mode CH7 for ADC_STATUS

// Bit fields for ADC SINGLECTRL
#define ADC_SINGLECTRL_REP                   (0x1UL << 0)             // Single Sample Repetitive Mode
#define ADC_SINGLECTRL_DIFF                  (0x1UL << 1)             // Single Sample Differential Mode
#define ADC_SINGLECTRL_ADJ                   (0x1UL << 2)             // Single Sample Result Adjustment

#define _ADC_SINGLECTRL_RES_MASK                     0x30             // Bit mask for ADC_RES
#define _ADC_SINGLECTRL_RES_SHIFT                       4             // Shift value for ADC_RES
#define ADC_SINGLECTRL_RES_12BIT                (0x0 << 4)            // Shifted mode 12BIT for ADC_SINGLECTRL
#define ADC_SINGLECTRL_RES_8BIT                 (0x1 << 4)            // Shifted mode 8BIT for ADC_SINGLECTRL
#define ADC_SINGLECTRL_RES_6BIT                 (0x2 << 4)            // Shifted mode 6BIT for ADC_SINGLECTRL
#define ADC_SINGLECTRL_RES_OVS                  (0x3 << 4)            // Shifted mode OVS for ADC_SINGLECTRL
#define _ADC_SINGLECTRL_INPUTSEL_MASK                0xF00            // Bit mask for ADC_INPUTSEL
#define _ADC_SINGLECTRL_INPUTSEL_SHIFT                   8            // Shift value for ADC_INPUTSEL
#define ADC_SINGLECTRL_INPUTSEL_CH0             (0x0 << 8)            // Shifted mode CH0 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_CH1             (0x1 << 8)            // Shifted mode CH1 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_CH2             (0x2 << 8)            // Shifted mode CH2 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_CH3             (0x3 << 8)            // Shifted mode CH3 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_CH4             (0x4 << 8)            // Shifted mode CH4 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_CH5             (0x5 << 8)            // Shifted mode CH5 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_CH6             (0x6 << 8)            // Shifted mode CH6 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_CH7             (0x7 << 8)            // Shifted mode CH7 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_TEMP            (0x8 << 8)            // Shifted mode TEMP for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_TEMPSENS             (0x8)            // Shifted mode TEMP for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_VDDDIV3         (0x9 << 8)            // Shifted mode VDDDIV3 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_VDD_DIV3             (0x9)            // Shifted mode VDDDIV3 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_VDD             (0xA << 8)            // Shifted mode VDD for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_VSS             (0xB << 8)            // Shifted mode VSS for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_VREFDIV2        (0xC << 8)            // Shifted mode VREFDIV2 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_DAC0OUT0        (0xD << 8)            // Shifted mode DAC0OUT0 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_INPUTSEL_DAC0OUT1        (0xE << 8)            // Shifted mode DAC0OUT1 for ADC_SINGLECTRL
#define _ADC_SINGLECTRL_REF_MASK                   0x70000            // Bit mask for ADC_REF
#define _ADC_SINGLECTRL_REF_SHIFT                       16            // Shift value for ADC_REF
#define ADC_SINGLECTRL_REF_1V25                 (0x0 << 16)           // Shifted mode 1V25 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_REF_2V5                  (0x1 << 16)           // Shifted mode 2V5 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_REF_VDD                  (0x2 << 16)           // Shifted mode VDD for ADC_SINGLECTRL
#define ADC_SINGLECTRL_REF_5VDIFF               (0x3 << 16)           // Shifted mode 5VDIFF for ADC_SINGLECTRL
#define ADC_SINGLECTRL_REF_EXTSINGLE            (0x4 << 16)           // Shifted mode EXTSINGLE for ADC_SINGLECTRL
#define ADC_SINGLECTRL_REF_2XEXTDIFF            (0x5 << 16)           // Shifted mode 2XEXTDIFF for ADC_SINGLECTRL
#define ADC_SINGLECTRL_REF_2XVDD                (0x6 << 16)           // Shifted mode 2XVDD for ADC_SINGLECTRL
#define _ADC_SINGLECTRL_AT_MASK                    0xF00000           // Bit mask for ADC_AT
#define _ADC_SINGLECTRL_AT_SHIFT                         20           // Shift value for ADC_AT
#define ADC_SINGLECTRL_AT_1CYCLE                 (0x0 << 20)          // Shifted mode 1CYCLE for ADC_SINGLECTRL
#define ADC_SINGLECTRL_AT_2CYCLES                (0x1 << 20)          // Shifted mode 2CYCLES for ADC_SINGLECTRL
#define ADC_SINGLECTRL_AT_4CYCLES                (0x2 << 20)          // Shifted mode 4CYCLES for ADC_SINGLECTRL
#define ADC_SINGLECTRL_AT_8CYCLES                (0x3 << 20)          // Shifted mode 8CYCLES for ADC_SINGLECTRL
#define ADC_SINGLECTRL_AT_16CYCLES               (0x4 << 20)          // Shifted mode 16CYCLES for ADC_SINGLECTRL
#define ADC_SINGLECTRL_AT_32CYCLES               (0x5 << 20)          // Shifted mode 32CYCLES for ADC_SINGLECTRL
#define ADC_SINGLECTRL_AT_64CYCLES               (0x6 << 20)          // Shifted mode 64CYCLES for ADC_SINGLECTRL
#define ADC_SINGLECTRL_AT_128CYCLES              (0x7 << 20)          // Shifted mode 128CYCLES for ADC_SINGLECTRL
#define ADC_SINGLECTRL_AT_256CYCLES              (0x8 << 20)          // Shifted mode 256CYCLES for ADC_SINGLECTRL

#define ADC_SINGLECTRL_PRSEN                   (0x1UL << 24)          // Single Sample PRS Trigger Enable

#define _ADC_SINGLECTRL_PRSSEL_MASK               0x30000000          // Bit mask for ADC_PRSSEL
#define _ADC_SINGLECTRL_PRSSEL_SHIFT                      28          // Shift value for ADC_PRSSEL
#define ADC_SINGLECTRL_PRSSEL_PRSCH0             (0x0 << 28)          // Shifted mode PRSCH0 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_PRSSEL_PRSCH1             (0x1 << 28)          // Shifted mode PRSCH1 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_PRSSEL_PRSCH2             (0x2 << 28)          // Shifted mode PRSCH2 for ADC_SINGLECTRL
#define ADC_SINGLECTRL_PRSSEL_PRSCH3             (0x3 << 28)          // Shifted mode PRSCH3 for ADC_SINGLECTRL

// Bit fields for ADC SCANCTRL
#define ADC_SCANCTRL_REP                        (0x1UL << 0)          // Scan Sequence Repetitive Mode
#define ADC_SCANCTRL_DIFF                       (0x1UL << 1)          // Scan Sequence Differential Mode
#define ADC_SCANCTRL_ADJ                        (0x1UL << 2)          // Scan Sequence Result Adjustment
#define _ADC_SCANCTRL_ADJ_MASK                           0x4          // Bit mask for ADC_ADJ
#define _ADC_SCANCTRL_ADJ_SHIFT                            2          // Shift value for ADC_ADJ
#define ADC_SCANCTRL_ADJ_RIGHT                    (0x0 << 2)          // Shifted mode RIGHT for ADC_SCANCTRL
#define ADC_SCANCTRL_ADJ_LEFT                     (0x1 << 2)          // Shifted mode LEFT for ADC_SCANCTRL

#define _ADC_SCANCTRL_RES_MASK                          0x30          // Bit mask for ADC_RES
#define _ADC_SCANCTRL_RES_SHIFT                            4          // Shift value for ADC_RES
#define ADC_SCANCTRL_RES_12BIT                    (0x0 << 4)          // Shifted mode 12BIT for ADC_SCANCTRL
#define ADC_SCANCTRL_RES_8BIT                     (0x1 << 4)          // Shifted mode 8BIT for ADC_SCANCTRL
#define ADC_SCANCTRL_RES_6BIT                     (0x2 << 4)          // Shifted mode 6BIT for ADC_SCANCTRL
#define ADC_SCANCTRL_RES_OVS                      (0x3 << 4)          // Shifted mode OVS for ADC_SCANCTRL

#define _ADC_SCANCTRL_INPUTMASK_MASK                  0xFF00          // Bit mask for ADC_INPUTMASK
#define _ADC_SCANCTRL_INPUTMASK_SHIFT                      8          // Shift value for ADC_INPUTMASK
#define ADC_SCANCTRL_INPUTMASK_CH0               (0x01 << 8)          // Shifted mode CH0 for ADC_SCANCTRL
#define ADC_SCANCTRL_INPUTMASK_CH1               (0x02 << 8)          // Shifted mode CH1 for ADC_SCANCTRL
#define ADC_SCANCTRL_INPUTMASK_CH2               (0x04 << 8)          // Shifted mode CH2 for ADC_SCANCTRL
#define ADC_SCANCTRL_INPUTMASK_CH3               (0x08 << 8)          // Shifted mode CH3 for ADC_SCANCTRL
#define ADC_SCANCTRL_INPUTMASK_CH4               (0x10 << 8)          // Shifted mode CH4 for ADC_SCANCTRL
#define ADC_SCANCTRL_INPUTMASK_CH5               (0x20 << 8)          // Shifted mode CH5 for ADC_SCANCTRL
#define ADC_SCANCTRL_INPUTMASK_CH6               (0x40 << 8)          // Shifted mode CH6 for ADC_SCANCTRL
#define ADC_SCANCTRL_INPUTMASK_CH7               (0x80 << 8)          // Shifted mode CH7 for ADC_SCANCTRL

#define _ADC_SCANCTRL_REF_SHIFT                          16           // Shift value for ADC_REF
#define _ADC_SCANCTRL_REF_MASK                      0x70000           // Bit mask for ADC_REF
#define ADC_SCANCTRL_REF_1V25                   (0x0 << 16)           // Shifted mode 1V25 for ADC_SCANCTRL
#define ADC_SCANCTRL_REF_2V5                    (0x1 << 16)           // Shifted mode 2V5 for ADC_SCANCTRL
#define ADC_SCANCTRL_REF_VDD                    (0x2 << 16)           // Shifted mode VDD for ADC_SCANCTRL
#define ADC_SCANCTRL_REF_5VDIFF                 (0x3 << 16)           // Shifted mode 5VDIFF for ADC_SCANCTRL
#define ADC_SCANCTRL_REF_EXTSINGLE              (0x4 << 16)           // Shifted mode EXTSINGLE for ADC_SCANCTRL
#define ADC_SCANCTRL_REF_2XEXTDIFF              (0x5 << 16)           // Shifted mode 2XEXTDIFF for ADC_SCANCTRL
#define ADC_SCANCTRL_REF_2XVDD                  (0x6 << 16)           // Shifted mode 2XVDD for ADC_SCANCTRL

#define _ADC_SCANCTRL_AT_SHIFT                           20           // Shift value for ADC_AT
#define _ADC_SCANCTRL_AT_MASK                      0xF00000           // Bit mask for ADC_AT
#define ADC_SCANCTRL_AT_1CYCLE                  (0x0 << 20)           // Shifted mode 1CYCLE for ADC_SCANCTRL
#define ADC_SCANCTRL_AT_2CYCLES                 (0x1 << 20)           // Shifted mode 2CYCLES for ADC_SCANCTRL
#define ADC_SCANCTRL_AT_4CYCLES                 (0x2 << 20)           // Shifted mode 4CYCLES for ADC_SCANCTRL
#define ADC_SCANCTRL_AT_8CYCLES                 (0x3 << 20)           // Shifted mode 8CYCLES for ADC_SCANCTRL
#define ADC_SCANCTRL_AT_16CYCLES                (0x4 << 20)           // Shifted mode 16CYCLES for ADC_SCANCTRL
#define ADC_SCANCTRL_AT_32CYCLES                (0x5 << 20)           // Shifted mode 32CYCLES for ADC_SCANCTRL
#define ADC_SCANCTRL_AT_64CYCLES                (0x6 << 20)           // Shifted mode 64CYCLES for ADC_SCANCTRL
#define ADC_SCANCTRL_AT_128CYCLES               (0x7 << 20)           // Shifted mode 128CYCLES for ADC_SCANCTRL
#define ADC_SCANCTRL_AT_256CYCLES               (0x8 << 20)           // Shifted mode 256CYCLES for ADC_SCANCTRL

#define ADC_SCANCTRL_PRSEN                    (0x1UL << 24)           // Scan Sequence PRS Trigger Enable

#define _ADC_SCANCTRL_PRSSEL_SHIFT                       28           // Shift value for ADC_PRSSEL
#define _ADC_SCANCTRL_PRSSEL_MASK                0x30000000           // Bit mask for ADC_PRSSEL
#define ADC_SCANCTRL_PRSSEL_PRSCH0              (0x0 << 28)           // Shifted mode PRSCH0 for ADC_SCANCTRL
#define ADC_SCANCTRL_PRSSEL_PRSCH1              (0x1 << 28)           // Shifted mode PRSCH1 for ADC_SCANCTRL
#define ADC_SCANCTRL_PRSSEL_PRSCH2              (0x2 << 28)           // Shifted mode PRSCH2 for ADC_SCANCTRL
#define ADC_SCANCTRL_PRSSEL_PRSCH3              (0x3 << 28)           // Shifted mode PRSCH3 for ADC_SCANCTRL

// Bit fields for ADC IEN
#define ADC_IEN_SINGLE                         (0x1UL << 0)           // Single Conversion Complete Interrupt Enable
#define ADC_IEN_SCAN                           (0x1UL << 1)           // Scan Conversion Complete Interrupt Enable
#define ADC_IEN_SINGLEOF                       (0x1UL << 8)           // Single Result Overflow Interrupt Enable
#define ADC_IEN_SCANOF                         (0x1UL << 9)           // Scan Result Overflow Interrupt Enable

// Bit fields for ADC IF
#define ADC_IF_SINGLE                          (0x1UL << 0)           // Single Conversion Complete Interrupt Flag
#define ADC_IF_SCAN                            (0x1UL << 1)           // Scan Conversion Complete Interrupt Flag
#define ADC_IF_SINGLEOF                        (0x1UL << 8)           // Single Result Overflow Interrupt Flag
#define ADC_IF_SCANOF                          (0x1UL << 9)           // Scan Result Overflow Interrupt Flag

// Bit fields for ADC IFS
#define ADC_IFS_SINGLE                         (0x1UL << 0)           // Single Conversion Complete Interrupt Flag Set
#define ADC_IFS_SCAN                           (0x1UL << 1)           // Scan Conversion Complete Interrupt Flag Set
#define ADC_IFS_SINGLEOF                       (0x1UL << 8)           // Single Result Overflow Interrupt Flag Set
#define ADC_IFS_SCANOF                         (0x1UL << 9)           // Scan Result Overflow Interrupt Flag Set

// Bit fields for ADC IFC
#define ADC_IFC_SINGLE                         (0x1UL << 0)           // Single Conversion Complete Interrupt Flag Clear
#define ADC_IFC_SCAN                           (0x1UL << 1)           // Scan Conversion Complete Interrupt Flag Clear
#define ADC_IFC_SINGLEOF                       (0x1UL << 8)           // Single Result Overflow Interrupt Flag Clear
#define ADC_IFC_SCANOF                         (0x1UL << 9)           // Scan Result Overflow Interrupt Flag Clear

// Bit fields for ADC SINGLEDATA
#define _ADC_SINGLEDATA_MASK                     0xFFFFFFFF           // Mask for ADC_SINGLEDATA

// Bit fields for ADC SCANDATA
#define _ADC_SCANDATA_MASK                       0xFFFFFFFF           // Mask for ADC_SCANDATA

// Bit fields for ADC SINGLEDATAP
#define _ADC_SINGLEDATAP_MASK                    0xFFFFFFFF           // Mask for ADC_SINGLEDATAP

// Bit fields for ADC SCANDATAP
#define _ADC_SCANDATAP_MASK                      0xFFFFFFFF           // Mask for ADC_SCANDATAP

// Bit fields for ADC CAL
#define _ADC_CAL_SINGLEOFFSET_MASK                     0x7F           // Bit mask for ADC_SINGLEOFFSET
#define _ADC_CAL_SINGLEGAIN_SHIFT                         8           // Shift value for ADC_SINGLEGAIN
#define _ADC_CAL_SINGLEGAIN_MASK                     0x7F00           // Bit mask for ADC_SINGLEGAIN
#define _ADC_CAL_SCANOFFSET_SHIFT                        16           // Shift value for ADC_SCANOFFSET
#define _ADC_CAL_SCANOFFSET_MASK                   0x7F0000           // Bit mask for ADC_SCANOFFSET
#define _ADC_CAL_SCANGAIN_SHIFT                          24           // Shift value for ADC_SCANGAIN
#define _ADC_CAL_SCANGAIN_MASK                   0x7F000000           // Bit mask for ADC_SCANGAIN

// Bit fields for ADC BIASPROG
#define _ADC_BIASPROG_BIASPROG_SHIFT                      0           // Shift value for ADC_BIASPROG
#define _ADC_BIASPROG_BIASPROG_MASK                     0xF           // Bit mask for ADC_BIASPROG
#define ADC_BIASPROG_HALFBIAS                    (0x1 << 6)           // Half Bias Current
#define _ADC_BIASPROG_HALFBIAS_SHIFT                      6           // Shift value for ADC_HALFBIAS
#define _ADC_BIASPROG_HALFBIAS_MASK                    0x40           // Bit mask for ADC_HALFBIAS
#define _ADC_BIASPROG_COMPBIAS_SHIFT                      8           // Shift value for ADC_COMPBIAS
#define _ADC_BIASPROG_COMPBIAS_MASK                   0xF00           // Bit mask for ADC_COMPBIAS
*/
#define INTERNAL1V25 ADC_SINGLECTRL_REF_1V25
#define INTERNAL2V5  ADC_SINGLECTRL_REF_2V5
#define INTERNALVDD  ADC_SINGLECTRL_REF_VDD
#define DEFAULT      ADC_SINGLECTRL_REF_VDD
#define EXTERNAL     ADC_SINGLECTRL_REF_EXTSINGLE

#define RES_6BITS    ADC_SINGLECTRL_RES_6BIT
#define RES_8BITS    ADC_SINGLECTRL_RES_8BIT
#define RES_12BITS   ADC_SINGLECTRL_RES_12BIT

//#endif
