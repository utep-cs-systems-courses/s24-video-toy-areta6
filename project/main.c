#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "switches.h"
#include "led.h"

void main()
{
  configureClocks(); //activating from timerlib
  switch_init();
  buzzer_init();
  led_init();
  lcd_init();

  enableWDTInterrupts();
  or_sr(0x8);

  clearScreen(COLOR_BLUE);
  
}
