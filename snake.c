#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "support.h"

#define XSIZE 20
#define YSIZE 20
#define RANDOMXMAX 17
#define RANDOMYMAX 17
#define RUNNING 1
#define ENDING 0
#define SPEED 200

struct snakeElement{
  int x;
  int y;
};

typedef struct snakeElement SNAKE;

SNAKE s1;
SNAKE s2;
SNAKE s3;

int gameStatus = RUNNING;

int newItem = 1;
int randomx;
int randomy;

int score = 0;

char startInput = 'd';

void changeSnakePosition(char playground[][XSIZE]){

  playground[s1.y][s1.x] = '@';
  playground[s2.y][s2.x] = 'o';
  playground[s3.y][s3.x] = 'o';
}

void placeFeedItem(char playground[][XSIZE]){

  srand(time(NULL));
  randomx = rand() % RANDOMXMAX + 1;
  randomy = rand() % RANDOMYMAX + 1;
}

void initializePlayground(char playground[][XSIZE]){

  for(int i = 0; i < YSIZE; i++){
    for(int j = 0; j < XSIZE; j++){
      if((i == 0 || i == YSIZE - 1) || (j == 0 || j == XSIZE - 1)){
        playground[i][j] = '*';
      }
      else {
        playground[i][j] = ' ';
      }
    }
  }

  if(newItem == 1){
    placeFeedItem(playground);
    newItem = 0;
  }

  playground[randomy][randomx] = '#';

  changeSnakePosition(playground);
}

void gamePlay(char playground[][XSIZE]){

  int temp1x = s1.x;
  int temp1y = s1.y;
  int temp2x = s2.x;
  int temp2y = s2.y;

  char input = support_readkey(SPEED);

  if(input != 'w' && input != 'a' && input != 's' && input != 'd'){
    input = startInput;
  }
  else{
    startInput = input;
  }

  switch(input){
    case 'w':
    s1.y--;
    s2.x = temp1x;
    s2.y = temp1y;
    s3.x = temp2x;
    s3.y = temp2y;
    break;
    case 'a':
    s1.x--;
    s2.x = temp1x;
    s2.y = temp1y;
    s3.x = temp2x;
    s3.y = temp2y;
    break;
    case 's':
    s1.y++;
    s2.x = temp1x;
    s2.y = temp1y;
    s3.x = temp2x;
    s3.y = temp2y;
    break;
    case 'd':
    s1.x++;
    s2.x = temp1x;
    s2.y = temp1y;
    s3.x = temp2x;
    s3.y = temp2y;
    break;
    default:
    break;
  }

  if(playground[s1.y][s1.x] == '*' || playground[s1.y][s1.x] == 'o'){
    gameStatus = ENDING;
  }

  if(playground[s1.y][s1.x] == '#'){
    score++;
    newItem = 1;
  }

}

void printPlayground(char playground[][XSIZE]){

  support_clear();

  initializePlayground(playground);

  for(int i = 0; i < YSIZE; i++){
    for(int j = 0; j < XSIZE; j++){
      printf("%c", playground[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char const *argv[]) {

  support_init();

  char playground[YSIZE][XSIZE];

  s1.x = 3;
  s1.y = 1;
  s2.x = 2;
  s2.y = 1;
  s3.x = 1;
  s3.y = 1;

  while(gameStatus == RUNNING){
    gamePlay(playground);
    printPlayground(playground);
    printf("\nPunkte: %d\n", score);
  }

  printf("\nVerloren!\n\n");

  return 0;
}
