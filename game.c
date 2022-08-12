#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define LEN 20
#define WID 50
#define TIME 60

int i = 0, j = 0;
char level [LEN][WID];

struct player {

  int x;
  int y;
  //char body[HBODY][LBODY];

};

void destroyPlayer (struct player * Player, char level [LEN][WID]);
void drawPlayer (struct player * Player, char level [LEN][WID]);
void move (struct player * Player, char level[LEN][WID]);
void Timer (void);



int main (void) {

  FILE * fp = fopen ("level1.txt", "r");

  struct player Player;

  char body[HBODY][LBODY] = {{' ', '0', ' '}, {' ', '0', ' '}, {' ', '0', ' '}, {'0', ' ', ' '}};

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


  int yo = 5;
  int xo = 10;
  int check = 1;

  Player.x = xo;
  Player.y = yo;

  for (i = 0; i < LEN; i++) {
    for (j = 0; j < WID; j++) {
      putchar (level[i][j]);
    }
  }


  struct player * pt;

  while (check == 1) {

    if (GetKeyState ('O') < 0) // ---> output
      check = 0;

    COORD position = {0, 0};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, position);

    move (&Player, level);

    for (i = 0; i < LEN; i++)
      for (j = 0; j < WID; j++)
        putchar (level[i][j]);

    Sleep (30);

  }

  return 0;
}

void move (struct player * Player, char level [LEN][WID]) {

  destroyPlayer (Player, level);

  if (GetKeyState ('D') < 0
    && level[Player->y][Player->x + 2] != '#'\
    && level[Player->y + 1][Player->x + 2] != '#'\
    && level[Player->y + 2][Player->x + 2] != '#'\
    && level[Player->y - 1][Player->x + 1] != '#')
      Player->x ++;

  if (GetKeyState ('A') < 0
    && level[Player->y][Player->x - 2] != '#'\
    && level[Player->y + 1][Player->x - 2] != '#'\
    && level[Player->y + 2][Player->x - 2] != '#'\
    && level[Player->y - 1][Player->x - 1] != '#')
      Player->x --;

  if (GetKeyState ('S') < 0
    && level[Player->y + 3][Player->x] != '#'\
    && level[Player->y + 3][Player->x + 1] != '#'\
    && level[Player->y + 3][Player->x - 1] != '#')
      Player->y ++;

  if (GetKeyState ('W') < 0
    && level[Player->y - 2][Player->x] != '#'\
    && level[Player->y - 1][Player->x + 1] != '#'\
    && level[Player->y - 1][Player->x - 1] != '#')
      Player->y --;

  drawPlayer (Player, level);

}

void drawPlayer (struct player * Player, char level [LEN][WID]) {

  level[Player->y][Player->x] = '0';
  level[Player->y][Player->x + 1] = '0';
  level[Player->y][Player->x - 1] = '0';
  level[Player->y - 1][Player->x] = '0';
  level[Player->y + 1][Player->x] = '0';
  level[Player->y + 2][Player->x + 1] = '0';
  level[Player->y + 2][Player->x - 1] = '0';

}

void destroyPlayer (struct player * Player, char level [LEN][WID]) {

  level[Player->y][Player->x] = ' ';
  level[Player->y][Player->x + 1] = ' ';
  level[Player->y][Player->x - 1] = ' ';
  level[Player->y - 1][Player->x] = ' ';
  level[Player->y + 1][Player->x] = ' ';
  level[Player->y + 2][Player->x + 1] = ' ';
  level[Player->y + 2][Player->x - 1] = ' ';

}

void Timer (void) {

  i = TIME;

  while (i > 0) {

    printf ("%d\r", i);
    Sleep (1000);
    i--;

  }

}

/*

 0
000
 0
0 0


*/
