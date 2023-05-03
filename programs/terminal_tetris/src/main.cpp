#include <iostream>  
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>
#include "baseitem.h"

const int STDIN = 0;
CellValue field[COUT_ROWS_WIDTH][COUT_ROWS_HEIGHT];
CellCoordinats figure_cells[FIGURE_CELL_COUT];

int interval { ONE_SECOND_IN_NS };

timespec time_start; 
timespec time_current;

Direction derection; 
Figure figure; 

int x_0 { 13 };
int y_0 { 1 };

int level { 0 };
int score { 0 };

void init()
{
   termios term;
   tcgetattr(STDIN, &term);
   term.c_lflag &= ~ICANON;
   tcsetattr(STDIN, TCSANOW, &term);
   setbuf(stdin, NULL);
   
   srand(time(NULL));
   
   auto set_field = [&](int x, int y) {
      if((x == 0) || (y == 0) || (x == COUT_ROWS_WIDTH - 1) || (y == COUT_ROWS_HEIGHT - 1)) {
         field[x][y] = BLOCK_WALL;  
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
}

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
            case BLOCK_WALL: 
               printf("\e[46m  \e[0m");   
               break;
            case BLOCK_SLEEP: 
               printf("\e[42m  \e[0m");   
               break;
            case BLOCK_ACTIVE: 
               printf("\e[40m  \e[0m");   
         }
         if(i == COUT_ROWS_WIDTH - 1) {
            printf("\n"); 
         }
      }
   }
   printf("< Lelel : %-38d | Score : %-39d > \n", level, score);  
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

void end_game()
{
   printf("\n[+]        Game Over           [+]\n"); 
   exit(0);
}

