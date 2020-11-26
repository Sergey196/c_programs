/*
 * Copyright 2020 utkinsv <email>
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

#include "logic.h"
#include <iostream>

Logic::Logic(Controller *_controller)
{
   controller = _controller; 
   for(int k = 0; k < _baseitem::COUT_PLAYERS; k++)
   {
      for(int i = 0; i < _baseitem::COUT_ROWS_COLUMS; i++)
      {
         for(int j = 0; j < _baseitem::COUT_ROWS_COLUMS; j++)
         {
            cells[k][i][j] = std::make_unique<Cell>();
         }
      }
      
      ships[k][0] = std::make_unique<Ship>(4);
      ships[k][1] = std::make_unique<Ship>(3);
      ships[k][2] = std::make_unique<Ship>(3);
      ships[k][3] = std::make_unique<Ship>(2);
      ships[k][4] = std::make_unique<Ship>(2);
      ships[k][5] = std::make_unique<Ship>(2);
      ships[k][6] = std::make_unique<Ship>(1);
      ships[k][7] = std::make_unique<Ship>(1);
      ships[k][8] = std::make_unique<Ship>(1);
      ships[k][9] = std::make_unique<Ship>(1);
   }
}
//---------------------------------------------------------------------------
_baseitem::cellState Logic::getCellStatus(int x, int y)
{
   if(cells[_baseitem::PLAYER_INDEX][x][y]->isShip())
   {
       if(cells[_baseitem::PLAYER_INDEX][x][y]->isBroken())
       {
          return _baseitem::ship_beat;
       }
       else
       {
          return _baseitem::ship_normal;
       }
   }
   else
   {
       if(cells[_baseitem::PLAYER_INDEX][x][y]->isBroken())
       {
          return _baseitem::free_beat;
       }
       else
       {
          return _baseitem::free_normal;
       }
   }
}
//---------------------------------------------------------------------------
void Logic::cellAtacker(int x, int y)
{
   if(x > 9 || y > 9)
   {
      return;
   }
   cells[_baseitem::PLAYER_INDEX][x][y]->cellAtacker();
}
//---------------------------------------------------------------------------
int Logic::getCoutCellsFreeShip()
{
   for(int i = 0; i < _baseitem::COUT_SHIPS; i++)
   {
      if(!ships[_baseitem::PLAYER_INDEX][i]->isActive())
      {
         idCurrentChangeResShip = i;
         return ships[_baseitem::PLAYER_INDEX][i]->getCoutCell(); 
      }
   }
   return -1;
}
//---------------------------------------------------------------------------
void Logic::addNewShip(int x, int y, int coutCells, bool verticalOrHorizontal)
{
   if(!changeShipCoordinatesCorrect(x, y, coutCells, verticalOrHorizontal))
   {
      return;
   }
   for(int i = 0; i < coutCells; i++)
   {
      cells[_baseitem::PLAYER_INDEX][x][y]->setShip(0);
      if(verticalOrHorizontal)
      {
         x++;
      }
      else
      {
         y++;
      }
   }

   ships[_baseitem::PLAYER_INDEX][idCurrentChangeResShip]->setActive();
   idCurrentChangeResShip = -1;
}
//---------------------------------------------------------------------------
bool Logic::changeShipCoordinatesCorrect(int x, int y, int coutCells, bool verticalOrHorizontal)
{
   if((x < 0 || x > 9 || y < 0 || y > 9))
   {
      return false;
   }

   bool result = true;

   for(int i = 0; i < coutCells; i++)
   {
      if(i == 0)
      {
          if(verticalOrHorizontal)
          {
             result = changeHorisontalStartSection(x, y);
          }
          else
          {
             result = changeVerticalStartSection(x, y);
          }
      }

      if(i == coutCells - 1)
      {
          if(verticalOrHorizontal)
          {
             result = changeHorisontalEndSection(x, y);
          }
          else
          {
             result = changeVerticalEndSection(x, y);
          }
      }

      if((i > 0) && (i < coutCells - 1))
      {
          if(verticalOrHorizontal)
          {
             result = changeHorisontalSection(x, y);
          }
          else
          {
             result = changeVerticalSection(x, y);
          }
      }

      if(!result)
      {
         return false;
      }

      if(verticalOrHorizontal)
      {
         x++;
      }
      else
      {
         y++;
      }
   }

   return true;
}
//---------------------------------------------------------------------------
bool Logic::changeVerticalStartSection(int x, int y)
{
   return isFieldFree(x, y) && isFieldFree(x + 1, y) && isFieldFree(x - 1, y) && isFieldFree(x, y - 1) && isFieldFree(x + 1, y - 1) && isFieldFree(x - 1, y - 1);
}
//---------------------------------------------------------------------------
bool Logic::changeHorisontalStartSection(int x, int y)
{
   return isFieldFree(x, y) && isFieldFree(x , y + 1) && isFieldFree(x, y - 1) && isFieldFree(x - 1, y) && isFieldFree(x - 1, y - 1) && isFieldFree(x - 1, y + 1);
}
//---------------------------------------------------------------------------
bool Logic::changeVerticalSection(int x, int y)
{
   return isFieldFree(x, y) && isFieldFree(x + 1, y) && isFieldFree(x - 1, y);
}
//---------------------------------------------------------------------------
bool Logic::changeHorisontalSection(int x, int y)
{
   return isFieldFree(x, y) && isFieldFree(x, y - 1) && isFieldFree(x, y + 1);
}
//---------------------------------------------------------------------------
bool Logic::changeVerticalEndSection(int x, int y)
{
   return isFieldFree(x, y) && isFieldFree(x + 1, y) && isFieldFree(x - 1, y) && isFieldFree(x, y + 1) && isFieldFree(x - 1, y + 1) && isFieldFree(x + 1, y + 1);
}
//---------------------------------------------------------------------------
bool Logic::changeHorisontalEndSection(int x, int y)
{
   return isFieldFree(x, y) && isFieldFree(x, y + 1) && isFieldFree(x, y - 1) && isFieldFree(x + 1, y) && isFieldFree(x + 1, y + 1) && isFieldFree(x + 1, y - 1);
}
//---------------------------------------------------------------------------
bool Logic::isFieldFree(int x, int y)
{
    if(x < 0 || x > 9 || y < 0 || y > 9)
    {
       return true;
    }

    return !cells[_baseitem::PLAYER_INDEX][x][y]->isShip();
}
//---------------------------------------------------------------------------
void Logic::reloadToDefault()
{
    for(int i = 0; i < _baseitem::COUT_SHIPS; i++)
    {
       ships[_baseitem::PLAYER_INDEX][i]->refreshState();
    }
    for(int i = 0; i < _baseitem::COUT_ROWS_COLUMS; i++)
    {
       for(int j = 0; j < _baseitem::COUT_ROWS_COLUMS; j++)
       {
          cells[_baseitem::PLAYER_INDEX][i][j]->refreshState();
       }
    }

   idCurrentChangeResShip = -1;
}
