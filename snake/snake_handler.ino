/* snake_handler.ino
 *  This file contains the subroutines to handle the snake's movement on the gameboard
 *  Zach Martin
 *  Aaron Olsen
 *  2021-11-10
 */

 #include "parameters.h"  // Settings file
 #include <Adafruit_NeoPixel.h>

// Handle the snake's movements
void snakeCharmer (void)
{
  strip.clear();
  color = strip.Color(255, 0, 0);
  switch(snakeDirection)
  {
    case UP:
      snake.row--;
    break;

    case DOWN:
      snake.row ++;
    break;

    case LEFT:
      snake.col--;
    break;

    case RIGHT:
      snake.col ++;
    break;
  }

  // "Wrap" snake around edge of display if it hits wall
  snake.row > 7 ? snake.row = 0 : 0;
  snake.col > 7 ? snake.col = 0 : 0;

  /* Lengthen the snake: 
   *  Each entry in the displayMatrix for the snake's body contains a value from 1 to n, where n is the length of the snake. 
   *  For example, a snake of length 5 has entries 1 2 3 4 5, where 5 is the head. The head coordinate corresponds with the value
   *  (snake.row, snake.col). 
   *  
   *  This section increments the entire snake body, adds the head
   */

  if(1) // if apple is encountered
  {
    displayMatrix[snake.row][snake.col] = snakeLength;
  }
  
  for(uint8_t row = 0; row < ROWS; row++)
  {
    for(uint8_t col = 0; col < COLUMNS; col++)
    {
     if(displayMatrix[row][col] > 0)
     {
        strip.setPixelColor(((COLUMNS)*row + col), color);
     }
    }
  }
  strip.show();
}





#if 0
 void testSnake(void)
 {
  color = strip.Color(1 + random(254), 1 + random(254), 1+ random(254));
  displayMatrix[snake.row][snake.col] = 1;
  

  snake.row++; // move down
  if(snake.row > 7)
  {
    snake.row = 0;
    snake.col++;
  }
  if(snake.col > 7)
  {
    snake.col = 0;

      for(uint8_t row = 0; row < ROWS; row++)
  {
    for(uint8_t col = 0; col < COLUMNS; col++)
    {
      displayMatrix[row][col] = 0;
    }
  }
  }
  strip.clear();
  for(uint8_t row = 0; row < ROWS; row++)
  {
    for(uint8_t col = 0; col < COLUMNS; col++)
    {
      if(displayMatrix[row][col] > 0)
      {
        strip.setPixelColor(((COLUMNS)*row + col), color) ;
      }
    }
  }
  strip.show();
 }
 #endif
