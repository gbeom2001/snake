#include "console.h"
#include <iostream>
#include <random>
#include <ctime>

#define BOARD_SIZE 10
#define MOVE_DELAY 15
#define WALL_VERTICAL_STRING "┃"
#define WALL_HORIZONTAL_STRING "━"
#define WALL_RIGHT_TOP_STRING "┓"
#define WALL_LEFT_TOP_STRING "┏"
#define WALL_RIGHT_BOTTOM_STRING "┛"
#define WALL_LEFT_BOTTOM_STRING "┗"
#define SNAKE_STRING "■"
#define SNAKE_BODY_STRING "■"
#define APPLE_STRING "●"

void draw(int x, int y, const char *s);
void draw(int x, int y, std::string s);
void wait();

using namespace std;

int window[BOARD_SIZE-2][BOARD_SIZE-2];
int a = 0;
int b = 0;

int x = 0;
int y = 0;

int apple = 0;
int body = 0;

void handleInput() {
  if (console::key(console::K_LEFT)) {
    x--;
  }
  if (console::key(console::K_RIGHT)) {
    x++;
  }
  if (console::key(console::K_UP)) {
    y--;
  }
  if (console::key(console::K_DOWN)) {
    y++;
  }
}

void restrictInScreen() {
  // x, y 위치를 화면의 최대 크기에서 벗어나지 않게 한다.
  if (x < 0)
    x = 0;
  if (x >= console::SCREEN_WIDTH)
    x = console::SCREEN_WIDTH - 1;
  if (y < 0)
    y = 0;
  if (y >= console::SCREEN_HEIGHT)
    y = console::SCREEN_HEIGHT - 1;
}

void drawapple() 
{
  
    mt19937 rng(time(nullptr)); 
    uniform_int_distribution<int> dis(1, BOARD_SIZE-2);
    a=dis(rng);
    b=dis(rng);
    if(window[x][y]==1)
    {
      drawapple();
    }
    else console::draw( a, b, APPLE_STRING);

  
}




int main()
{
  console::init();
  console::draw( x, y, WALL_LEFT_TOP_STRING);
  console::draw( x, y+BOARD_SIZE-1, WALL_LEFT_BOTTOM_STRING);
  console::draw( x+BOARD_SIZE-1, y, WALL_RIGHT_TOP_STRING);
  console::draw( x+BOARD_SIZE-1, y+BOARD_SIZE-1, WALL_RIGHT_BOTTOM_STRING);
  x++;
  y++;

  for( x; x<BOARD_SIZE-1;x++)
  {
    console::draw( x, y, WALL_HORIZONTAL_STRING);
    console::draw( x, y+BOARD_SIZE-1, WALL_HORIZONTAL_STRING);
  }
    
  for( y; y<BOARD_SIZE-1;y++)
  {
    console::draw( x, y, WALL_VERTICAL_STRING);
    console::draw( x+BOARD_SIZE-1, y, WALL_VERTICAL_STRING);
  }
  x=x/2;
  y=y/2;
  string s=to_string(body);
  console::draw( x-3, BOARD_SIZE, "Score: " );
  console::draw( x+4, BOARD_SIZE, "Score:  " );

  console::draw( x, y, SNAKE_STRING);
  for(int i = 0;i<body;i++)
  {
    console::draw( x, y, SNAKE_BODY_STRING);
  }
  window[x][y]=1;
  drawapple();
  handleInput();
  if(x==a&&y==b) 
  {
    apple+=10;
    body+=1;
  }
  wait();

  return 0;
}