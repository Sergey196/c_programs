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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "logic.h"
#include "maingui.h"
#include "pipconnectplayers.h"

class Controller
{
public:
    Controller();
    
    void start(int idRunProgramm, int idAnotherPlaer);
    _baseitem::cellState getCellStatus(int typePlayer, int x, int y);
    void cellAtacker(int x, int y);
    int getCoutCellsFreeShip();
    void addNewShip(int x, int y, int coutCells, bool verticalOrHorizontal);
    void reloadToDefault();
    void messageRequest(std::string request, _baseitem::messageType type);
    void messageResponse(std::string response, _baseitem::messageType type);
    void repaint();
    void reloadToDefaultGui();
    
private: 
   std::unique_ptr<Logic> logic;
   std::unique_ptr<MainGui> gui;
   std::unique_ptr<PipConnectPlayers> messager;
};

#endif // CONTROLLER_H
