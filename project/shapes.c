#include <msp430.h>
#include <libtTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define cRow (screenWidth / 2) //center row value
#define cCol (screenHeight / 2) //center col value


// shape code so i kept it simple mostly due to time constraint and also using this to teach myself for the final

void draw_triangle() //using draw pixel for this 
{
  for (short col = 0; col < 20; col ++)
    {
      for (short row = 0; row < col; row++)
	{
	  drawPixel(cCol + col, cRow + row, COLOR_PINK);
	}
    }
}

void draw_square() //using fill rectangle and outline rectangle for this making 4 squares different quadrants
{
  
}

void draw_hourglass() //the fake lab from class again i will make this and diagonal into assembly
{
  
}

void draw_diagonal() //using same tech as triangle i will do the excercise problem from lab here
{
  for (short i = 0; i < 30; i++)
    {
      drawPixel(cCol + i, cRow - i, COLOR_GREEN);
    }
}
