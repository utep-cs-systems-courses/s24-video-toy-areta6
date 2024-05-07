#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shapes.h"
#include "buzzer.h"

//pretty much noticed after trying to get it working beforehand that the wakedemo had it all build inside of it so i will try it with wakedemo.c

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!

#define LED BIT6/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

//char blue = 31, green = 0, red = 31; //no longer need this line
char statePos = 0; //state position
unsigned char step = 0;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}

void switch_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}

// axis zero for col, axis 1 for row

short drawPos[2] = {1,10}, controlPos[2] = {2, 10};
short colVelocity = 1, colLimits[2] = {1, screenWidth/2};

void draw_ball(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 3, 3, color);
}


void screen_update_ball() //keeping the ball due to it helping demonstrat wdt
{
  for (char axis = 0; axis < 2; axis ++)
    if (drawPos[axis] != controlPos[axis]) /* position changed? */
      goto redraw;
  return;/* nothing to do */
 redraw:
  draw_ball(drawPos[0], drawPos[1], COLOR_BLACK); /* erase */
  for (char axis = 0; axis < 2; axis ++)
    drawPos[axis] = controlPos[axis];
  draw_ball(drawPos[0], drawPos[1], COLOR_WHITE); /* draw */
}


short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;
  
  secCount ++;
  if (secCount >= 25) {/* 10/sec */
    {/* move ball */
      short oldCol = controlPos[0];
      short newCol = oldCol + colVelocity;
      if (newCol <= colLimits[0] || newCol >= colLimits[1])
	colVelocity = -colVelocity;
      else
	controlPos[0] = newCol;
    }
    
    {/* changed from update hourglass to states */
      if (switches & SW4) statePos = 4;
      if (switches & SW3) statePos = 3;
      if (switches & SW2) statePos = 2;
      if (switches & SW1) statePos = 1;
      if (step <= 30)
	step ++;
      else
	step = 0;
      secCount = 0;
      statePos = 0;//reset state pos to 0 
    }
    redrawScreen = 1;
  }
}

void update_shape();

void main()
{
  P1DIR |= LED;
  P1OUT |= LED; //turns on the red led for me
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();

  enableWDTInterrupts();
  or_sr(0x8); //GIE

  clearScreen(COLOR_BLACK);
  while (1)
    {
      if (redrawScreen)
	{
	  redrawScreen = 0;
	  update_shape();
	}
      P1OUT &= ~LED;
      or_sr(0x10);
      P1OUT |= LED;
    }
}

void screen_update_hourglass() //going to turn screen update hourglass into a form of state machine
{
  //static unsigned char row = screenHeight / 2, col = screenWidth / 2;
  static char lastStep = 0; //still want it to clean screen after a few seconds 
  if (step == 0 || (lastStep > step)) {
    clearScreen(COLOR_BLACK);
    lastStep = 0;
    statePos = 0;
  }
  else if (statePos == 1)
    {
      draw_triangle();
      buzzer_tune();
    }
  else if (statePos == 2)
    {
      draw_square();
      buzzer_tune();
    }
  else if (statePos == 3)
    {
      draw_hourglass();
      buzzer_tune();
      buzzer_tune();
    }
  else if (statePos == 4)
    {
      draw_diagonal();
      buzzer_tune();
    }
  }
}

void update_shape()
{
  screen_update_ball();
  screen_update_hourglass();
}



void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}
