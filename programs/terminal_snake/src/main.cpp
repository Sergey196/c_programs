#include <iostream>  
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "baseitem.h"


CellValue field[COUT_ROWS_WIDTH][COUT_ROWS_HEIGHT] { { FREE } };
std::queue<CellCoordinats> snakeCells;

timespec time_start; 
timespec time_current; 

int interval { ONE_SECOND_IN_NS };
Direction direction { RIGHT };
int coutFood { 4 };
const int STDIN = 0;
int level { 0 };
int score { 0 };

void repaint()
{
   system("clear"); 
   
   for(int j = 0; j < COUT_ROWS_HEIGHT; j++)
   {
      for(int i = 0; i < COUT_ROWS_WIDTH; i++)
      {
         switch(field[i][j]) {
            case FREE: 
               printf("\e[44m  \e[0m");  
               break;
            case BLOCK: 
               printf("\e[46m  \e[0m");   
               break;
            case FOOD: 
               printf("\e[42m  \e[0m");   
               break;
            case SNAKE: 
               printf("\e[40m  \e[0m");   
         }
         if(i == COUT_ROWS_WIDTH - 1) {
            printf("\n"); 
         }
      }
   }
   printf("< Lelel : %-38d | Score : %-39d > \n", level, score);  
}

void foodRandom(int coutFields)
{
   int cellFood = coutFields;
   while(cellFood > 0)
   {
      int x = rand() % COUT_ROWS_WIDTH - 1;
      int y = rand() % COUT_ROWS_HEIGHT - 1; 
      if(field[x][y] == FREE)
      {
         cellFood--; 
         field[x][y] = FOOD;
      }
   }
}

void step()
{
   CellCoordinats start = snakeCells.back();
   CellCoordinats end = snakeCells.front();
   
   int newx { 1 };
   int newy { 1 };
   
   if(direction == UP) {
      newx = start.x;
      newy = start.y - 1;
   } else if(direction == DOWN) {
      newx = start.x;
      newy = start.y + 1;
   } else if(direction == RIGHT) {
      newx = start.x + 1;
      newy = start.y; 
   } else if(direction == LEFT) {
      newx = start.x - 1;
      newy = start.y; 
   }
   
   if(((newx < 1) || (newx > COUT_ROWS_WIDTH - 2) || (newy < 1) || (newy > COUT_ROWS_HEIGHT - 2)) || field[newx][newy] == SNAKE)
   {
      printf("\n[+]        Game Over           [+]\n"); 
      exit(0);
      return;
   }
       
   if(field[newx][newy] != FOOD) {
      field[end.x][end.y] = FREE; 
      snakeCells.pop(); 
   } else  {
     coutFood--;
     score++;
     if(coutFood < 3)
     {
        foodRandom(2);   
        coutFood += 2; 
        if(interval > 200000000)
        {
           interval = interval * 0.8; 
        }
        level++;
     }
   }
   
   snakeCells.push(CellCoordinats { newx, newy });
   field[newx][newy] = SNAKE;
}

bool check_step_time()
{
   clock_gettime(CLOCK_MONOTONIC, &time_current);
   if((ONE_SECOND_IN_NS * (time_current.tv_sec - time_start.tv_sec)) + (time_current.tv_nsec - time_start.tv_nsec) >= interval) {
      clock_gettime(CLOCK_MONOTONIC, &time_start);  
      clock_gettime(CLOCK_MONOTONIC, &time_current);
      return true;
   } else {
      return false; 
   }
}

void sleep_ns(long long time_ns)
{
   timespec time_start; 
   timespec time_current; 
   clock_gettime(CLOCK_MONOTONIC, &time_start);  
   clock_gettime(CLOCK_MONOTONIC, &time_current);
   while((ONE_SECOND_IN_NS * (time_current.tv_sec - time_start.tv_sec)) + (time_current.tv_nsec - time_start.tv_nsec) < time_ns)
   {
      clock_gettime(CLOCK_MONOTONIC, &time_current);  
   }
}


int check_key() {
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

//---------------------------------------------------------------------------
void setDirection(char k) 
{ 
    Direction _direction { UP };
    if(k == 'w') {
       _direction = UP;  
    } else if(k == 's') {
       _direction = DOWN;  
    } else if(k == 'd') {
       _direction = RIGHT;  
    } else if(k == 'a') {
       _direction = LEFT;  
    } 
    if((direction == UP && _direction != DOWN) || (direction == DOWN && _direction != UP) || (direction == RIGHT && _direction != LEFT) || (direction == LEFT && _direction != RIGHT) || (snakeCells.size() == 1))
    {
       direction = _direction;  
    }
}

void startGame()
{
   auto set_field = [&](int x, int y) {
      if((x == 0) || (y == 0) || (x == COUT_ROWS_WIDTH - 1) || (y == COUT_ROWS_HEIGHT - 1)) {
         field[x][y] = BLOCK;  
      } else {
         field[x][y] = FREE;  
      }
   };
   for(int i = 0; i < COUT_ROWS_WIDTH; i++)
   {
      for(int j = 0; j < COUT_ROWS_HEIGHT; j++)
      {
         set_field(i, j); 
      }
   }
   
   clock_gettime(CLOCK_MONOTONIC, &time_start);
   
   field[1][1] = SNAKE;
   snakeCells.push(CellCoordinats { 1, 1 });
   foodRandom(4);
   
   char k;
   while(true) 
   {
      if(check_step_time())
      {
         step(); 
      }
      if(check_key())
      {
         fgets(&k, 2, stdin);
         //std::cin >> k;
         setDirection(k); 
      }
      repaint(); 
      sleep_ns(8000000); 
   };
}

void init_terminal()
{
   termios term;
   tcgetattr(STDIN, &term);
   term.c_lflag &= ~ICANON;
   tcsetattr(STDIN, TCSANOW, &term);
   setbuf(stdin, NULL);
}

int main() 
{
   init_terminal(); 
   startGame(); 
   return 0;
}
