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
#include "controller.h"
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
   }

   for(int k = 0; k < _baseitem::COUT_PLAYERS; k++)
   {
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
_baseitem::cellState Logic::getCellStatus(int typePlayer, int x, int y)
{
   if(cells[typePlayer][x][y]->isShip())
   {
       if(cells[typePlayer][x][y]->isBroken())
       {
          return _baseitem::ship_beat;
       }
       else
       {
          if(typePlayer == _baseitem::PLAYER_INDEX)
          {
             return _baseitem::ship_normal;
          }
          else
          {
             return _baseitem::enemy_ship_normal;
          }
       }
   }
   else
   {
       if(cells[typePlayer][x][y]->isBroken())
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
   if(!isAllShipsArePlaced || !isAllEnemyShipsArePlaced || !myMove || winFlag)
   {
      return;
   }

   if(x > 9 || y > 9 || x < 0 || y < 0)
   {
      return;
   }

   myMove = false;
   controller->messageRequest(std::to_string(x) + "_" + std::to_string(y), _baseitem::attackCellRequest);
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
   isAllShipsArePlaced = true;
   controller->messageRequest("", _baseitem::allEnemyShipsPlaced);
   return -1;
}
//---------------------------------------------------------------------------
void Logic::addNewShip(int x, int y, int coutCells, bool verticalOrHorizontal)
{
   if(!changeShipCoordinatesCorrect(x, y, coutCells, verticalOrHorizontal))
   {
      return;
   }
   
   ships[_baseitem::PLAYER_INDEX][idCurrentChangeResShip]->setActive();
   
   for(int i = 0; i < coutCells; i++)
   {
      cells[_baseitem::PLAYER_INDEX][x][y]->setShip(idCurrentChangeResShip);
      controller->messageRequest(std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(idCurrentChangeResShip), _baseitem::addShip);
      if(verticalOrHorizontal)
      {
         x++;
      }
      else
      {
         y++;
      }
   }
   
   idCurrentChangeResShip = -1;
}
//---------------------------------------------------------------------------
void Logic::addEnemyPlayerShip(int x, int y, int idShip)
{
   std::cout << "TEST addEnemyPlayerShip = " << idShip << std::endl;
   cells[_baseitem::ENEMY_INDEX][x][y]->setShip(idShip);
   controller->repaint();
}
//---------------------------------------------------------------------------
bool Logic::changeShipCoordinatesCorrect(int x, int y, int coutCells, bool verticalOrHorizontal)
{
   if(x < 0 || x > 9 || y < 0 || y > 9)
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
          if(!result)
          {
             return false;
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
          if(!result)
          {
             return false;
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
          if(!result)
          {
             return false;
          }
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
    reloadLogic();
    controller->messageRequest("", _baseitem::reloadShips);
}
//---------------------------------------------------------------------------
void Logic::reloadLogic()
{
    for(int i = 0; i < _baseitem::COUT_SHIPS; i++)
    {
       ships[_baseitem::PLAYER_INDEX][i]->refreshState();
       ships[_baseitem::ENEMY_INDEX][i]->refreshState();
    }
    for(int i = 0; i < _baseitem::COUT_ROWS_COLUMS; i++)
    {
       for(int j = 0; j < _baseitem::COUT_ROWS_COLUMS; j++)
       {
          cells[_baseitem::PLAYER_INDEX][i][j]->refreshState();
          cells[_baseitem::ENEMY_INDEX][i][j]->refreshState();
       }
    }

    isAllShipsArePlaced = false;
    idCurrentChangeResShip = -1;
    isAllEnemyShipsArePlaced = false;
    myMove = true;
    winFlag = false;

    controller->reloadToDefaultGui();
    controller->repaint();
}
//---------------------------------------------------------------------------
std::vector<std::string> Logic::split(std::string str, std::string delimiter)
{
   std::vector<std::string> list;
   size_t pos = 0;
   std::string token;
   while ((pos = str.find(delimiter)) != std::string::npos) {
       token = str.substr(0, pos);
       list.push_back(token);
       str.erase(0, pos + delimiter.length());
   }
   list.push_back(str);
   return list;
}
//---------------------------------------------------------------------------
void Logic::messageResponse(std::string response, _baseitem::messageType type)
{
   auto messageBody = split(response, "_");

   switch (type)
   {
      case _baseitem::addShip:
         addEnemyPlayerShip(std::stoi(messageBody.at(0)), std::stoi(messageBody.at(1)), std::stoi(messageBody.at(2)));
         break;
      case _baseitem::allEnemyShipsPlaced:
         isAllEnemyShipsArePlaced = true;
         break;
      case _baseitem::attackCellRequest:
         attackerCellRequest(std::stoi(messageBody.at(0)), std::stoi(messageBody.at(1)));
         break;
      case _baseitem::attackCellResponse:
         attackerCellResponse(std::stoi(messageBody.at(0)), std::stoi(messageBody.at(1)));
         break;
      case _baseitem::reloadShips:
         reloadLogic();
         break;
      case _baseitem::playerWin:
         winFlag = true;
         break;
      default:
         ;
   }
}
//---------------------------------------------------------------------------
void Logic::attackerCellRequest(int x, int y)
{
   cells[_baseitem::PLAYER_INDEX][x][y]->cellAtacker();

   if(cells[_baseitem::PLAYER_INDEX][x][y]->isShip())
   {
      myMove = false;
   }
   else
   {
      myMove = true;
   }

   if(isShipDestroy(_baseitem::PLAYER_INDEX, cells[_baseitem::PLAYER_INDEX][x][y]->getIdShip()))
   {
      ships[_baseitem::PLAYER_INDEX][cells[_baseitem::PLAYER_INDEX][x][y]->getIdShip()]->setDestroyFlag();
      setCellAroundDestroyShipBeat(_baseitem::PLAYER_INDEX, cells[_baseitem::PLAYER_INDEX][x][y]->getIdShip());

      if(checkDestroyAllShips())
      {
         controller->messageRequest("", _baseitem::playerWin);
         winFlag = true;
      }
   }

   controller->messageRequest(std::to_string(x) + "_" + std::to_string(y), _baseitem::attackCellResponse);
}
//---------------------------------------------------------------------------
bool Logic::checkDestroyAllShips()
{
    for(int i = 0; i < _baseitem::COUT_SHIPS; i++)
    {
       if(!ships[_baseitem::PLAYER_INDEX][i]->isDestroy())
       {
          return false;
       }
    }
    return true;
}
//---------------------------------------------------------------------------
bool Logic::isShipDestroy(int indexPlayer, int idShip)
{
   if(idShip == -1)
   {
      return false;
   }

   for(int i = 0; i < _baseitem::COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < _baseitem::COUT_ROWS_COLUMS; j++)
      {
         if((cells[indexPlayer][i][j]->getIdShip() == idShip) && !cells[indexPlayer][i][j]->isBroken())
         {
            return false;
         }
      }
   }

   return true;
}
//---------------------------------------------------------------------------
void Logic::attackerCellResponse(int x, int y)
{
   cells[_baseitem::ENEMY_INDEX][x][y]->cellAtacker();

   if(isShipDestroy(_baseitem::ENEMY_INDEX, cells[_baseitem::ENEMY_INDEX][x][y]->getIdShip()))
   {
      setCellAroundDestroyShipBeat(_baseitem::ENEMY_INDEX, cells[_baseitem::ENEMY_INDEX][x][y]->getIdShip());
      ships[_baseitem::ENEMY_INDEX][cells[_baseitem::PLAYER_INDEX][x][y]->getIdShip()]->setDestroyFlag();
   }

   if(cells[_baseitem::ENEMY_INDEX][x][y]->isShip())
   {
      myMove = true;
   }

   controller->repaint();
}
//---------------------------------------------------------------------------
void Logic::setCellAroundDestroyShipBeat(int indexPlayer, int idShip)
{
    auto setDestroyCell = [&](int x, int y) {
        if(x < 0 || x > 9 || y < 0 || y > 9)
        {
           return;
        }
        cells[indexPlayer][x][y]->cellAtacker();
    };

    auto checkAndSetDestroyField = [&](int x, int y) {
        if(cells[indexPlayer][x][y]->getIdShip() == idShip)
        {
           setDestroyCell(x + 1, y);
           setDestroyCell(x - 1, y);
           setDestroyCell(x, y + 1);
           setDestroyCell(x, y - 1);
           setDestroyCell(x + 1, y - 1);
           setDestroyCell(x - 1, y + 1);
           setDestroyCell(x + 1, y + 1);
           setDestroyCell(x - 1, y - 1);
        }
    };

    for(int i = 0; i < _baseitem::COUT_ROWS_COLUMS; i++)
    {
       for(int j = 0; j < _baseitem::COUT_ROWS_COLUMS; j++)
       {
          checkAndSetDestroyField(i, j);
       }
    }
}
