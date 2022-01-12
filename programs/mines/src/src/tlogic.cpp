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
   for(int i = 0; i < COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         fields[i][j] = NONE; 
      }
   }

   std::vector<int> mines;
   for(int i = 0; i < 99; i++)
   {
      mines.push_back(i);
   }
   std::random_device rd;
   std::mt19937 g(rd());
   std::shuffle(mines.begin(), mines.end(), g);
   
   for(int i = 0; i < 20; i++)
   {
      int x;
      int y;
      std::string num_str = std::to_string(mines.at(i));
      if(num_str.length() == 1)
      {
         x = num_str.at(0);
         y = 0;
      } else {
         x = num_str.at(0) - '0'; 
         y = num_str.at(1) - '0'; 
      }
      fields[x][y] = MINE_NONE; 
      freeField--;
   }
}
//---------------------------------------------------------------------------
CellState TLogic::getCellValue(int x, int y)
{
   CellState state { fields[x][y], getCoutMinesAroundField(x, y) };
   return state; 
}
//---------------------------------------------------------------------------
void TLogic::selectCell(int x, int y)
{
   if(fields[x][y] == MINE_NONE)
   {
      for(int i = 0; i < COUT_ROWS_COLUMS; i++)
      {
         for(int j = 0; j < COUT_ROWS_COLUMS; j++)
         {
            if(fields[i][j] == MINE_NONE)
            {
               fields[i][j] = MINE_BOM;  
            }
         }
      }
      pointOnControler->gameStatus(false); 
   } else if(fields[x][y] == NONE) { 
      searchOtherFreeFields(x, y);
      if(fields[x][y] != FREE)
      {
         freeField--; 
         fields[x][y] = FREE;  
      }
      if(freeField == 0)
      {
         pointOnControler->gameStatus(true); 
      }
   }
}
//---------------------------------------------------------------------------
void TLogic::searchOtherFreeFields(int x, int y)
{
   if(x < 0 || x > 9 || y < 0 || y > 9)
   {
      return; 
   }
   if(fields[x][y] != NONE)
   {
      return; 
   }
   fields[x][y] = FREE; 
   freeField--;
   if(getCoutMinesAroundField(x, y) == 0)
   {
      searchOtherFreeFields(x - 1, y);
      searchOtherFreeFields(x + 1, y);
      searchOtherFreeFields(x, y - 1);
      searchOtherFreeFields(x, y + 1);
      searchOtherFreeFields(x - 1, y - 1);
      searchOtherFreeFields(x + 1, y + 1);
      searchOtherFreeFields(x - 1, y + 1);
      searchOtherFreeFields(x + 1, y - 1);
   } 
}
//---------------------------------------------------------------------------
int TLogic::getCoutMinesAroundField(int x, int y)
{
   int result { 0 }; 
   if((x != 0) && ((fields[x - 1][y] == MINE_NONE) || (fields[x - 1][y] == MINE_BOM)))
   {
      result++;
   }
   if((x != 9) && ((fields[x + 1][y] == MINE_NONE) || (fields[x + 1][y] == MINE_BOM)))
   {
      result++;
   }
   if((y != 0) && ((fields[x][y - 1] == MINE_NONE) || (fields[x][y - 1] == MINE_BOM)))
   {
      result++;
   }
   if((y != 9) && ((fields[x][y + 1] == MINE_NONE) || (fields[x][y + 1] == MINE_BOM)))
   {
      result++;
   }
   if((x != 9) && (y != 9) && ((fields[x + 1][y + 1] == MINE_NONE) || (fields[x + 1][y + 1] == MINE_BOM)))
   {
      result++;
   }
   if((x != 0) && (y != 0) && ((fields[x - 1][y - 1] == MINE_NONE) || (fields[x - 1][y - 1] == MINE_BOM)))
   {
      result++;
   }
   if((x != 9) && (y != 0) && ((fields[x + 1][y - 1] == MINE_NONE) || (fields[x + 1][y - 1] == MINE_BOM)))
   {
      result++;
   }
   if((x != 0) && (y != 9) && ((fields[x - 1][y + 1] == MINE_NONE) || (fields[x - 1][y + 1] == MINE_BOM)))
   {
      result++;
   }
   return result;
}
