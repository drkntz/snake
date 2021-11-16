/*  parameters
 *  Setup parameters, constants, etc for the snake.ino project
 *  Zach Martin
 *  Aaron Olsen
 *  2021-11-10
 *  
 */
 
#ifndef PARAMETERS_H
#define PARAMETERS_H

// Input buttons, active low & internally pulled up
#define LEFT_BUTTON 2
#define RIGHT_BUTTON 3
#define UP_BUTTON 4
#define DOWN_BUTTON 5

// NeoPixel display settings
#define LED_PIN 6       // Pin for neopixel serial data
#define LED_COUNT 64    // Size of matrix display
#define ROWS 8
#define COLUMNS 8

#define INITIAL_LENGTH 3  // initial length of snake
#define INITIAL_SPEED 500 // Initial period of snake loop, in ms

// Structure for a 2d coordinate (row,col)
struct point
{
  int8_t row = 0, col = 0;
};

// Create two point coordinates
point snake;
point food;

// Enumerate snake movement directions
enum
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};

// Enumerate game States
enum
{
  S_RUN,
  S_WON,
  S_LOST
};

uint8_t gameState = S_RUN;

uint8_t gameboard[ROWS][COLUMNS] = {};  // This array contains the snake

// This contains the "Game Over" message.
// todo:  progmem?
const bool gameOver[ROWS][COLUMNS*11] = {
  0, 0, 0, 0, 0, 0, 0, 0,      0, 0, 1, 1, 1, 1, 0, 0,      0, 1, 1, 1, 1, 1, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 1, 1, 1, 1, 1, 0,      0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 1, 1, 1, 1, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 1, 1, 1, 1, 1, 0,      0, 1, 1, 1, 1, 1, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 1, 0, 0, 1, 1, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 1, 1, 0, 1, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 1, 0, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 1, 1, 1, 0, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 1, 0, 0,      0, 1, 1, 1, 1, 0, 0, 0,      0, 1, 1, 1, 1, 1, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 1, 1, 0,      0, 1, 1, 1, 1, 1, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 1, 0, 0, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 1, 0, 1, 0, 0, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 1, 0, 0, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 1, 0, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 1, 0, 0, 0, 0,      0, 1, 0, 0, 0, 0, 0, 0,      0, 1, 0, 0, 0, 1, 0, 0,      0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,      0, 0, 1, 1, 1, 1, 0, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 1, 1, 1, 1, 1, 1, 0,      0, 0, 0, 0, 0, 0, 0, 0,      0, 1, 1, 1, 1, 1, 1, 0,      0, 0, 1, 0, 0, 0, 0, 0,      0, 1, 1, 1, 1, 1, 1, 0,      0, 1, 0, 0, 0, 0, 1, 0,      0, 0, 0, 0, 0, 0, 0, 0,
  };

// Colors for the NeoPixel display
uint32_t snakeColor;
uint32_t backgroundColor;
uint32_t foodColor;
uint32_t headColor;

// Snake direction, body, length
volatile uint8_t snakeDirection = RIGHT; // volatile because it is used in interrupts
uint8_t snakeLength = INITIAL_LENGTH;
uint16_t snakeSpeed = INITIAL_SPEED;   // Period for main loop in ms

void generateFood(void);
void handleGameStates(void);
void fixEdge(void);

#endif
