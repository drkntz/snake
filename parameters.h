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

#define INITIAL_LENGTH 3  // initial lenght of snake

int gameOver = 0;
int win = 0;
struct point
{
  int row = 0, col = 0;
};

point snake;
point food;


enum  // Give numbers to directions
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};

int gameboard[ROWS][COLUMNS] = {};  // This is the main playing field
uint32_t color;
int snakeDirection = RIGHT;
int snakeLength = 3;

void printstuff(void);
// Function prototypes
void testSnake(void);

#endif
