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
#include <vector>

class TController;

class TLogic
{
public: 
   TLogic(TController *pointOnControler); 
   void startGame();
   int getCellValue(int x, int y) { return list_cells[x][y]; }
   void keyPress(int key);
private:
   void addRandomCells();
   bool checkFreeCells();
   TController *pointOnControler;
   int list_cells[COUT_ROWS_COLUMS][COUT_ROWS_COLUMS];
   std::vector<Cell> current_cells;
   
};

#endif // TLOGIC_H
