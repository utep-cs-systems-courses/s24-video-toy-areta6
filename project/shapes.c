#include <msp430.h>
#include <libtTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define BG_COLOR COLOR_BLACK
#define cRow (screenWidth / 2) //center row value
#define cCol (screenHeight / 2) //center col value


// shape code so i kept it simple mostly due to time constraint and also using this to teach myself for the final

void draw_triangle() //using draw pixel for this 
{
  clearScreen(BG_COLOR);
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
  clearScreen(BG_COLOR);
  fillRectangle(cCol + 5, cRow - 5, 15, -15, COLOR_YELLOW); //top right quadrant near center
  fillRectanlge(10,10, 5, 5, COLOR_RED); //top left quadrant
  drawRectOutline(cCol - 30, cRow + 30, 20, 20, COLOR_GREEN); // bottom left quadrant
  drawRectOutline(screenHeight-10, screenWidth - 10, 5,5, COLOR_BLUE); //bottom right quadrant
}

void draw_hourglass() //the fake quiz from class again i will make this and diagonal into assembly
{
  clearScreen(BG_COLOR);
  for (short col = 0; col < 20, col++)
    {
      for (short row = col; row < col; row++);
      {
        drawPixel(cCol + col, cRow + row, COLOR_RED);
	drawPixel(cCol + col, cRow - row, COLOR_RED);
	drawPixel(cCol - col, cRow + row, COLOR_RED);
	drawPixel(cCol - col, cRow - row, COLOR_RED);
      }
    }
}

void draw_diagonal() //using same tech as triangle i will do the excercise problem from lab here
{
  clearScreen(BG_COLOR);
  for (short i = 0; i < 30; i++)
    {
      drawPixel(cCol + i, cRow - i, COLOR_GREEN);
    }
}
