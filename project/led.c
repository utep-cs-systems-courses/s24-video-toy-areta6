#include <msp430.h>
#include "led.h"
#include "switches.h"

//using demo 10 as a base
void led_init()
{
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;
  switch_state_changed =1;
  led_update();
}

void led_update() //code from demo 10 still
{
  if (switch_state_changed)
    {
      char ledflags = 0;

      ledflags |= switch_state_down ? LED_GREEN : 0;
      ledflags |= switch_state_down ? 0 : LED_RED;

      P1OUT &=(0xff - LEDS) | ledflags;
      P1OUT |= ledflags;
    }
  switch_state_changed = 0;
} //from demo 10

void led_green_on()
{
  P1OUT ^= LED_GREEN;
  P1OUT &= ~LED_RED;
  __delay_cycles(500000);
}

void led_red_on()//might not use this one but making it just in case
{
  P1OUT ^= LED_RED;
  P1OUT &= ~LED_GREEN;
  __delay_cycles(500000);
}

void leds_off() //turn off leds
{
  P1OUT &= ~LED_RED;
  __delay_cycles(500000);
  P1OUT &= ~LED_GREEN;
  __delay_cycles(500000);
}

//adding these for more functions in statemachine
void led_green_off() 
{
  P1OUT &= ~LED_GREEN;
  __delay_cycles(500000);
}

void led_red_off()
{
  P1OUT &= ~LED_RED;
  __delay_cycles(500000);
}

void led_alternate() //I'm pretty sure my LEDS on my launch pad are flipped compared to others so if the lights dont match up its cause of that
{
  P1OUT |= LED_GREEN;
  __delay_cycles(500000);
  P1OUT &= ~LED_RED;
  __delay_cycles(500000);
  P1OUT &= ~LED_GREEN;
  __delay_cycles(1500000);
  P1OUT |= LED_RED;
  __delay_cycles(1500000);
}

