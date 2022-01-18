/*
 * Copyright 2021 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tlogic.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <random>
#include "tcontroller.h"

TLogic::TLogic(TController *_pointOnControler)
{
   pointOnControler = _pointOnControler;
   connect(&timerStep, &QTimer::timeout, this, &TLogic::step);
   
   /*int counter { 0 };
   for(int i = 0; i < COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         counter++; 
         randomCellsCoordinateContener[counter] = {i, j};
      }
   }*/
}
//---------------------------------------------------------------------------
void TLogic::startGame()
{
   interval = 1000; 
   timerStep.setInterval(interval);
   timerStep.stop(); 
   for(int i = 0; i < COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         field[i][j] = FREE; 
      }
   }
   
   field[0][0] = SNAKE;
   direction = RIGHT;
   snakeCells = { };
   /*while(snakeCells.size() > 0)
   {
      snakeCells.pop(); 
   }*/
   snakeCells.push(CellCoordinats { 0, 0 });
   foodRandom(4);
   coutFood = 4;
   pointOnControler->repaint(); 
   timerStep.start();
}
//---------------------------------------------------------------------------
void TLogic::step()
{
   CellCoordinats start = snakeCells.back();
   CellCoordinats end = snakeCells.front();
   
   int newx { 0 };
   int newy { 0 };
   
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
   
   if(((newx < 0) || (newx > COUT_ROWS_COLUMS - 1) || (newy < 0) || (newy > COUT_ROWS_COLUMS - 1)) || field[newx][newy] == SNAKE)
   {
      pointOnControler->setGameState(false); 
      timerStep.stop();
      return;
   }
       
   if(field[newx][newy] != FOOD) {
      field[end.x][end.y] = FREE; 
      snakeCells.pop(); 
   } else  {
     coutFood--;
     if(coutFood < 3)
     {
        foodRandom(2);   
        coutFood += 2; 
        if(interval > 200)
        {
           interval = interval * 0.8; 
        }
        timerStep.setInterval(interval);
     }
   }
   
   snakeCells.push(CellCoordinats { newx, newy });
   field[newx][newy] = SNAKE;
   
   pointOnControler->repaint(); 
}
//---------------------------------------------------------------------------
void TLogic::foodRandom(int coutFields)
{
   /*std::random_device rd;
   std::mt19937 g(rd());
   std::shuffle(&randomCellsCoordinateContener[0], &randomCellsCoordinateContener[99], g);
   int cellFood = coutFields;
   int counter { 0 };
   while(cellFood > 0)
   {
      CellCoordinats cell = randomCellsCoordinateContener[counter]; 
      if(field[cell.x][cell.y] == FREE)
      {
         cellFood--; 
         field[cell.x][cell.y] = FOOD;
      }
      counter++;
   }*/
   int cellFood = coutFields;
   while(cellFood > 0)
   {
      int x = rand() % 9;
      int y = rand() % 9; 
      if(field[x][y] == FREE)
      {
         cellFood--; 
         field[x][y] = FOOD;
      }
   }
   
}
//---------------------------------------------------------------------------
void TLogic::setDirection(Direction _direction) 
{ 
    if((direction == UP && _direction != DOWN) || (direction == DOWN && _direction != UP) || (direction == RIGHT && _direction != LEFT) || (direction == LEFT && _direction != RIGHT) || (snakeCells.size() == 1))
    {
       direction = _direction;  
    }
    
}
