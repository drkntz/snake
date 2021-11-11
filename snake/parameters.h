/*  parameters
 *  Setup parameters, constants, etc for the snake.ino project
 *  Zach Martin
 *  Aaron Olsen
 *  2021-11-10
 *  
 */
 
#ifndef PARAMETERS_H
#define PARAMETERS_H

#define LED_PIN 6       // Pin for neopixel serial data
#define LED_COUNT 64    // Size of matrix display
#define ROWS 8
#define COLUMNS 8


struct point
{
  int row = 0, col = 0;
};

point snake;

enum  // Give numbers to directions
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};

int displayMatrix[ROWS][COLUMNS] = {};  // This is the main playing field
uint32_t color;
int snakeDirection = DOWN;
int snakeLength = 3;

void printstuff(void);
// Function prototypes
void testSnake(void);

#endif
