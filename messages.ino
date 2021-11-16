/* messages.ino
 *  error, display, and other messages for the arduino snake game
 *  11/13/2021
 *  Zach Martin
 *  Aaron Olsen
 */
#include "parameters.h"

 // TODO: create game over message, create game begin message, show score, etc
void displayMsg(void)
{
  for (int d = 0; d < sizeof(snakeMessage[0]) - 7; d++) 
  {
    randomSeed(analogRead(A0));
    for (int col = 0; col < 8; col++) 
    {
      delay(15);
      for (int row = 0; row < 8; row++) 
      {
        // this reads the byte from the PROGMEM and displays it on the screen
         if(pgm_read_byte(&(snakeMessage[row][col + d])))
         {
          strip.setPixelColor(COLUMNS*row + col, foodColor);

         }
         else
         {
          strip.setPixelColor(COLUMNS*row + col, backgroundColor);
         }
         
        
        //strip.setPixelColor(((COLUMNS)*row + col), backgroundColor);
        //matrix.setLed(0, row, col, pgm_read_byte(&(snakeMessage[row][col + d])));
      }
      strip.show();
    }
  }
}

 // TODO: create game over message, create game begin message, show score, etc
void displayOverMsg(void)
{
  for (int d = 0; d < sizeof(gameOverMessage[0]) - 7; d++) 
  {
    randomSeed(analogRead(A0));
    for (int col = 0; col < 8; col++) 
    {
      delay(15);
      for (int row = 0; row < 8; row++) 
      {
        // this reads the byte from the PROGMEM and displays it on the screen
         if(pgm_read_byte(&(gameOverMessage[row][col + d])))
         {
          strip.setPixelColor(COLUMNS*row + col, foodColor);

         }
         else
         {
          strip.setPixelColor(COLUMNS*row + col, backgroundColor);
         }
         
        
        //strip.setPixelColor(((COLUMNS)*row + col), backgroundColor);
        //matrix.setLed(0, row, col, pgm_read_byte(&(snakeMessage[row][col + d])));
      }
      strip.show();
    }
  }
}
