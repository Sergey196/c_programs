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

#include "tcontroller.h"

TController::~TController()
{
   delete gui; 
   delete logic;
}
//---------------------------------------------------------------------------
void TController::start()
{
   gui = new TGui(this); 
   logic = new TLogic(this);
   gui->show(); 
}
//---------------------------------------------------------------------------
CellState TController::getCellValue(int x, int y)
{
   return logic->getCellValue(x, y); 
}
//---------------------------------------------------------------------------
void TController::selectCell(int x, int y)
{
   logic->selectCell(x, y);
}
//---------------------------------------------------------------------------
void TController::gameStatus(bool status)
{
   gui->gameStatus(status); 
}
