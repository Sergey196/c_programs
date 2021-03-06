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

#include "controller.h"
#include <iostream>

Controller::Controller()
{ 
   logic = std::make_unique<Logic>(this);
   gui = std::make_unique<MainGui>(this);
   messager = std::make_unique<PipConnectPlayers>(this);
}

//---------------------------------------------------------------------------
void Controller::start(int idRunProgramm, int idAnotherPlaer)
{
   messager->start(idRunProgramm, idAnotherPlaer);
   gui->start();
}
//---------------------------------------------------------------------------
_baseitem::cellState Controller::getCellStatus(int typePlayer, int x, int y)
{
   logic->getCellStatus(typePlayer, x, y);
}
//---------------------------------------------------------------------------
void Controller::cellAtacker(int x, int y)
{
   logic->cellAtacker(x, y);
}
//---------------------------------------------------------------------------
int Controller::getCoutCellsFreeShip()
{
   return logic->getCoutCellsFreeShip();
}
//---------------------------------------------------------------------------
void Controller::addNewShip(int x, int y, int coutCells, bool verticalOrHorizontal)
{
   logic->addNewShip(x, y, coutCells, verticalOrHorizontal);
}
//---------------------------------------------------------------------------
void Controller::reloadToDefault()
{
   logic->reloadToDefault();
}
//---------------------------------------------------------------------------
void Controller::messageRequest(std::string request, _baseitem::messageType type)
{
   messager->sendMessage(request, type);
}
//---------------------------------------------------------------------------
void Controller::messageResponse(std::string response, _baseitem::messageType type)
{
   logic->messageResponse(response, type);
}
//---------------------------------------------------------------------------
void Controller::repaint()
{
   gui->repaint();
}
//---------------------------------------------------------------------------
void Controller::reloadToDefaultGui()
{
   gui->reloadToDefaultGui();
}
