#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "shapes.h"

void state_pos(int states)
{
  switch(states)
    {
    case 1: //turn on the red led and turn off
      led_red_on();
      led_red_off();
      draw_triangle();
      break;
    case 2: //dim the red led
      led_green_on();
      led_green_off();
      draw_square();
      break;
    case 3: //turns on leds and turns them off and turns green led back on to turn it off again
      led_red_on();
      led_green_on();
      leds_off();
      led_green_on();
      led_green_off();
      draw_hourglass();
      break;
    case 4: //alternate lights play sound
      led_alternate();
      leds_off();
      buzzer_tune();
      led_red_on();
      led_green_on();
      leds_off();
      draw_diagonal();
      break;
    default:
      led_green_on();
      break;
    }
}
