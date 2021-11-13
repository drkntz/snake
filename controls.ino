/* controls.ino
 *  input controls for snake game
 *  created 11/13/2021
 *  Zach Martin
 *  Aaron Olsen
 */

 #include "parameters.h"

// Poll control inputs. Active low (IE connect to ground to trigger input)
 void readControls(void)
 {
  snakeDirection = digitalRead(LEFT_BUTTON) ? snakeDirection: LEFT;
  snakeDirection = digitalRead(RIGHT_BUTTON) ? snakeDirection: RIGHT;
  snakeDirection = digitalRead(UP_BUTTON) ? snakeDirection: UP;
  snakeDirection = digitalRead(DOWN_BUTTON) ? snakeDirection: DOWN;
 }
