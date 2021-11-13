/*  parameters
 *  Setup parameters, constants, etc for the snake.ino project
 *  Zach Martin
 *  Aaron Olsen
 *  2021-11-10
 *  
 */
 
#ifndef PARAMETERS_H
#define PARAMETERS_H

// Input buttons, active high
#define LEFT_PIN 2
#define RIGHT_PIN 3
#define UP_PIN 4
#define DOWN_PIN 5

// NeoPixel display settings
#define LED_PIN 6       // Pin for neopixel serial data
#define LED_COUNT 64    // Size of matrix display
#define ROWS 8
#define COLUMNS 8

#define INITIAL_LENGTH 4  // initial length of snake

// Structure for a 2d coordinate (row,col)
struct point
{
  uint8_t row = 0, col = 0;
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

// Colors for the NeoPixel display
uint32_t snakeColor;
uint32_t backgroundColor;
uint32_t foodColor;

// Snake direction and body length
uint8_t snakeDirection = RIGHT;
uint8_t snakeLength = INITIAL_LENGTH;

#endif
