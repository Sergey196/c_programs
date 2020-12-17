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

#ifndef LOGIC_H
#define LOGIC_H

#include <memory>
#include <vector>
#include "constants.h"
#include "cell.h"
#include "ship.h"

class Controller;

class Logic
{
public:
    Logic(Controller *_controller);

    _baseitem::cellState getCellStatus(int typePlayer, int x, int y);
    void cellAtacker(int x, int y);
    int getCoutCellsFreeShip();
    void addNewShip(int x, int y, int coutCells, bool verticalOrHorizontal);
    void reloadToDefault();
    void messageResponse(std::string response, _baseitem::messageType type);
private:
   bool changeShipCoordinatesCorrect(int x, int y, int coutCells, bool verticalOrHorizontal);
   bool changeVerticalStartSection(int x, int y);
   bool changeHorisontalStartSection(int x, int y);
   bool changeVerticalSection(int x, int y);
   bool changeHorisontalSection(int x, int y);
   bool changeVerticalEndSection(int x, int y);
   bool changeHorisontalEndSection(int x, int y);
   bool isFieldFree(int x, int y);
   std::vector<std::string> split(std::string str, std::string delimiter);
   void attackerCellRequest(int x, int y);
   void attackerCellResponse(int x, int y);
   bool isShipDestroy(int indexPlayer, int idShip);
   void setCellAroundDestroyShipBeat(int indexPlayer, int idShip);
   void addEnemyPlayerShip(int x, int y, int idShip);
   bool checkDestroyAllShips();
   void reloadLogic();


   std::unique_ptr<Cell> cells[_baseitem::COUT_PLAYERS][_baseitem::COUT_ROWS_COLUMS][_baseitem::COUT_ROWS_COLUMS];
   std::unique_ptr<Ship> ships[_baseitem::COUT_PLAYERS][_baseitem::COUT_SHIPS];
   Controller *controller;

   int idCurrentChangeResShip { -1 };
   bool isAllShipsArePlaced { false };
   bool isAllEnemyShipsArePlaced { false };
   bool myMove { true };
   bool winFlag { false };
};

#endif // LOGIC_H
