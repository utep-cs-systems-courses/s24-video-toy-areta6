#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define BG_COLOR COLOR_BLACK
#define cRow (screenWidth / 2) //center row value
#define cCol (screenHeight / 2) //center col value


// shape code so i kept it simple mostly due to time constraint and also using this to teach myself for the final

void draw_triangle() //using draw pixel for this 
{
  for (short col = 0; col < 20; col++)
    {
      for (short row = 0; row < col; row++)
	{
	  drawPixel(cCol + col, cRow + row, COLOR_PINK);
	}
    }
}

void draw_square() //using fill rectangle and outline rectangle for this making 4 squares different quadrants
{
  fillRectangle(cCol + 5, cRow - 5, 15, 15, COLOR_YELLOW); //top right quadrant near center
  fillRectangle(10,10, 5, 5, COLOR_RED); //top left quadrant
  drawRectOutline(cCol - 30, cRow + 30, 20, 20, COLOR_GREEN); // bottom left quadrant
  drawRectOutline(screenHeight - 40, screenWidth - 40, 10,10, COLOR_BLUE); //bottom right quadrant
}

void draw_hourglass() //the fake quiz from class again i will make this and diagonal into assembly
{
  for (short col = 0; col < 20; col++)
    {
      for (short row = col; row < 20; row++)
      {
        drawPixel(cCol + col, cRow + row, COLOR_GREEN);
	drawPixel(cCol + col, cRow - row, COLOR_GREEN);
	drawPixel(cCol - col, cRow + row, COLOR_GREEN);
	drawPixel(cCol - col, cRow - row, COLOR_GREEN);
      }
    }
}

void draw_diagonal() //using same tech as triangle i will do the excercise problem from lab here
{
  for (short i = 0; i < 30; i++)
    {
      drawPixel(cCol + i, cRow - i, COLOR_BLUE);
    }
}
