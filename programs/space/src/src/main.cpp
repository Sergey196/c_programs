#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include "tbaseitem.h"

CellValue field[COUT_ROWS][COUT_COLUMS];
bool fieldShips[COUT_ROWS][COUT_COLUMS];
int current_position { 1 };
bool stop_flag { false };
int current_interval { START_INTERVAl };
int scores { 0 };
int level { 0 };
const int STDIN { 0 }; 

std::vector<ShipInfo> ships;

void repaint()
{
   system("clear"); 
   
   for(int j = 0; j < COUT_ROWS; j++)
   {
      for(int i = 0; i < COUT_COLUMS; i++)
      {
         if(fieldShips[j][i] != 0) {
            printf("\e[41m  \e[0m"); 
            continue;
         }
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
            case PATRON_SHIP: 
               printf("\e[40m  \e[0m");   
               break;
            case PATRON_USER: 
               printf("\e[40m  \e[0m");   
               break;
         }
         if(i == COUT_COLUMS - 1) {
            printf("\n"); 
         }
      }
   }
   printf("< Lelel : %-38d | Score : %-39d > \n", level, scores); 
}
//---------------------------------------------------------------------------
void removeTurel()
{
   field[COUT_ROWS - 1][current_position - 1] = FREE;
   field[COUT_ROWS - 1][current_position] = FREE;
   field[COUT_ROWS - 1][current_position + 1] = FREE;
   field[COUT_ROWS - 2][current_position] = FREE;
}
//---------------------------------------------------------------------------
void setPositionTurel()
{
   field[COUT_ROWS - 1][current_position - 1] = TUREL;
   field[COUT_ROWS - 1][current_position] = TUREL;
   field[COUT_ROWS - 1][current_position + 1] = TUREL;
   field[COUT_ROWS - 2][current_position] = TUREL;
}
//---------------------------------------------------------------------------
void setRight()
{
   if(current_position >= COUT_COLUMS - 2) {
      return;
   }
   removeTurel();
   current_position++;
   setPositionTurel();
}
//---------------------------------------------------------------------------
void setLeft()
{
   if(current_position <= 1) {
      return;
   }
   removeTurel();
   current_position--;
   setPositionTurel();
}
//---------------------------------------------------------------------------
void shootPlayer()
{
    if(field[COUT_ROWS - 3][current_position] == FREE) {
       field[COUT_ROWS - 3][current_position] = PATRON_USER;
    } 
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
   return 0;
};
//---------------------------------------------------------------------------
void setShip(ShipInfo info) 
{
   fieldShips[info.cell.x][info.cell.y] = true;
   fieldShips[info.cell.x][info.cell.y + 1] = true;
   fieldShips[info.cell.x][info.cell.y + 2] = true;
   fieldShips[info.cell.x + 1][info.cell.y + 1] = true;
};
//---------------------------------------------------------------------------
void shipClear(ShipInfo info) 
{
   fieldShips[info.cell.x][info.cell.y] = false;
   fieldShips[info.cell.x][info.cell.y + 1] = false;
   fieldShips[info.cell.x][info.cell.y + 2] = false;
   fieldShips[info.cell.x + 1][info.cell.y + 1] = false;
};
//----------------------------------------------------------------------------
void generateRows() 
{
   int x0 { 1 };
   int y0 { 1 };
   bool is_right_left { true };
   
   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 8; j++)
      {
         ShipInfo info;
         info.cell.x = x0;
         info.cell.y = y0;
         info.is_right_left = is_right_left;
         info.start_pos_y = y0;
         ships.push_back(info);

         setShip(info); 
         y0 += 4;
      }
      is_right_left = !is_right_left;
      if(is_right_left) {
         y0 = 1;
      } else {
         y0 = 5;
      }
      x0 += 3;
   }
};
//---------------------------------------------------------------------------
void setShipsPosition()
{
   auto toRight = [](ShipInfo &ship) {
      if((ship.start_pos_y + 4) > ship.cell.y) {
         ship.cell.y = ship.cell.y + 1;
      } else {
         ship.is_right_left = !ship.is_right_left;
         ship.start_pos_y = ship.cell.y;
         ship.cell.y = ship.cell.y - 1;
      }
   };
   
   auto toLeft = [](ShipInfo &ship) {
      if((ship.start_pos_y - 4) < ship.cell.y) {
         ship.cell.y = ship.cell.y - 1;
      } else {
         ship.is_right_left = !ship.is_right_left;
         ship.start_pos_y = ship.cell.y;
         ship.cell.y = ship.cell.y + 1;
      }
   };
   for(auto &ship : ships) 
   {
      shipClear(ship); 
      if(ship.is_right_left) {
         toRight(ship);
      } else {
         toLeft(ship);
      }
   }
   for(auto ship : ships) 
   {
      setShip(ship); 
   }
}
//---------------------------------------------------------------------------
void playerShootUp()
{
   //CellValue field[COUT_ROWS][COUT_COLUMS];
   auto lowTimeout = []() {
      scores++;
      if(current_interval > MIN_INTERVAL) {
         current_interval = START_INTERVAl - ((scores / SCORES_INTERVAl) * 5);
         level = scores / SCORES_INTERVAl;
      }
      if(ships.size() == 0) {
         stop_flag = true;
      }
   };
   
   auto eraseShip = [lowTimeout](int x, int y) {
      for(auto ship = ships.begin(); ship != ships.end();)
      {
         if(((ship->cell.x == x) && (ship->cell.y == y)) || ((ship->cell.x == x) && (ship->cell.y + 1 == y)) || ((ship->cell.x == x) && (ship->cell.y + 2 == y)) || ((ship->cell.x + 1 == x) && (ship->cell.y + 1 == y))) {
            shipClear(*ship); 
            ships.erase(ship);
            lowTimeout();
            break;
         } else {
            ship++;
         }
      }
   };
   
   auto patronNewPosition = [eraseShip](int x, int y) {
      if(field[x][y] == PATRON_USER) {
         field[x][y] = FREE;
         if(x - 1 < 0) {
            return;
         }
         
         if(fieldShips[x - 1][y]) {
            eraseShip(x - 1, y);
            return;
         }
         
         if(field[x - 1][y] == FREE) {
            field[x - 1][y] = PATRON_USER;
         } else if((field[x - 1][y] == BLOCK) || (field[x - 1][y] == PATRON_SHIP)) {
            field[x - 1][y] = FREE;
         }
      }
   };
   
   
   for(int i = 0; i < COUT_ROWS; i++) 
   {
      for(int j = 0; j < COUT_COLUMS; j++)
      {
         patronNewPosition(i, j);
      }
   }
}
//---------------------------------------------------------------------------
void shipsShootDown()
{
   auto patronNewPosition = [](int x, int y) {
      if(field[x][y] == PATRON_SHIP) {
         field[x][y] = FREE;
         if(x + 1 > COUT_ROWS - 1) {
            return;
         }
         if(field[x + 1][y] == FREE) {
            field[x + 1][y] = PATRON_SHIP;
         } else if((field[x + 1][y] == BLOCK) || (field[x + 1][y] == PATRON_USER)) {
            field[x + 1][y] = FREE;
         } else if(field[x + 1][y] == TUREL) {
            stop_flag = true;
         } 
      }
   };
   
   
   for(int i = COUT_ROWS - 1; i > -1; i--) 
   {
      for(int j = COUT_COLUMS - 1; j > -1; j--)
      {
         patronNewPosition(i, j);
      }
   }
}
//---------------------------------------------------------------------------
void shipsShoot()
{  
   for(auto ship : ships) 
   {
      if(((rand() % 8) == 1) && field[ship.cell.x + 2][ship.cell.y + 1] == FREE) {
         field[ship.cell.x + 2][ship.cell.y + 1] = PATRON_SHIP;
      }
   }
}
//---------------------------------------------------------------------------
void step()
{
   setShipsPosition();
   shipsShootDown();
   shipsShoot();
}
//---------------------------------------------------------------------------
void start()
{
   int interval { 0 };
   char k;
   while(true) 
   {
      if(stop_flag) {
         std::cout << "TEST = " << current_interval << std::endl;
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
            shootPlayer();
         }
      }
      playerShootUp();
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
void setBlocks()
{
   auto addBlock = [](int pos) {
      field[POS_BLOCKS][pos] = BLOCK;
      field[POS_BLOCKS][pos + 1] = BLOCK;
      field[POS_BLOCKS][pos + 2] = BLOCK;
      field[POS_BLOCKS][pos + 3] = BLOCK;
      field[POS_BLOCKS][pos + 4] = BLOCK;
      field[POS_BLOCKS - 1][pos] = BLOCK;
      field[POS_BLOCKS - 1][pos + 1] = BLOCK;
      field[POS_BLOCKS - 1][pos + 2] = BLOCK;
      field[POS_BLOCKS - 1][pos + 3] = BLOCK;
      field[POS_BLOCKS - 1][pos + 4] = BLOCK;
      field[POS_BLOCKS - 2][pos + 1] = BLOCK;
      field[POS_BLOCKS - 2][pos + 2] = BLOCK;
      field[POS_BLOCKS - 2][pos + 3] = BLOCK;
   };
   for(int i { 2 }; i < COUT_ROWS - 7; i += 7) {
      addBlock(i);
   }
   addBlock(2);
}
//---------------------------------------------------------------------------
int main()
{
   for(int i = 0; i < COUT_ROWS; i++)
   {
      for(int j = 0; j < COUT_COLUMS; j++)
      {
         field[i][j] = FREE;
         fieldShips[i][j] = 0;
      }
   }
   termios term;
   tcgetattr(STDIN, &term);
   term.c_lflag &= ~ICANON;
   tcsetattr(STDIN, TCSANOW, &term);
   setbuf(stdin, NULL);
   setPositionTurel();
   setBlocks();
   generateRows();
   start();
   return 0;
}
