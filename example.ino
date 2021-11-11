#include <strip.h>

//matrix settings
#define NUM_LEDS 64
#define DATA_PIN 3
#define BRIGHTNESS 8

//joystick settings
#define pinX    A2  // ось X джойстика
#define pinY    A1  // ось Y джойстика
#define swPin    2  // кнопка джойстика

int snake[256]; // array of snake elements
int snakeSize = 2;  // real snake size 
int snakeSpeed = 500;

int row;        // row number
int col;        // column number

int lastDirection = 135; // start direction
int i, newDirection, OlddX = 1, OlddY, f;

int red, green, blue, fred, fgreen, fblue; //colors
CRGB leds[NUM_LEDS];

void setup() {
  red = random(0, 255);
  green = random(0, 255);
  blue = random(0, 255);
  fred = random(127, 255);
  fgreen = random(127, 255);
  fblue = random(127, 255);
  
  Serial.begin(9600);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(swPin, INPUT);
  digitalWrite(swPin, HIGH);
    
  strip.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  strip.setBrightness(BRIGHTNESS);
  for( i=0; i<=255; i++ ){
    snake[i] = 0;
  }

  for( i=0; i<=snakeSize; i++ ){
    snake[i] = lastDirection+i;
  }
    
  f = random(0, 255);
  strip.show();
}

int Snakedirection(int last, int dX, int dY ){
  dX = map(dX, 0, 1000, -1, 1);
  dY = map(dY, 0, 1000, -1, 1);
  if(dX == 0 && dY == 0 && OlddX != dX){
    dX = OlddX;
  }
  if(dY == 0 && dX == 0 && OlddY != dY){
    dY = OlddY;
  }
  int newDirection = last;
  if( dX != 0 ){ // moving in X direction
    if ( row&1 ){
        if( col == 0 && dX == 1){ newDirection = last -15; } 
        else if( col == 15 && dX == -1){ newDirection = last +15; }
        else newDirection = last + dX; // четная
    } else {
        if( col == 0 && dX == 1){ newDirection = last +15; }
        else if( col == 15 && dX == -1 ){ newDirection = last -15; }
        else newDirection = last - dX; // не четная
    }
  } 
  if( dY < 0){ // moving in Y DOWN direction
    if(row == 15 && dY == -1){newDirection = col;}
    else if ( row&1 ){
      newDirection = last + (col*2)+1; // четная
    } else {
      newDirection = last + (16-col-1)+(16-col); // не четная
    }
  }
  if( dY > 0){ // moving in Y UP direction
    if( row == 0 && dY == 1){ newDirection = 255 - col;}
    else if ( row&1 ){
      newDirection = last - (last - 16*row) - (16 - col); // четная
    } else {
      newDirection = last - (col*2)-1; // не четная
    }
  }
  OlddX = dX;
  OlddY = dY;
  return newDirection;
}

int snakeMove(int snakeDirection){

  for( i=0; i<=255; i++ ){
    if( snake[i] == snakeDirection ){
      death();
    }
  }
  
  strip.clear();
  for(i=snakeSize; i>=1; i--){
    snake[i] = snake[i-1];
  }
  snake[0] = snakeDirection;
  for( i=0; i<=255; i++ ){
    if( snake[i] ){
      leds[snake[i]].setRGB(red, green, blue);
    }
  }
  strip.show();
  row = (int)(snakeDirection/16);  // row number 
  if ( row&1 ){
    col = (row+1) * 16 - snakeDirection - 1;
  } else {
    col = snakeDirection - row * 16;
  }
  return snakeDirection;
}

void food( int eaten ){
  if( eaten == f ){
    snakeSize++;
    f = random(0, 255);
    red = fred; 
    green = fgreen; 
    blue = fblue;
    fred = random(0, 255);
    fgreen = random(0, 255);
    fblue = random(0, 255);
    snakeSpeed = snakeSpeed / 1.1;
  } else {
    leds[f].setRGB(fred, fgreen, fblue);
    strip.show();
  }
}

void death(){
    snakeSize = 2;
    snakeSpeed = 500;
    red = 255;
    green = 0;
    blue = 0;  
}

void color(boolean sw){
  if(!sw){

    red = random(0,255);
    green = random(0,255);
    blue = random(0,255);
    
  }
}

void loop() {
  color( digitalRead(swPin) );
  newDirection = Snakedirection(lastDirection, analogRead(pinX), analogRead(pinY));
  lastDirection = snakeMove(newDirection);
  food(newDirection);
  delay(snakeSpeed);
}
