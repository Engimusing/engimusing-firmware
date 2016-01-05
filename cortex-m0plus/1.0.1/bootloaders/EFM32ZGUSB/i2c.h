
#ifndef I2C_H
#define I2C_H

#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_dma.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_int.h"
#include "em_i2c.h"


/*
I2C Configurations:

Devices:
  TMP102         ADDR: 0x48
  TCS3472        ADDR: 0x29
  MLX90614       ADDR: 0x5A
  MPL3115A2      ADDR: 0x60
  HTU21D         ADDR: 0x40
  LSM303         ADDR: 0x1E
  MAG3110        ADDR: 0x0E
  MPU9150        ADDR: 0x68
  PCAL64         ADDR: 0x20
  MCP4018        ADDR: 0x2F
  SSC Pressure   ADDR: 0x28
  TMD2771        ADDR: 0x39

EFM32HG308:
  SDA: PE12  SCL: PE13

EFM32ZG108:
  SDA: PD6  SCL: PD7
  SDA: PE12 SCL: PE13

EFM32TG110:
  SDA: PD6  SCL: PD7

EFM32TG222:
  SDA: PA0   SCL: PA1

EFM32ZG222:
  SDA: PA0   SCL: PA1

EFM32WG840:
  SDA: PD6  SCL: PD7
  SDA: PC4  SCL: PC5
  SDA: PA0  SCL: PA1
  SDA: PB11 SCL: PB12


DF11  -  SDA: Pin8  SCL: Pin7
*/

#define HTU21D_ADDR     0x40
#define LSM303_ADDR     0x1E
#define MAG3110_ADDR    0x0E
#define MLX90614_ADDR   0x5A
#define MPL3115A2_ADDR  0x60
#define MPU9150_ADDR    0x68
#define PCAL64_ADDR     0x20
#define MCP4018_ADDR    0x2F
#define SSC_PRESS_ADDR  0x28
#define TCS3472_ADDR    0x29
#define TMD2771_ADDR    0x39
#define TMP102_ADDR     0x48

#define I2C_TXBUFFER_SIZE 8
#define I2C_RXBUFFER_SIZE 8

void i2c0_Init(int i2c_location);
void i2c1_Init(int i2c_location);
void beginTransmission(uint8_t address);
size_t write(uint8_t data);
uint8_t requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop);
uint8_t endTransmission(uint8_t sendStop);
int read(void);

void read_i2c_registers(void);
int i2c_write_byte(uint8_t address, uint8_t data);
int i2c_write_two_bytes(uint8_t address, uint8_t data1, uint8_t data2);
uint8_t i2c_read_byte(uint8_t address);
uint16_t i2c_read_two_bytes(uint8_t address);


#endif
