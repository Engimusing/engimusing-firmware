#pragma once

#include "io_types.h"

#define DEVINFO_HFRCOCAL1_BAND21      0x000000FFUL        // 21MHz tuning value for HFRCO, mask */

 // EFM32ZG_DEVINFO
typedef struct
{
  __I uint32_t CAL;          // Calibration temperature and checksum */
  __I uint32_t ADC0CAL0;     // ADC0 Calibration register 0 */
  __I uint32_t ADC0CAL1;     // ADC0 Calibration register 1 */
  __I uint32_t ADC0CAL2;     // ADC0 Calibration register 2 */
  uint32_t     RESERVED0[2]; // Reserved */
  __I uint32_t IDAC0CAL0;    // IDAC0 calibration register */
  uint32_t     RESERVED1[2]; // Reserved */
  __I uint32_t AUXHFRCOCAL0; // AUXHFRCO calibration register 0 */
  __I uint32_t AUXHFRCOCAL1; // AUXHFRCO calibration register 1 */
  __I uint32_t HFRCOCAL0;    // HFRCO calibration register 0 */
  __I uint32_t HFRCOCAL1;    // HFRCO calibration register 1 */
  __I uint32_t MEMINFO;      // Memory information */
  uint32_t     RESERVED2[2]; // Reserved */
  __I uint32_t UNIQUEL;      // Low 32 bits of device unique number */
  __I uint32_t UNIQUEH;      // High 32 bits of device unique number */
  __I uint32_t MSIZE;        // Flash and SRAM Memory size in KiloBytes */
  __I uint32_t PART;         // Part description */
} DEVINFO_TypeDef;

#define DEVINFO      ((DEVINFO_TypeDef *) 0x0FE081B0UL)     // DEVINFO base pointer

