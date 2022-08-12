#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define LEN 20
#define WID 50

int i = 0, j = 0;
char level [LEN][WID];

struct player {

  int x;
  int y;
  char character;

};

struct coords {

  int X;
  int Y;

};

void move (struct player Player);


int main (void) {

  FILE * fp = fopen ("level1.txt", "r");

  struct player Player;
  Player.character = '0';

  char ch;

  fseek (fp, 0, SEEK_SET);

  i = 0;
  j = 0;

  while ((ch = getc (fp)) != EOF) {

    if (ch == '\n') {
      level[i][j] = '\0';
      i++;
      j = 0;
    }

    level[i][j] = ch;
    j++;

  }


  int xo = 5;
  int yo = 10;
  int check = 1;

  Player.x = xo;
  Player.y = yo;
  level[xo][yo] = Player.character;

  for (i = 0; i < LEN; i++) {
    for (j = 0; j < WID; j++) {
      putchar (level[i][j]);
    }
  }


  while (check == 1) {

    if (GetKeyState ('O') < 0) // ---> output
      check = 0;

    COORD position = {0, 0};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, position);

    level[Player.x][Player.y] = ' ';

    if (GetKeyState ('D') < 0)
      Player.y ++;
    if (GetKeyState ('A') < 0)
      Player.y --;
    if (GetKeyState ('S') < 0)
      Player.x ++;
    if (GetKeyState ('W') < 0)
      Player.x --;

    level[Player.x][Player.y] = '0';

    for (i = 0; i < LEN; i++) {
      for (j = 0; j < WID; j++) {
        putchar (level[i][j]);
      }
    }


    Sleep (50);

  }

  return 0;
}

void move (struct player Player) {

  if (GetKeyState ('D') < 0)
    Player.x ++;
  if (GetKeyState ('A') < 0)
    Player.x --;
  if (GetKeyState ('S') < 0)
    Player.y --;
  if (GetKeyState ('W') < 0)
    Player.y ++;

}
