/*  snake.ino
 *  A program that plays the game snake with an Arduino and matrix display
 *  For more info (don't know if this is the original author): https://create.arduino.cc/projecthub/rishab8551/arduino-snake-game-using-arduino-and-martix-6c230c
 *  Designed for CMPEH 472 final project
 *  Zach Martin
 *  Aaron Olsen
 *  2021-11-10
 */

#include <Adafruit_NeoPixel.h>
#include "parameters.h"

 // Declare our NeoPixel strip object (see documentation)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(A0, INPUT);
  
  strip.begin();           // INITIALIZE NeoPixel strip object
  strip.show();            // Turn OFF display
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  Serial.begin(9600);

  // Initialize food and snake location
  randomSeed(analogRead(A0));
  food.row = random(8);
  food.col = random(8);
  snake.row = random(8);
  snake.col = random(8);

  // Define colors in (R, G, B). 256 bit.
  snakeColor = strip.Color(255, 0,0);
  backgroundColor = strip.Color(0, 0, 77);
  foodColor = strip.Color(204, 136, 0);

  // Define input pins
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  
}

void loop()
{

  for(uint16_t i = 0; ; i++)
  {
    readControls();

    if( i == snakeSpeed )
    {
      i = 0;
      calculateSnake();  // calculates snake parameters
      generateFood();    // if there is no food, generate one
      handleGameStates();
      strip.show();
    }
    
    delay(1);
  }
  
  
}



 
/*
 * useful functions 
 * 
 strip.clear();         //   Set all pixels in RAM to 0 (off)
 strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
 strip.show();                          //  Update strip to match
 strip.setPixelColor(c, color)
 strip.Color(255,   0,   0) // RGB color

 there are some other nifty functions. See docs from adafruit

 */
