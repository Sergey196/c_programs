#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "tbaseitem.h"

CellValue field[COUT_ROWS_COLUMS][COUT_ROWS_COLUMS];
int current_position { 0 };
bool stop_flag { false };
int current_interval { START_INTERVAl };
int scores { 0 };
int level { 0 };
const int STDIN { 0 }; 


void repaint()
{
   system("clear"); 
   
   for(int j = 0; j < COUT_ROWS_COLUMS; j++)
   {
      for(int i = 0; i < COUT_ROWS_COLUMS; i++)
      {
         switch(field[j][i]) {
            case FREE: 
               printf("\e[44m  \e[0m");  
               break;
            case BLOCK: 
               printf("\e[46m  \e[0m");   
               break;
            case TUREL: 
               printf("\e[42m  \e[0m");   
               break;
            case PATRON: 
               printf("\e[40m  \e[0m");   
         }
         if(i == COUT_ROWS_COLUMS - 1) {
            printf("\n"); 
         }
      }
   }
   printf("< Lelel : %-38d | Score : %-39d > \n", level, scores); 
}
//---------------------------------------------------------------------------
void setRight()
{
   if(current_position < COUT_ROWS_COLUMS - 1) {
      field[COUT_ROWS_COLUMS - 1][current_position] = FREE;
      current_position++;
      field[COUT_ROWS_COLUMS - 1][current_position] = TUREL;
   }
}
//---------------------------------------------------------------------------
void setLeft()
{
   if(current_position > 0) {
      field[COUT_ROWS_COLUMS - 1][current_position] = FREE;
      current_position--;
      field[COUT_ROWS_COLUMS - 1][current_position] = TUREL;
   }
}
//---------------------------------------------------------------------------
void shoot()
{
   /*for(int i = COUT_ROWS_COLUMS - 1; i > -1; i--) 
   {
      if(field[i][current_position] == BLOCK) {
         field[i][current_position] = FREE;
         scores++;
         if(current_interval > MIN_INTERVAL) {
            current_interval = START_INTERVAl - (scores / SCORES_INTERVAl);
            level = scores / SCORES_INTERVAl;
         }
         break;
      }
   }*/
   field[COUT_ROWS_COLUMS - 1][current_position] = PATRON;
}
//---------------------------------------------------------------------------
int check_key() {
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
//---------------------------------------------------------------------------
int getCoutNotEmptyRows() 
{
   int row { 0 };
   for(int i = COUT_ROWS_COLUMS - 1; i > -1; i--) 
   {
      for(int j = COUT_ROWS_COLUMS - 1; j > -1; j--) 
      {
         if(field[i][j] == BLOCK) {
            row++;
            break;
         }
      }
   }
   return row;
};
//---------------------------------------------------------------------------
void setDownRows() 
{
   auto down_cell = [](int i, int j) {
      if(field[i][j] == BLOCK) {
         field[i][j] = FREE; 
         field[i + 1][j] = BLOCK; 
      }
   }; 
   for(int i = COUT_ROWS_COLUMS - 1; i > -1; i--) 
   {
      for(int j = COUT_ROWS_COLUMS - 1; j > -1; j--) 
      {
         down_cell(i, j);
      }
   }
};
//---------------------------------------------------------------------------
void generateNewRow() 
{
   for(int i = 0; i < COUT_ROWS_COLUMS; i++) 
   {
      field[0][i] = (CellValue)(rand() % 2);
   }
};
//---------------------------------------------------------------------------
void step()
{
   if(getCoutNotEmptyRows() > COUT_ROWS_COLUMS - 1) {
      stop_flag = true;
      return;
   }
   setDownRows();
   generateNewRow();
}
//---------------------------------------------------------------------------
void patron_new_pos(int i, int j) 
{
   if(field[i - 1][j] == BLOCK) {
      field[i - 1][j] = FREE; 
      scores++;
      if(current_interval > MIN_INTERVAL) {
         current_interval = START_INTERVAl - (scores / SCORES_INTERVAl);
         level = scores / SCORES_INTERVAl;
      }
   } else if(field[i - 1][j] == FREE) {
      field[i - 1][j] = PATRON; 
   }
};
//---------------------------------------------------------------------------
void patron_step(int i, int j) 
{
   if(field[i][j] == PATRON) {
      if((i == COUT_ROWS_COLUMS - 1) && (j == current_position)) {
         field[i][j] = TUREL; 
      } else {
         field[i][j] = FREE; 
      }
      if(i - 1 > -1) 
      {
         patron_new_pos(i, j);
      }
   }
};
//---------------------------------------------------------------------------
void patron_run()
{
   for(int i = 0; i < COUT_ROWS_COLUMS; i++) 
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++) 
      {
         patron_step(i, j);
      }
   }
}
//---------------------------------------------------------------------------
void start()
{
   int interval { 0 };
   char k;
   while(true) 
   {
      if(stop_flag) {
         std::cout << "TEST" << std::endl;
         break;
      }
      if(check_key())
      {
         k = getchar();
         if(k == 'a') { 
            setLeft(); 
         } else if(k == 'd') {
            setRight();
         } else if(k == 's') {
            shoot();
         }
      }
      patron_run();
      if(interval >= current_interval) {
         step();
         interval = 0;
      }
      interval++;
      repaint();
      usleep(SLEEP_INTERVAl);
   }
   
}
//---------------------------------------------------------------------------
int main()
{
   termios term;
   tcgetattr(STDIN, &term);
   term.c_lflag &= ~ICANON;
   tcsetattr(STDIN, TCSANOW, &term);
   setbuf(stdin, NULL);
   field[COUT_ROWS_COLUMS - 1][0] = TUREL;
   start();
   return 0;
}