bool generateFigure(NewFigureInfo info)
{
   CellCoordinats new_figure_cells[FIGURE_CELL_COUT]; 
   
   if(info.figure == I) {
      if((info.derection == UP) || (info.derection == DOWN)) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x, info.y + 2 };
         new_figure_cells[3] = CellCoordinats { info.x, info.y + 3 };
      } else if((info.derection == LEFT) || (info.derection == RIGHT)) {
         new_figure_cells[0] = CellCoordinats { info.x - 1, info.y };
         new_figure_cells[1] = CellCoordinats { info.x, info.y };
         new_figure_cells[2] = CellCoordinats { info.x + 1, info.y };
         new_figure_cells[3] = CellCoordinats { info.x + 2, info.y };
      }
   } else if(info.figure == T) {
      if(info.derection == UP) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x - 1, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x + 1, info.y + 1 };
         new_figure_cells[3] = CellCoordinats { info.x, info.y + 1 };
      } else if(info.derection == DOWN) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[1] = CellCoordinats { info.x - 1, info.y };
         new_figure_cells[2] = CellCoordinats { info.x, info.y };
         new_figure_cells[3] = CellCoordinats { info.x + 1, info.y };
      } else if(info.derection == LEFT) {
         new_figure_cells[0] = CellCoordinats { info.x + 1, info.y };
         new_figure_cells[1] = CellCoordinats { info.x + 1, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x + 1, info.y + 2 };
         new_figure_cells[3] = CellCoordinats { info.x, info.y + 1 };
      } else if(info.derection == RIGHT) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x, info.y + 2 };
         new_figure_cells[3] = CellCoordinats { info.x + 1, info.y + 1 };
      }
   } else if(info.figure == J) {
      if(info.derection == UP) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x, info.y + 2 };
         new_figure_cells[3] = CellCoordinats { info.x - 1, info.y + 2 };
      } else if(info.derection == DOWN) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x, info.y + 2 };
         new_figure_cells[3] = CellCoordinats { info.x - 1, info.y };
      } else if(info.derection == LEFT) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y + 1};
         new_figure_cells[1] = CellCoordinats { info.x - 1, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x + 1, info.y + 1 };
         new_figure_cells[3] = CellCoordinats { info.x - 1, info.y };
      } else if(info.derection == RIGHT) {
         new_figure_cells[0] = CellCoordinats { info.x - 1, info.y + 1 };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x + 1, info.y + 1 };
         new_figure_cells[3] = CellCoordinats { info.x + 1, info.y };
      }
   } else if(info.figure == L) {
      if(info.derection == UP) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x, info.y + 2 };
         new_figure_cells[3] = CellCoordinats { info.x + 1, info.y + 2 };
      } else if(info.derection == DOWN) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x, info.y + 2 };
         new_figure_cells[3] = CellCoordinats { info.x + 1, info.y };
      } else if(info.derection == LEFT) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y + 1};
         new_figure_cells[1] = CellCoordinats { info.x - 1, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x + 1, info.y + 1 };
         new_figure_cells[3] = CellCoordinats { info.x + 1, info.y };
      } else if(info.derection == RIGHT) {
         new_figure_cells[0] = CellCoordinats { info.x - 1, info.y + 1 };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x + 1, info.y + 1 };
         new_figure_cells[3] = CellCoordinats { info.x - 1, info.y };
      }
   } else if(info.figure == S) {
      if((info.derection == UP) || info.derection == DOWN) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x + 1, info.y };
         new_figure_cells[2] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[3] = CellCoordinats { info.x - 1, info.y + 1 };
      } else if((info.derection == LEFT) || (info.derection == RIGHT)) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x + 1, info.y + 1 };
         new_figure_cells[3] = CellCoordinats { info.x + 1, info.y + 2 };
      } 
   } else if(info.figure == Z) {
      if((info.derection == UP) || info.derection == DOWN) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x - 1, info.y };
         new_figure_cells[2] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[3] = CellCoordinats { info.x + 1, info.y + 1 };
      } else if((info.derection == LEFT) || (info.derection == RIGHT)) {
         new_figure_cells[0] = CellCoordinats { info.x, info.y };
         new_figure_cells[1] = CellCoordinats { info.x, info.y + 1 };
         new_figure_cells[2] = CellCoordinats { info.x - 1, info.y + 1 };
         new_figure_cells[3] = CellCoordinats { info.x - 1, info.y + 2 };
      } 
   } else if(info.figure == O) {
      new_figure_cells[0] = CellCoordinats { info.x - 1, info.y };
      new_figure_cells[1] = CellCoordinats { info.x, info.y };
      new_figure_cells[2] = CellCoordinats { info.x - 1, info.y + 1 };
      new_figure_cells[3] = CellCoordinats { info.x, info.y + 1 };
   }
   
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      if((new_figure_cells[i].x > COUT_ROWS_WIDTH - 2) || new_figure_cells[i].y > COUT_ROWS_HEIGHT - 2) {
         return false;  
      } 
      if((field[new_figure_cells[i].x][new_figure_cells[i].y] == BLOCK_SLEEP) || (field[new_figure_cells[i].x][new_figure_cells[i].y] == BLOCK_WALL)) {
         return false; 
      } 
   }
   
   memcpy(figure_cells, new_figure_cells, sizeof(figure_cells));
   
   return true; 
}

void create_figure()
{
   derection = (Direction)(rand() % 4); 
   figure = (Figure)(rand() % 7); 
   NewFigureInfo info { derection, figure, x_0, y_0 };
   
   if(!generateFigure(info)) {
      end_game();   
   }  

   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      field[figure_cells[i].x][figure_cells[i].y] = BLOCK_ACTIVE;
   }
}

bool set_down() {
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      if((field[figure_cells[i].x][figure_cells[i].y + 1] == BLOCK_SLEEP) || (field[figure_cells[i].x][figure_cells[i].y + 1] == BLOCK_WALL)) {
         return false; 
      }
   } 
   
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      field[figure_cells[i].x][figure_cells[i].y] = FREE; 
      figure_cells[i].y = figure_cells[i].y + 1;
   }
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      field[figure_cells[i].x][figure_cells[i].y] = BLOCK_ACTIVE;
   }
   
   y_0++;
   
   return true;
};

bool set_right() {
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      if((field[figure_cells[i].x + 1][figure_cells[i].y] == BLOCK_SLEEP) || (field[figure_cells[i].x + 1][figure_cells[i].y] == BLOCK_WALL)) {
         return false; 
      }
   } 
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      field[figure_cells[i].x][figure_cells[i].y] = FREE; 
      figure_cells[i].x = figure_cells[i].x + 1;
   }
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      field[figure_cells[i].x][figure_cells[i].y] = BLOCK_ACTIVE;
   }
   
   x_0++;
   
   return true;
};

