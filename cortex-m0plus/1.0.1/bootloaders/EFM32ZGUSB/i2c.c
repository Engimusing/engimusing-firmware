/*****************************************************************************
******************************************************************************/

#include "config.h"
#include "i2c.h"

uint8_t i2c_txBuffer[I2C_TXBUFFER_SIZE];
uint8_t i2c_rxBuffer[I2C_RXBUFFER_SIZE];

uint8_t i2c_txBufferSize = sizeof(i2c_txBuffer);
uint8_t i2c_rxBufferIndex = sizeof(i2c_rxBuffer);

uint8_t i2c_rxBufferIndex;

// Transmission flags
volatile bool i2c_rxInProgress;
volatile bool i2c_startTx;


void i2c0_Init(int i2c_location)
{
  I2C_TypeDef *i2c = I2C0;

  CMU_ClockEnable(cmuClock_I2C0, true);

  if(i2c_location ==  I2C_ROUTE_LOCATION_LOC0) {
    // EFM32TG222 EFM32ZG222 EFM32WG840:  SDA: PA0  SCL: PA1
    GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE0_MASK) | GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER; // PA0
    GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE1_MASK) | GPIO_P_MODEL_MODE1_WIREDANDPULLUPFILTER; // PA1
    I2C0->ROUTE = (I2C0->ROUTE & ~_I2C_ROUTE_LOCATION_MASK) | I2C_ROUTE_LOCATION_LOC0;
  } else if(i2c_location == I2C_ROUTE_LOCATION_LOC1) {
    // EFM32ZG108 EFM32TG110 EFM32WG840:  SDA: PD6  SCL: PD7
    GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE6_MASK) | GPIO_P_MODEL_MODE6_WIREDANDPULLUPFILTER; // PD6
    GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE7_MASK) | GPIO_P_MODEL_MODE7_WIREDANDPULLUPFILTER; // PD7
    I2C0->ROUTE = (I2C0->ROUTE & ~_I2C_ROUTE_LOCATION_MASK) | I2C_ROUTE_LOCATION_LOC1;
  } else if(i2c_location == I2C_ROUTE_LOCATION_LOC6) {
    // EFM32ZG108:  SDA: PE12 SCL: PE13
    GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE12_MASK) | GPIO_P_MODEH_MODE12_WIREDANDPULLUPFILTER; // PE12
    GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE13_MASK) | GPIO_P_MODEH_MODE13_WIREDANDPULLUPFILTER; // PE13
    I2C0->ROUTE = (I2C0->ROUTE & ~_I2C_ROUTE_LOCATION_MASK) | I2C_ROUTE_LOCATION_LOC6;
  } else {
    printf0("Invalid I2C location\n\r");
    printf1("Invalid I2C location\n\r");
  }
  I2C0->ROUTE |= I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;  // Enable signals SCL, SDA
  if (I2C0->STATE & I2C_STATE_BUSY)  {I2C0->CMD = I2C_CMD_ABORT;}  // Exit the BUSY state out of RESET
  I2C0->CTRL = (I2C0->CTRL & ~_I2C_CTRL_CLTO_MASK) | I2C_CTRL_CLTO_160PCC;  // Enable the Clock Low Timeout counter
  I2C0->IEN |= I2C_IEN_ARBLOST | I2C_IEN_BUSERR | I2C_IEN_CLTO;  // Enable error interrupts
  NVIC_EnableIRQ(I2C0_IRQn);  // Enable interrupts in NVIC

  // Using default settings
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

  // Initializing the I2C
  I2C_Init(I2C0, &i2cInit);

  // Setting the status flags and index
  i2c_rxInProgress = false;
  i2c_startTx = false;
  i2c_rxBufferIndex = 0;

  i2c->CTRL |= I2C_CTRL_CLTO_40PCC | I2C_CTRL_GIBITO | I2C_CTRL_BITO_40PCC;
}


