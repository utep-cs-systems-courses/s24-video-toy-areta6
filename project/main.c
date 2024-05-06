#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "switches.h"
#include <stdio.h>

#define LED BIT6 //from the sounds of it i shoult not use my led files


void main()
{
  P1DIR |= LED;
  P1OUT |= LED;
  
  configureClocks(); //activating from timerlib
  switch_init();
  buzzer_init();
  lcd_init();
  
  enableWDTInterrupts();
  or_sr(0x8);
  clearScreen(COLOR_BLACK);

}
