#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "tbaseitem.h"

CellValue field[COUT_ROWS_COLUMS][COUT_ROWS_COLUMS];
const int STDIN { 0 }; 


void repaint()
{
   system("clear"); 
   
   auto printField = [](int i, int j) {
      switch(field[j][i]) {
         case FREE: 
            printf("\e[44m  \e[0m");  
            break;
         case BUTTON: 
            printf("\e[46m  \e[0m");   
            break;
         case BUTTONCLICK: 
            printf("\e[42m  \e[0m");   
            break;
      }
   };
   
   for(int j = 0; j < COUT_ROWS_COLUMS; j++)
   {
      for(int i = 0; i < COUT_ROWS_COLUMS; i++)
      {
         if(((i == 0) && (j == 0)) || ((i == COUT_ROWS_COLUMS - 1) && (j == COUT_ROWS_COLUMS - 1))) {
            printf("\e[44m%c\e[0m", 47);  
         } else if(((i == 0) && (j == COUT_ROWS_COLUMS - 1)) || ((i == COUT_ROWS_COLUMS - 1) && (j == 0))) {
            printf("\e[44m%c\e[0m", 92);  
         } else if((i == 0) || i == COUT_ROWS_COLUMS - 1) {
            printf("\e[44m%c\e[0m", 124);
         } else if(j == 0) {
            printf("\e[44m%c%c\e[0m", 45, 45);
         } else if(j == COUT_ROWS_COLUMS - 1) {
            printf("\e[44m%c%c\e[0m", 95, 95);
         } else {
            printField(i, j);
         }
         if(i == COUT_ROWS_COLUMS - 1) {
            printf("\n"); 
         }
      }
   } 
}
//---------------------------------------------------------------------------
void init()
{
   for(int j = 0; j < COUT_ROWS_COLUMS; j++)
   {
      for(int i = 0; i < COUT_ROWS_COLUMS; i++)
      {
         field[i][j] = FREE;
      }
   }
}
//---------------------------------------------------------------------------
void run()
{
   while(true) {
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
   init();
   run();
   return 0;
}
