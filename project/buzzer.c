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
  //int a = 880;
  //int b = 494;
  //int c = 523; //these are randomly picked i want to have proper notes for next lab

  //int playn[10] = {a,b,c,c,a,b,b,a,c,a};
  //for some reason i get an error with these

  for (int i = 0; 0 < 3; i++)
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
  buzzer_set_period(0);
}
