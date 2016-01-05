#include "config.h"
#include "timer.h"

static volatile int timer_int = 0;

void init_timer(void)
{
  CMU_ClockEnable(cmuClock_TIMER0, true);

  TIMER0->CTRL = TIMER_CTRL_MODE_UP | TIMER_CTRL_OSMEN | TIMER_CTRL_DEBUGRUN;
  NVIC_EnableIRQ(TIMER0_IRQn);  // Enable TIMER0 interrupt vector in NVIC
  TIMER_IntEnable(TIMER0, TIMER_IF_OF);
}


void delayt(uint32_t val)
{
  timer_int = 0;
  TIMER_IntEnable(TIMER0, TIMER_IF_OF);
  TIMER0->CNT = 0;
  TIMER_TopSet(TIMER0,val);
  TIMER0->CMD = TIMER_CMD_START;
  // EMU_EnterEM1();
  while(timer_int == 0) {
  }
}



void TIMER0_IRQHandler(void)
{ 
  timer_int = 1;
  TIMER_IntClear(TIMER0, TIMER_IF_OF);  // Clear flag for TIMER0 overflow interrupt
}