/*
  void i2c1_Init(int i2c_location)
  {
  CMU_ClockEnable(cmu_Clock_I2C1, true);

  if(i2c_location == I2C_ROUTE_LOCATION_LOC0) {
  // EFM32WG840:  SDA: PC4  SCL: PC5
  GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE4_MASK) | GPIO_P_MODEL_MODE4_WIREDANDPULLUPFILTER; // PC4
  GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE5_MASK) | GPIO_P_MODEL_MODE5_WIREDANDPULLUPFILTER; // PC5
  I2C1->ROUTE = (I2C1->ROUTE & ~_I2C_ROUTE_LOCATION_MASK) | I2C_ROUTE_LOCATION_LOC0;
  } else if(i2c_location == I2C_ROUTE_LOCATION_LOC1) {
  // EFM32WG840:  SDA: PB11 SCL: PB12
  GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE11_MASK) | GPIO_P_MODEH_MODE11_WIREDANDPULLUPFILTER; // PB11
  GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE12_MASK) | GPIO_P_MODEH_MODE12_WIREDANDPULLUPFILTER; // PB12
  I2C1->ROUTE = (I2C1->ROUTE & ~_I2C_ROUTE_LOCATION_MASK) | I2C_ROUTE_LOCATION_LOC1;
  } else {
  printf0("Invalid I2C location\n\r");
  printf1("Invalid I2C location\n\r");
  }
  I2C1->ROUTE |= I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;  // Enable signals SCL, SDA
  if (I2C1->STATE & I2C_STATE_BUSY)  {I2C1->CMD = I2C_CMD_ABORT;}  // Exit the BUSY state out of RESET
  I2C1->CTRL = (I2C1->CTRL & ~_I2C_CTRL_CLTO_MASK) | I2C_CTRL_CLTO_160PCC;  // Enable the Clock Low Timeout counter
  I2C1->IEN |= I2C_IEN_ARBLOST | I2C_IEN_BUSERR | I2C_IEN_CLTO;  // Enable error interrupts
  NVIC_EnableIRQ(I2C1_IRQn);  // Enable interrupts in NVIC
  }
*/

//===================================================================================
//	_wire.begin();
/*
  void begin(void)
  {
  if(onBeginCallback)
  onBeginCallback();

  // Enable High Frequency Peripherals
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_I2C0, true);

  I2C0->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN | (myLocation << _I2C_ROUTE_LOCATION_SHIFT);
  status = MASTER_IDLE;
  I2C_Init(I2C0, &i2cInit);
  I2C_Enable(I2C0, true);
  }
*/
//===================================================================================


void read_i2c_registers(void)
{
  I2C_TypeDef *i2c = I2C0;

  printf1("\n\r");
  printf1("I2C0_CTRL      = %08x\n\r",i2c->CTRL);
  printf1("I2C0_CMD       = %08x\n\r",i2c->CMD);
  printf1("I2C0_STATE     = %08x\n\r",i2c->STATE);
  printf1("I2C0_STATUS    = %08x\n\r",i2c->STATUS);
  printf1("I2C0_CLKDIV    = %08x\n\r",i2c->CLKDIV);
  printf1("I2C0_SADDR     = %08x\n\r",i2c->SADDR);
  printf1("I2C0_SADDRMASK = %08x\n\r",i2c->SADDRMASK);
  printf1("I2C0_RXDATA    = %08x\n\r",i2c->RXDATA);
  printf1("I2C0_RXDATAP   = %08x\n\r",i2c->RXDATAP);
  printf1("I2C0_TXDATA    = %08x\n\r",i2c->TXDATA);
  printf1("I2C0_IF        = %08x\n\r",i2c->IF);
  printf1("I2C0_IFS       = %08x\n\r",i2c->IFS);
  printf1("I2C0_IFC       = %08x\n\r",i2c->IFC);
  printf1("I2C0_IEN       = %08x\n\r",i2c->IEN);
  printf1("I2C0_ROUTE     = %08x\n\r",i2c->ROUTE);
}


//----------------------------------------------------------------------
// I2C_FLAG_WRITE       S+ADDR(W)+DATA0+P
// I2C_FLAG_READ        S+ADDR(R)+DATA0+P
// I2C_FLAG_WRITE_READ  S+ADDR(W)+DATA0+Sr+ADDR(R)+DATA1+P.
// I2C_FLAG_WRITE_WRITE S+ADDR(W)+DATA0+DATA1+P

static I2C_TypeDef *i2c = I2C0;

