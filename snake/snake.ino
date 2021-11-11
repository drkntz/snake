/*  snake.ino
 *  A program that plays the game snake with an Arduino and matrix display
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

  strip.begin();           // INITIALIZE NeoPixel strip object
  strip.show();            // Turn OFF display
  strip.setBrightness(1); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.begin(9600);
}

void loop ()
{
  snakeCharmer();
  delay(100);
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
