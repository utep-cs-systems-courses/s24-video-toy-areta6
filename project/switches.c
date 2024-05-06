#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char switch_state_down, switch_state_changed, states;

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void switch_init()//copied over the code from demo again just using port 2
{
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_update();
}


void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  if(p2val & SW1 ? 0 : 1)
    {
      state_pos(1);
  }
  else if(p2val & SW2 ? 0 : 1)
    {
    state_pos(2);
  }
  else if(p2val & SW3 ? 0 : 1)
    {
    state_pos(3);
  }
  else if(p2val & SW4 ? 0 : 1)
    {
    state_pos(4);
  }
}