void received_nack(void)
{
  i2c->IFC      = I2C_IFC_NACK;
  i2c->CMD      = I2C_CMD_STOP;
  i2c->IFC      = I2C_IFC_MSTOP;
  printf1("nack\r\n");
}

void i2c_timeout(void)
{
  printf1("i2c timeout\r\n");
  i2c->CMD = (I2C_CMD_ABORT | I2C_CMD_CLEARTX | I2C_CMD_CLEARPC);
}

int wait_for_ack(void)
{
  while((i2c->IF & I2C_IF_ACK) == 0) {
    if(i2c->IF & I2C_IF_NACK) {
      received_nack();
      return 1;
    }
    if(i2c->IF & I2C_IF_CLTO) {
      i2c_timeout();
      return 2;
    }
  }
  i2c->IFC = I2C_IFC_ACK;
  return 0;
}

int i2c_write_byte(uint8_t address, uint8_t data)
{
  int ret = 0;

  I2C0->IFC = _I2C_IFC_MASK;
  i2c->TXDATA = address << 1; // Data not transmitted until START sent
  i2c->CMD = I2C_CMD_START;

  ret = wait_for_ack();
  if(ret) return ret;

  i2c->TXDATA = data;

  ret = wait_for_ack();
  if(ret) return ret;

  i2c->CMD = I2C_CMD_STOP;
  if (i2c->IF & I2C_IF_MSTOP) {
    i2c->IFC = I2C_IFC_MSTOP;
  }
  return 0;
}

int i2c_write_two_bytes(uint8_t address, uint8_t data1, uint8_t data2)
{
  int ret = 0;

  I2C0->IFC = _I2C_IFC_MASK;
  i2c->TXDATA = address << 1; // Data not transmitted until START sent
  i2c->CMD = I2C_CMD_START;

  ret = wait_for_ack();
  if(ret) return ret;

  i2c->TXDATA = data1;

  ret = wait_for_ack();
  if(ret) return ret;

  i2c->TXDATA = data2;

  ret = wait_for_ack();
  if(ret) return ret;

  i2c->CMD = I2C_CMD_STOP;
  if (i2c->IF & I2C_IF_MSTOP) {
    i2c->IFC = I2C_IFC_MSTOP;
  }
  return 0;
}

int wait_for_datav(void)
{
  while((i2c->IF & I2C_IF_RXDATAV) == 0) {
    if(i2c->IF & I2C_IF_CLTO) {
      i2c_timeout();
      return 2;
    }
  }
  i2c->IFC = I2C_IFC_ACK;
  return 0;
}

uint8_t i2c_read_byte(uint8_t address)
{
  uint8_t data;
  int ret = 0;

  I2C0->IFC = _I2C_IFC_MASK;
  i2c->TXDATA = (address << 1) | 0x01; // Data not transmitted until START sent
  i2c->CMD = I2C_CMD_START;

  ret = wait_for_ack();
  if(ret) return ret;

  i2c->CMD  = I2C_CMD_NACK;

  ret = wait_for_datav();
  if(ret) return ret;
  data = (uint8_t)(i2c->RXDATA);
  i2c->CMD  = I2C_CMD_NACK;

  i2c->CMD = I2C_CMD_STOP;
  if (i2c->IF & I2C_IF_MSTOP) {
    i2c->IFC = I2C_IFC_MSTOP;
  }
  return data;
}

uint16_t i2c_read_two_bytes(uint8_t address)
{
  uint8_t data1,data0;
  int ret = 0;

  i2c->IFC = _I2C_IFC_MASK;
  i2c->CTRL |= I2C_CTRL_AUTOACK;
  i2c->TXDATA = (address << 1) | 0x01; // Data not transmitted until START sent
  i2c->CMD = I2C_CMD_START;

  ret = wait_for_ack();
  if(ret) return ret;

  data1 = (uint8_t)(i2c->RXDATA);

  ret = wait_for_datav();
  if(ret) return ret;
  data0 = (uint8_t)(i2c->RXDATA);

  ret = wait_for_datav();
  if(ret) return ret;
  data1 = (uint8_t)(i2c->RXDATA);

  i2c->CMD = I2C_CMD_STOP;
  if (i2c->IF & I2C_IF_MSTOP) {
    i2c->IFC = I2C_IFC_MSTOP;
  }
  return (data0 << 8) | data1;
}


