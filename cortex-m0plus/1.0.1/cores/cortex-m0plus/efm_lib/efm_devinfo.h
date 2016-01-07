#pragma once

#include "io_types.h"

#define DEVINFO_HFRCOCAL1_BAND21      0x000000FFUL        // 21MHz tuning value for HFRCO, mask

// Bit fields for EFM32ZG_DEVINFO
#define DEVINFO_CAL_CRC_MASK                      0x0000FFFFUL // Integrity CRC checksum mask
#define DEVINFO_CAL_TEMP_MASK                     0x00FF0000UL // Calibration temperature, DegC, mask
#define DEVINFO_CAL_TEMP_SHIFT                    16           // Calibration temperature shift
#define DEVINFO_ADC0CAL0_1V25_GAIN_MASK           0x00007F00UL // Gain for 1V25 reference, mask
#define DEVINFO_ADC0CAL0_1V25_GAIN_SHIFT          8            // Gain for 1V25 reference, shift
#define DEVINFO_ADC0CAL0_1V25_OFFSET_MASK         0x0000007FUL // Offset for 1V25 reference, mask
#define DEVINFO_ADC0CAL0_1V25_OFFSET_SHIFT        0            // Offset for 1V25 reference, shift
#define DEVINFO_ADC0CAL0_2V5_GAIN_MASK            0x7F000000UL // Gain for 2V5 reference, mask
#define DEVINFO_ADC0CAL0_2V5_GAIN_SHIFT           24           // Gain for 2V5 reference, shift
#define DEVINFO_ADC0CAL0_2V5_OFFSET_MASK          0x007F0000UL // Offset for 2V5 reference, mask
#define DEVINFO_ADC0CAL0_2V5_OFFSET_SHIFT         16           // Offset for 2V5 reference, shift
#define DEVINFO_ADC0CAL1_VDD_GAIN_MASK            0x00007F00UL // Gain for VDD reference, mask
#define DEVINFO_ADC0CAL1_VDD_GAIN_SHIFT           8            // Gain for VDD reference, shift
#define DEVINFO_ADC0CAL1_VDD_OFFSET_MASK          0x0000007FUL // Offset for VDD reference, mask
#define DEVINFO_ADC0CAL1_VDD_OFFSET_SHIFT         0            // Offset for VDD reference, shift
#define DEVINFO_ADC0CAL1_5VDIFF_GAIN_MASK         0x7F000000UL // Gain 5VDIFF for 5VDIFF reference, mask
#define DEVINFO_ADC0CAL1_5VDIFF_GAIN_SHIFT        24           // Gain for 5VDIFF reference, mask
#define DEVINFO_ADC0CAL1_5VDIFF_OFFSET_MASK       0x007F0000UL // Offset for 5VDIFF reference, mask
#define DEVINFO_ADC0CAL1_5VDIFF_OFFSET_SHIFT      16           // Offset for 5VDIFF reference, shift
#define DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_MASK     0x0000007FUL // Offset for 2XVDDVSS reference, mask
#define DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_SHIFT    0            // Offset for 2XVDDVSS reference, shift
#define DEVINFO_ADC0CAL2_TEMP1V25_MASK            0xFFF00000UL // Temperature reading at 1V25 reference, mask
#define DEVINFO_ADC0CAL2_TEMP1V25_SHIFT           20           // Temperature reading at 1V25 reference, DegC
#define DEVINFO_IDAC0CAL0_RANGE0_MASK             0x000000FFUL // Current range 0 tuning value for IDAC0 mask
#define DEVINFO_IDAC0CAL0_RANGE0_SHIFT            0            // Current range 0 tuning value for IDAC0 shift
#define DEVINFO_IDAC0CAL0_RANGE1_MASK             0x0000FF00UL // Current range 1 tuning value for IDAC0 mask
#define DEVINFO_IDAC0CAL0_RANGE1_SHIFT            8            // Current range 1 tuning value for IDAC0 shift
#define DEVINFO_IDAC0CAL0_RANGE2_MASK             0x00FF0000UL // Current range 2 tuning value for IDAC0 mask
#define DEVINFO_IDAC0CAL0_RANGE2_SHIFT            16           // Current range 2 tuning value for IDAC0 shift
#define DEVINFO_IDAC0CAL0_RANGE3_MASK             0xFF000000UL // Current range 3 tuning value for IDAC0 mask
#define DEVINFO_IDAC0CAL0_RANGE3_SHIFT            24           // Current range 3 tuning value for IDAC0 shift
#define DEVINFO_AUXHFRCOCAL0_BAND1_MASK           0x000000FFUL // 1MHz tuning value for AUXHFRCO, mask
#define DEVINFO_AUXHFRCOCAL0_BAND1_SHIFT          0            // 1MHz tuning value for AUXHFRCO, shift
#define DEVINFO_AUXHFRCOCAL0_BAND7_MASK           0x0000FF00UL // 7MHz tuning value for AUXHFRCO, mask
#define DEVINFO_AUXHFRCOCAL0_BAND7_SHIFT          8            // 7MHz tuning value for AUXHFRCO, shift
#define DEVINFO_AUXHFRCOCAL0_BAND11_MASK          0x00FF0000UL // 11MHz tuning value for AUXHFRCO, mask
#define DEVINFO_AUXHFRCOCAL0_BAND11_SHIFT         16           // 11MHz tuning value for AUXHFRCO, shift
#define DEVINFO_AUXHFRCOCAL0_BAND14_MASK          0xFF000000UL // 14MHz tuning value for AUXHFRCO, mask
#define DEVINFO_AUXHFRCOCAL0_BAND14_SHIFT         24           // 14MHz tuning value for AUXHFRCO, shift
#define DEVINFO_AUXHFRCOCAL1_BAND21_MASK          0x000000FFUL // 21MHz tuning value for AUXHFRCO, mask
#define DEVINFO_AUXHFRCOCAL1_BAND21_SHIFT         0            // 21MHz tuning value for AUXHFRCO, shift
#define DEVINFO_HFRCOCAL0_BAND1_MASK              0x000000FFUL // 1MHz tuning value for HFRCO, mask
#define DEVINFO_HFRCOCAL0_BAND1_SHIFT             0            // 1MHz tuning value for HFRCO, shift
#define DEVINFO_HFRCOCAL0_BAND7_MASK              0x0000FF00UL // 7MHz tuning value for HFRCO, mask
#define DEVINFO_HFRCOCAL0_BAND7_SHIFT             8            // 7MHz tuning value for HFRCO, shift
#define DEVINFO_HFRCOCAL0_BAND11_MASK             0x00FF0000UL // 11MHz tuning value for HFRCO, mask
#define DEVINFO_HFRCOCAL0_BAND11_SHIFT            16           // 11MHz tuning value for HFRCO, shift
#define DEVINFO_HFRCOCAL0_BAND14_MASK             0xFF000000UL // 14MHz tuning value for HFRCO, mask
#define DEVINFO_HFRCOCAL0_BAND14_SHIFT            24           // 14MHz tuning value for HFRCO, shift
#define DEVINFO_HFRCOCAL1_BAND21_MASK             0x000000FFUL // 21MHz tuning value for HFRCO, mask
#define DEVINFO_HFRCOCAL1_BAND21_SHIFT            0            // 21MHz tuning value for HFRCO, shift
#define DEVINFO_MEMINFO_FLASH_PAGE_SIZE_MASK      0xFF000000UL // Flash page size (refer to ref.man for encoding) mask
#define DEVINFO_MEMINFO_FLASH_PAGE_SIZE_SHIFT     24           // Flash page size shift
#define DEVINFO_UNIQUEL_MASK                      0xFFFFFFFFUL // Lower part of  64-bit device unique number
#define DEVINFO_UNIQUEL_SHIFT                     0            // Unique Low 32-bit shift
#define DEVINFO_UNIQUEH_MASK                      0xFFFFFFFFUL // High part of  64-bit device unique number
#define DEVINFO_UNIQUEH_SHIFT                     0            // Unique High 32-bit shift
#define DEVINFO_MSIZE_SRAM_MASK                   0xFFFF0000UL // Flash size in kilobytes
#define DEVINFO_MSIZE_SRAM_SHIFT                  16           // Bit position for flash size
#define DEVINFO_MSIZE_FLASH_MASK                  0x0000FFFFUL // SRAM size in kilobytes
#define DEVINFO_MSIZE_FLASH_SHIFT                 0            // Bit position for SRAM size
#define DEVINFO_PART_PROD_REV_MASK                0xFF000000UL // Production revision
#define DEVINFO_PART_PROD_REV_SHIFT               24           // Bit position for production revision
#define DEVINFO_PART_DEVICE_FAMILY_MASK           0x00FF0000UL // Device Family, 0x47 for Gecko
#define DEVINFO_PART_DEVICE_FAMILY_SHIFT          16           // Bit position for device family
#define DEVINFO_PART_DEVICE_FAMILY_G              71           // Gecko Device Family
#define DEVINFO_PART_DEVICE_FAMILY_GG             72           // Giant Gecko Device Family
#define DEVINFO_PART_DEVICE_FAMILY_TG             73           // Tiny Gecko Device Family
#define DEVINFO_PART_DEVICE_FAMILY_LG             74           // Leopard Gecko Device Family
#define DEVINFO_PART_DEVICE_FAMILY_WG             75           // Wonder Gecko Device Family
#define DEVINFO_PART_DEVICE_FAMILY_ZG             76           // Zero Gecko Device Family
#define DEVINFO_PART_DEVICE_NUMBER_MASK           0x0000FFFFUL // Device number
#define DEVINFO_PART_DEVICE_NUMBER_SHIFT          0            // Bit position for device number


 // EFM32ZG_DEVINFO
