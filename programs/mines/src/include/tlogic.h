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

#ifndef TLOGIC_H
#define TLOGIC_H

#include "tbaseitem.h"

class TController;

class TLogic
{
public: 
   TLogic(TController *pointOnControler); 
   CellState getCellValue(int x, int y);
   void selectCell(int x, int y);
   void startGame();
private:
   void searchOtherFreeFields(int x, int y);
   int getCoutMinesAroundField(int x, int y);
   CellState fields[FIELD_SIZE][FIELD_SIZE];
   int freeField { 100 };
   TController *pointOnControler;
};

#endif // TLOGIC_H
