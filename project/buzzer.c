#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init() //pretty much the same code from demos
{
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void buzzer_set_period(short cycles)
{
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

void buzzer_tune()
{
  buzzer_set_period(880);
  __delay_cycles(500000);
  buzzer_set_period(0);
  __delay_cycles(500000);
  buzzer_set_period(523);
  __delay_cycles(500000);
  buzzer_set_period(0);
  __delay_cycles(500000);
  
}