typedef struct
{
  __I uint32_t CAL;          // Calibration temperature and checksum
  __I uint32_t ADC0CAL0;     // ADC0 Calibration register 0
  __I uint32_t ADC0CAL1;     // ADC0 Calibration register 1
  __I uint32_t ADC0CAL2;     // ADC0 Calibration register 2
  uint32_t     RESERVED0[2]; // Reserved
  __I uint32_t IDAC0CAL0;    // IDAC0 calibration register
  uint32_t     RESERVED1[2]; // Reserved
  __I uint32_t AUXHFRCOCAL0; // AUXHFRCO calibration register 0
  __I uint32_t AUXHFRCOCAL1; // AUXHFRCO calibration register 1
  __I uint32_t HFRCOCAL0;    // HFRCO calibration register 0
  __I uint32_t HFRCOCAL1;    // HFRCO calibration register 1
  __I uint32_t MEMINFO;      // Memory information
  uint32_t     RESERVED2[2]; // Reserved
  __I uint32_t UNIQUEL;      // Low 32 bits of device unique number
  __I uint32_t UNIQUEH;      // High 32 bits of device unique number
  __I uint32_t MSIZE;        // Flash and SRAM Memory size in KiloBytes
  __I uint32_t PART;         // Part description
} DEVINFO_TypeDef;

#define DEVINFO      ((DEVINFO_TypeDef *) 0x0FE081B0UL)     // DEVINFO base pointer

