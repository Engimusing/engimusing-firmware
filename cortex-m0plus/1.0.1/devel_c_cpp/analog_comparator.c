

// ACMP0_CH0 PC0  Pin 8
// ACMP0_CH1 PC1  Pin 7
// ACMP0_CH2 PC2  Pin 5
// ACMP0_CH3 PC3  Pin 4
// ACMP0_CH4 PC4  Pin 6
// ACMP0_O   PE13 Pin 10 loc0   PD6 Pin 3 loc 2

static uint8_t acmp_pos_ch[14] = {0xFF,0xFF,0xFF,0xFF,3,2,4,1,0,0xFF,0xFF,0xFF,0xFF,0xFF}
static uint8_t acmp_neg_ch[14] = {0xFF,0xFF,0xFF,0xFF,3,2,4,1,0,0xFF,0xFF,0xFF,0xFF,0xFF}

void ACMPpinMode(uint8_t pospin, uint8_t negpin, uint8_t outpin)
{
  if(mode == ACMP0_POSITIVE_INPUT) { // valid pins: 4-8
    if(acmp_pos_ch[pin] != 0xFF) {
      ACMP0->INPUTSEL &= ~_ACMP_INPUTSEL_POSSEL_MASK;
      ACMP0->INPUTSEL |= acmp_pos_ch[pin];
    }
  } else if(mode == ACMP0_NEGATIVE_INPUT) { // valid pins: 4-8
    if(acmp_neg_ch[pin] != 0xFF) {
      ACMP0->INPUTSEL &= ~_ACMP_INPUTSEL_NEGSEL_MASK;
      ACMP0->INPUTSEL |= acmp_neg_ch[pin];
    }
  } else if(mode == ACMP0_OUTPUT){ // valid pins: 3, 10
    if(pin == 3) {
      ACMP0->ROUTE = _ACMP_ROUTE_LOCATION_LOC2 | ACMP_ROUTE_ACMPPEN;
    } else if(pin == 10) {
      ACMP0->ROUTE = _ACMP_ROUTE_LOCATION_LOC0 | ACMP_ROUTE_ACMPPEN;
    }
  }
}

void enable_ACMP0(void)  {ACMP0->CTRL |= ACMP_CTRL_EN;}
void disable_ACMP0(void) {ACMP0->CTRL &= ~ACMP_CTRL_EN;}

void ACMP0_inactive_high(void) {ACMP0->CTRL |= ACMP_CTRL_INACTVAL;}
void ACMP0_inactive_low(void) {ACMP0->CTRL &= ~ACMP_CTRL_INACTVAL;}

void ACMP0_output_inverted(void) {ACMP0->CTRL |= ACMP_CTRL_GPIOINV;}
void ACMP0_output_not_inverted(void) {ACMP0->CTRL &= ~ACMP_CTRL_GPIOINV;}

void ACMP0_set_hysteresis(uint32_t hysteresis)
{
  ACMP0->CTRL = (ACMP0->CTRL & ~_ACMP_CTRL_HYSTSEL_MASK) | hysteresis;
}


void ACMP0_set_warmtime(uint32_t warmtime)
{
  ACMP0->CTRL = (ACMP0->CTRL & ~_ACMP_CTRL_WARMTIME_MASK) | warmtime;
}


void ACMP0_interrupt_edges(uint32_t edges)
{
  ACMP0->CTRL = (ACMP0->CTRL & ~(ACMP_CTRL_IRISE | ACMP_CTRL_IFALL)) | edges;
}


void ACMP0_set_bias(uint32_t fullbias, uint32_t halfbias, uint32_t biasprog)
{
  ACMP0->CTRL &= ~(_ACMP_CTRL_BIASPROG_MASK
                  | ACMP_CTRL_HALFBIAS
                  | ACMP_CTRL_FULLBIAS);
  ACMP0->CTRL |= (fullbias | halfbias | (biasprog << 24))
}

