#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define LEN 25
#define WID 50
#define TIME 60
#define FPS 50

int i = 0, j = 0;
static unsigned short multiplicityMinutes = 1;
char level [LEN][WID];

struct player {

  int x;
  int y;
  //char body[HBODY][LBODY];

};

void cursorStart (void);
void destroyPlayer (struct player *, char [LEN][WID]);
void drawPlayer (struct player *, char [LEN][WID]);
void fpsTime (char *, char *);
void move (struct player *, char [LEN][WID]);
void Timer (long, char *, char *);



int main (void) {

  FILE * fp = fopen ("level1.txt", "r");

  struct player Player;

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

  fclose (fp);


  int yo = 5;
  int xo = 10;
  int check = 1;

  Player.x = xo;
  Player.y = yo;


  long time = 0;


  while (check == 1) {

    if (GetKeyState ('O') < 0) // ---> output
      check = 0;

    cursorStart ();

    move (&Player, level);

    for (i = 0; i < LEN ; i++)
      for (j = 0; j < WID; j++)
        putchar (level[i][j]);

    Sleep (FPS);
    time += FPS;

    Timer (time, &level[21][8], &level[21][9]);


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

  level[Player->y][Player->x] = '+';
  level[Player->y][Player->x + 1] = '-';
  level[Player->y][Player->x - 1] = '-';
  level[Player->y - 1][Player->x] = '0';
  level[Player->y + 1][Player->x] = '|';
  level[Player->y + 2][Player->x + 1] = '\\';
  level[Player->y + 2][Player->x - 1] = '/';

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

void cursorStart (void) {

  COORD position = {0, 0};
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsole, position);

}

int iTime = 5, jTime = 9;

void fpsTime (char * numClock1, char * numClock2) {


  if (iTime >= 0) {

    if (jTime >= 0) {

      * numClock1 = iTime + '0';
      * numClock2 = jTime + '0';

      if (iTime == 0)
        * numClock1 = ' ';

      jTime--;

    }

    if (jTime < 0) {

      jTime = 9;
      iTime --;

    }

  }

}

void Timer (long time, char * numClock1, char * numClock2) {

  if (time >= 1000 * multiplicityMinutes) {

    fpsTime (numClock1, numClock2);
    multiplicityMinutes++;

  }


}

/*

 0
-+-
 |
/ \


*/