bool set_left() {
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      if((field[figure_cells[i].x - 1][figure_cells[i].y] == BLOCK_SLEEP) || (field[figure_cells[i].x - 1][figure_cells[i].y] == BLOCK_WALL)) {
         return false; 
      }
   } 
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      field[figure_cells[i].x][figure_cells[i].y] = FREE; 
      figure_cells[i].x = figure_cells[i].x - 1;
   }
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      field[figure_cells[i].x][figure_cells[i].y] = BLOCK_ACTIVE;
   }
   
   x_0--;
   
   return true;
}; 

void check_line()
{
   int j;
    
   auto find_line = [&j]() {
      for(int i = 1; i < COUT_ROWS_WIDTH - 1; i++)
      { 
         if(field[i][j] != BLOCK_SLEEP)
         {
            return false; 
         }
      } 
      return true;
   };
   
   auto delete_full_line = [&j]() {
      for(int i = 1; i < COUT_ROWS_HEIGHT - 2; i++)
      {
         field[i][j] == FREE;
      }
      //////////      
      for(int k = COUT_ROWS_HEIGHT - 2; k > 1; k--)
      {
         for(int i = 1; i < COUT_ROWS_WIDTH - 1; i++)
         {
            field[i][k] = field[i][k - 1];
         }
      } 
      
      score++;
      if(score >= 10) {
         score = 0;
         level++;
         if(interval > 200000000)
         {
            interval = interval * 0.8; 
         }
      }
   };
   
   for(j = COUT_ROWS_HEIGHT - 2; j > 0; j--)
   {
      if(find_line()) {
         delete_full_line();
      }
   } 
}

void step()
{
   auto sleep_figure = []() {
      for(int i = 0; i < FIGURE_CELL_COUT; i++) {
         field[figure_cells[i].x][figure_cells[i].y] = BLOCK_SLEEP;
      }
   }; 
   
   if(!set_down()) { 
      sleep_figure();
      x_0 = 13;
      y_0 = 1;
      check_line();
      create_figure();
   } 
}

int check_key() {
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

void set_new_direction()
{
   if(figure == O) {
      return; 
   } else if(derection == UP) {
      if((figure == I) || (figure == Z) || (figure == S)) {
         derection = LEFT;  
      } else {
         derection = DOWN;   
      }
   } else if(derection == DOWN) {
      derection = LEFT;  
   } else if(derection == LEFT) {
      if((figure == I) || (figure == Z) || (figure == S)) {
         derection = UP;  
      } else {
         derection = RIGHT;   
      }
   } else if(derection == RIGHT) {
      derection = UP;  
   }
   
   NewFigureInfo info { derection, figure, x_0, y_0 };
   
   if(!generateFigure(info)) {
      return; 
   }
   
   for(int i = 0; i < COUT_ROWS_WIDTH; i++)
   {
      for(int j = 0; j < COUT_ROWS_HEIGHT; j++)
      {
         if(field[i][j] == BLOCK_ACTIVE) {
            field[i][j] = FREE; 
         }
      }
   }
   
   for(int i = 0; i < FIGURE_CELL_COUT; i++) {
      field[figure_cells[i].x][figure_cells[i].y] = BLOCK_ACTIVE;
   }
}

void chande_pos(char k) 
{ 
    switch(k) {
       case 'w': 
          return;
       case 's': 
          set_down(); 
          break;
       case 'd': 
          set_right(); 
          break;
       case 'a': 
          set_left();   
          break; 
       case '\n':
          set_new_direction(); 
          break; 
    }
}

void start()
{
   char k; 
   create_figure(); 
   while(true) {
      if(check_key())
      {
         fgets(&k, 2, stdin);
         chande_pos(k); 
      }
     if(check_step_time()) {
        step(); 
     } 
     repaint();  
     sleep_ns(8000000);
   }
}

int main() 
{
   init(); 
   start();
   return 0;
}
