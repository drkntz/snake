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
  
  // Move the snake head coordinates towards snakeDirection
  // Wrap to other side of display if head coordinates have gone off the screen
  switch (snakeDirection) {
    case UP:
      snake.row--;
      fixEdge();
      //strip.setPixelColor(((COLUMNS)*snake.row + snake.col), color);
      // TODO: remove this if not needed
      break;

    case RIGHT:
      snake.col++;
      fixEdge();
      //strip.setPixelColor(((COLUMNS)*snake.row + snake.col), color);
      break;

    case DOWN:
      snake.row++;
      fixEdge();
      //strip.setPixelColor(((COLUMNS)*snake.row + snake.col), color);
      break;

    case LEFT:
      snake.col--;
      fixEdge();
      //strip.setPixelColor(((COLUMNS)*snake.row + snake.col), color);
      break;

    default: // if the snake is not moving, exit
    return;
  }

  // Game is over if the snake head has landed on a body segment
  if (gameboard[snake.row][snake.col] > 1) {
    gameState = S_LOST; // Lost game
    return;
  }

  // check if the food was eaten
  if (snake.row == food.row && snake.col == food.col) 
  {
    // reset the food
    food.row = -1;
    food.col = -1;
    
    // increment snake length
    snakeLength++;

    // Make game faster
    snakeSpeed = (snakeSpeed*4)/5;

    // Increment all the snake body segments. 
    // This keeps the tip of the tail from being removed in the 
    // movement/decrement step below. 
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (gameboard[row][col] > 0 ) {
          gameboard[row][col]++;
        }
      }
    }
  }

  // Add new segment at the snake head location. This will create a snake body of length n+1, where the body segments
  // are entered into the gameboard as [1][2][3]...[n-1][n][n+1]. n+1 is at the NEW head location
  gameboard[snake.row][snake.col] = snakeLength + 1;

  // Decrement all of the snake body segments entered into the gameboard. 
  // In above example, the cells now contain [0][1][2]...[n-2][n-1][n], where n is at the NEW head location. 
  // The snake has now been moved!
  for (int row = 0; row < 8; row++) 
  {
    for (int col = 0; col < 8; col++) 
    {
      // Decrement snake body segment entries
      if (gameboard[row][col] > 0 ) 
      {
        gameboard[row][col]--;
      }

      // Add the pixel to the NeoPixel buffer
      if(gameboard[row][col] > 0) // Snake pixel
      { 
        strip.setPixelColor(((COLUMNS)*row + col), snakeColor);
      }
      else // "empty" pixel
      {
        strip.setPixelColor(((COLUMNS)*row + col), backgroundColor);
      }
    }
  }
  //strip.show(); // Show neopixel buffer
}


// Wraps the snake around the display if it falls off the edge
void fixEdge() {
  snake.col < 0 ? snake.col += 8 : 0;
  snake.col > 7 ? snake.col -= 8 : 0;
  snake.row < 0 ? snake.row += 8 : 0;
  snake.row > 7 ? snake.row -= 8 : 0;
  strip.setPixelColor(((COLUMNS)*snake.row + snake.col), snakeColor);
}


// Create a new food 
void generateFood() {
  if (food.row == -1 || food.col == -1) 
  {
    // self-explanatory
    if (snakeLength >= LED_COUNT) {
      gameState = S_WON; //win = true; // TODO: this seems like a dumb place to check for victory
      return; // prevent the food generator from running, in this case it would run forever, because it will not be able to find a pixel without a snake
    }

    // generate food until it is in the right position
    do 
    {
      randomSeed(analogRead(A0)); // Seed rand() with an unconnected pin
      food.col = random(COLUMNS);
      food.row = random(ROWS);
      Serial.print("generatingfood");
    } while (gameboard[food.row][food.col] > 0);
    Serial.print("\nFood is now at ");
    Serial.print(food.row);
    Serial.print(", ");
    Serial.println(food.col);
    
    
  }
  strip.setPixelColor(((COLUMNS)*food.row + food.col), foodColor);
}


void handleGameStates() {
  switch(gameState)
  {
    case S_RUN: // do nothing for now
    break;

    case S_WON:
      for(uint8_t i = 0; i < LED_COUNT; i++)
      {
        strip.setPixelColor(i, foodColor);
      }
      strip.show();
      for(;;){} // do nothing
   break;

   case S_LOST:
    displayOverMsg();
    Serial.println("Game lost");
    delay(5000);
    gameState = S_RUN;
   break;

    default:
    // do nothing
    break;
  }

  // TODO: if game won, display message and restart game
}
