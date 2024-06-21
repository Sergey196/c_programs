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
#include <vector>
#include <random>
#include <algorithm>
#include <string.h>
#include "tcontroller.h"

TLogic::TLogic(TController *_pointOnControler)
{
   pointOnControler = _pointOnControler;
}
//---------------------------------------------------------------------------
void TLogic::startGame()
{
   freeField = 100;
   for(int i = 0; i < COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         fields[i][j] =  CellState { FREE, 0, false }; 
      }
   }

   for(int i = 0; i < COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         if((rand() % 5) == MINE) {
            fields[i][j].value = MINE;
            freeField--;
         }
      }
   }
   
   for(int i = 0; i < COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         fields[i][j].coutMines = getCoutMinesAroundField(i, j);
      }
   }
}
//---------------------------------------------------------------------------
CellState TLogic::getCellValue(int x, int y)
{
   return fields[x][y]; 
}
//---------------------------------------------------------------------------
void TLogic::selectCell(int x, int y)
{
   
   if(fields[x][y].value == MINE) {
      fields[x][y].value = MINE_BOM;
      pointOnControler->stopGame(); 
      return;
   } else if(fields[x][y].value == FREE) {
      for(int i = 0; i < COUT_ROWS_COLUMS; i++)
      {
         for(int j = 0; j < COUT_ROWS_COLUMS; j++)
         {
            fields[i][j].isCheck = false;
         }
      }
      searchOtherFreeFields(x, y);
   }
   
   if(freeField == 0) {
      pointOnControler->stopGame(); 
   }
}
//---------------------------------------------------------------------------
void TLogic::searchOtherFreeFields(int x, int y)
{
   if(x < 0 || x > COUT_ROWS_COLUMS - 1 || y < 0 || y > COUT_ROWS_COLUMS - 1)
   {
      return; 
   }
   
   if(fields[x][y].isCheck) {
      return;
   }
   
   fields[x][y].isCheck = true;
   fields[x][y].value = SELECT;
   freeField--;
   
   if(fields[x][y].coutMines == 0) {
      searchOtherFreeFields(x + 1, y);
      searchOtherFreeFields(x - 1, y);
      searchOtherFreeFields(x, y + 1);
      searchOtherFreeFields(x, y - 1);
      searchOtherFreeFields(x + 1, y + 1);
      searchOtherFreeFields(x - 1, y - 1);
      searchOtherFreeFields(x - 1, y + 1);
      searchOtherFreeFields(x + 1, y - 1);
   }
}
//---------------------------------------------------------------------------
int TLogic::getCoutMinesAroundField(int x, int y)
{
   int result { 0 }; 
   if((x > 0) && (fields[x - 1][y].value == MINE))
   {
      result++;
   }
   if((x < COUT_ROWS_COLUMS - 1) && (fields[x + 1][y].value == MINE))
   {
      result++;
   }
   if((y > 0) && (fields[x][y - 1].value == MINE))
   {
      result++;
   }
   if((y < COUT_ROWS_COLUMS - 1) && (fields[x][y + 1].value == MINE))
   {
      result++;
   }
   if((x < COUT_ROWS_COLUMS - 1) && (y < COUT_ROWS_COLUMS - 1) && (fields[x + 1][y + 1].value == MINE))
   {
      result++;
   }
   if((x > 0) && (y > 0) && (fields[x - 1][y - 1].value == MINE))
   {
      result++;
   }
   if((x != COUT_ROWS_COLUMS - 1) && (y > 0) && (fields[x + 1][y - 1].value == MINE))
   {
      result++;
   }
   if((x > 0) && (y != COUT_ROWS_COLUMS - 1) && (fields[x - 1][y + 1].value == MINE))
   {
      result++;
   }
   return result;
}
