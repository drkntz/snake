/* snake_handler.ino
 *  This file contains the subroutines to handle the snake's movement on the gameboard
 *  Zach Martin
 *  Aaron Olsen
 *  2021-11-10
 */

 #include "parameters.h"  // Settings file
 #include <Adafruit_NeoPixel.h>

  /* Lengthen the snake: 
   *  Each entry in the displayMatrix for the snake's body contains a value from 1 to n, where n is the length of the snake. 
   *  For example, a snake of length 5 has entries 1 2 3 4 5, where 5 is the head. The head coordinate corresponds with the value
   *  (snake.row, snake.col). 
   *  
   *  This section increments the entire snake body, adds the head
   */


 // calculate snake movement data
void calculateSnake() {
  switch (snakeDirection) {
    case UP:
      snake.row--;
      fixEdge();
      strip.setPixelColor(((COLUMNS)*snake.row + snake.col), color);
      break;

    case RIGHT:
      snake.col++;
      fixEdge();
      strip.setPixelColor(((COLUMNS)*snake.row + snake.col), color);
      break;

    case DOWN:
      snake.row++;
      fixEdge();
      strip.setPixelColor(((COLUMNS)*snake.row + snake.col), color);
      break;

    case LEFT:
      snake.col--;
      fixEdge();
      strip.setPixelColor(((COLUMNS)*snake.row + snake.col), color);
      break;

    default: // if the snake is not moving, exit
      return;
  }

  // if there is a snake body segment, this will cause the end of the game (snake must be moving)
  if (gameboard[snake.row][snake.col] > 1 && snakeDirection != 0) {
    // game over later TODO
    return;
  }

  // check if the food was eaten
  if (snake.row == food.row && snake.col == food.col) {
    food.row = -1; // reset food
    food.col = -1;

    // increment snake length
    snakeLength++;

    // increment all the snake body segments
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (gameboard[row][col] > 0 ) {
          gameboard[row][col]++;
        }
      }
    }
  }

  // add new segment at the snake head location
  gameboard[snake.row][snake.col] = snakeLength + 1; // will be decremented in a moment

  // decrement all the snake body segments, if segment is 0, turn the corresponding led off
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      // if there is a body segment, decrement it's value
      if (gameboard[row][col] > 0 ) {
        gameboard[row][col]--;
      }

      // display the current pixel
      if(gameboard[row][col] > 0)
      { 
        strip.setPixelColor(((COLUMNS)*row + col), color);
      }
      else
      {
        strip.setPixelColor(((COLUMNS)*row + col), (0, 255, 255));
      }
       //matrix.setLed(0, row, col, gameboard[row][col] == 0 ? 0 : 1);
      strip.show();
    }
  }
}

// causes the snake to appear on the other side of the screen if it gets out of the edge
void fixEdge() {
  snake.col < 0 ? snake.col += 8 : 0;
  snake.col > 7 ? snake.col -= 8 : 0;
  snake.row < 0 ? snake.row += 8 : 0;
  snake.row > 7 ? snake.row -= 8 : 0;
}


// if there is no food, generate one, also check for victory
void generateFood() {
  if (food.row == -1 || food.col == -1) {
    // self-explanatory
    if (snakeLength >= 64) {
      //win = true;
      return; // prevent the food generator from running, in this case it would run forever, because it will not be able to find a pixel without a snake
    }

    // generate food until it is in the right position
    do {
      food.col = random(8);
      food.row = random(8);
    } while (gameboard[food.row][food.col] > 0);
    strip.setPixelColor(((COLUMNS)*food.row + food.col), (0, 255, 0));
    strip.show();
  }
}


void handleGameStates() {
  if (gameOver || win) {
    //unrollSnake();

    //showScoreMessage(snakeLength - initialSnakeLength);

    //if (gameOver) showGameOverMessage();
    //else if (win) showWinMessage();

    // re-init the game
    //win = false;
    //gameOver = false;
    snake.row = random(8);
    snake.col = random(8);
    food.row = -1;
    food.col = -1;
    snakeLength = INITIAL_LENGTH;
    snakeDirection = 0;
    memset(gameboard, 0, sizeof(gameboard[0][0]) * 8 * 8);
    strip.clear();
  }
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
