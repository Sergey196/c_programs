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
#include <unistd.h>
#include <vector>
#include <random>
#include <algorithm>
#include "tcontroller.h"

TLogic::TLogic(TController *_pointOnControler)
{
   pointOnControler = _pointOnControler;
   for(int i = 0; i < COUT_ROWS_COLUMS; i++) 
   { 
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         list_cells[i][j] = 0;
      }
   }
}
//---------------------------------------------------------------------------
void TLogic::startGame()
{
   pointOnControler->setGameState(true);
   for(int i = 0; i < COUT_ROWS_COLUMS; i++) 
   { 
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         list_cells[i][j] = 0;
      }
   }
   addRandomCells();
}
//---------------------------------------------------------------------------
void TLogic::addRandomCells()
{
   current_cells.clear();
   int countCells = rand() % 2 + 1;
   
   std::cout << "TEST = " << countCells << std::endl;
   
   for(int i = 0; i < COUT_ROWS_COLUMS; i++) 
   { 
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         if(list_cells[i][j]) {
            continue;
         }
         Cell cell;
         cell.x = i;
         cell.y = j;
         current_cells.push_back(cell);
      }
   }
   
   /*if(!current_cells.size()) {
      pointOnControler->setGameState(false);
      return;
   } */
   
   if(countCells > current_cells.size()) {
      countCells = current_cells.size();
   } 
   
   for(int i = 0; i < countCells; i++) 
   {                      
      int position = rand() % current_cells.size();
      
      list_cells[current_cells[position].x][current_cells[position].y] = 2;
   }
}
//---------------------------------------------------------------------------
void TLogic::keyPress(int key)
{
   bool addNewCellFlag { false };
   auto toLeft = [this, &addNewCellFlag]() {
      std::cout << "TEST toLeft" << std::endl;
      
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         current_cells.clear();
         for(int i = 0; i < COUT_ROWS_COLUMS; i++)
         {
            if(!list_cells[i][j]) {
               addNewCellFlag = true;
               continue;
            }
            Cell cell;
            //cell.x = i;
            //cell.y = j;
            cell.value = list_cells[i][j];
            current_cells.push_back(cell);
            list_cells[i][j] = 0;
         }
         
         if(!current_cells.size()) {
            continue;
         }
         
         auto it_pre = current_cells.begin();
         std::vector<Cell>::iterator it_current = it_pre + 1;

         while(it_current != current_cells.end()) { 
           if(it_pre->value == it_current->value) {
              it_current = current_cells.erase(it_current);
              it_pre->value = it_pre->value * 2;
              addNewCellFlag = true;
              if(it_current != current_cells.end()) {
                it_current++;
                it_pre++;
              }
           } else {
              it_current++;
              it_pre++;
           }
         }
         
         int index { 0 };
         for(auto cell : current_cells)
         {
            list_cells[index][j] = cell.value;
            index++;
         }
      }
   };
   auto toRight = [this, &addNewCellFlag]() {
      std::cout << "TEST toRight" << std::endl;
      for(int j = COUT_ROWS_COLUMS - 1; j >= 0; j--)
      {
         current_cells.clear();
         for(int i = COUT_ROWS_COLUMS - 1; i >= 0; i--)
         {
            if(!list_cells[i][j]) {
               addNewCellFlag = true;
               continue;
            }
            Cell cell;
            //cell.x = i;
            //cell.y = j;
            cell.value = list_cells[i][j];
            current_cells.push_back(cell);
            list_cells[i][j] = 0;
         }
         
         if(!current_cells.size()) {
            continue;
         }
         
         auto it_pre = current_cells.begin();
         std::vector<Cell>::iterator it_current = it_pre + 1;
         
         while(it_current != current_cells.end()) {
           if(it_pre->value == it_current->value) {
              it_current = current_cells.erase(it_current);
              it_pre->value = it_pre->value * 2;
              addNewCellFlag = true;
              if(it_current != current_cells.end()) {
                it_current++;
                it_pre++;
              }
           } else {
              it_current++;
              it_pre++;
           }
         }
         
         int index { COUT_ROWS_COLUMS - 1 };
         for(auto cell : current_cells)
         {
            list_cells[index][j] = cell.value;
            index--;
         }
      }
   };
   auto toTop = [this, &addNewCellFlag]() {
      std::cout << "TEST toTop" << std::endl;
      for(int i = 0; i < COUT_ROWS_COLUMS; i++)
      {
         current_cells.clear();
         for(int j = 0; j < COUT_ROWS_COLUMS; j++)
         {
            if(!list_cells[i][j]) {
               addNewCellFlag = true;
               continue;
            }
            Cell cell;
            //cell.x = i;
            //cell.y = j;
            cell.value = list_cells[i][j];
            current_cells.push_back(cell);
            list_cells[i][j] = 0;
         }
         
         if(!current_cells.size()) {
            continue;
         }
         
         std::cout << "TEST size = " << current_cells.size() << std::endl;
         
         auto it_pre = current_cells.begin();
         std::vector<Cell>::iterator it_current = it_pre + 1;
         
         //std::cout << "TEST1 = " << &(*current_cells.begin()) << std::endl;
         //std::cout << "TEST2 = " << &(*current_cells.end()) << std::endl;
         
         while(it_current != current_cells.end()) {
           if(it_pre->value == it_current->value) {
              it_current = current_cells.erase(it_current);
              it_pre->value = it_pre->value * 2;
              addNewCellFlag = true;
              if(it_current != current_cells.end()) {
                it_current++;
                it_pre++;
              }
           } else {
              it_current++;
              it_pre++;
           }
         }
         
         int index { 0 };
         for(auto cell : current_cells)
         {
            list_cells[i][index] = cell.value;
            index++;
         }
      }
   };
   auto toDown = [this, &addNewCellFlag]() {
      std::cout << "TEST toDown" << std::endl;
      for(int i = 0; i < COUT_ROWS_COLUMS; i++)
      {
         current_cells.clear();
         for(int j = COUT_ROWS_COLUMS - 1; j >= 0; j--)
         {
            if(!list_cells[i][j]) {
               addNewCellFlag = true;
               continue;
            }
            Cell cell;
            //cell.x = i;
            //cell.y = j;
            cell.value = list_cells[i][j];
            current_cells.push_back(cell);
            list_cells[i][j] = 0;
         }
         
         if(!current_cells.size()) {
            continue;
         }
         
         auto it_pre = current_cells.begin();
         std::vector<Cell>::iterator it_current = it_pre + 1;
         
         while(it_current != current_cells.end()) {
           if(it_pre->value == it_current->value) {
              it_current = current_cells.erase(it_current);
              it_pre->value = it_pre->value * 2;
              addNewCellFlag = true;
              if(it_current != current_cells.end()) {
                it_current++;
                it_pre++;
              }
           } else {
              it_current++;
              it_pre++;
           }
         }
         
         int index { COUT_ROWS_COLUMS - 1 };
         for(auto cell : current_cells)
         {
            list_cells[i][index] = cell.value;
            index--;
         }
      }
   };
   
   std::cout << "TEST key = " << key << std::endl;
   if(key == Qt::Key_A) {
      toLeft();
   } else if(key == Qt::Key_D) {
      toRight();
   } else if(key == Qt::Key_W) {
      toTop();
   } else if(key == Qt::Key_X) {
      toDown();
   } 
   
   if(!checkFreeCells()) {
      pointOnControler->setGameState(false);
   }
   
   if(addNewCellFlag) {
      addRandomCells();
   }
}
//---------------------------------------------------------------------------
bool TLogic::checkFreeCells()
{
   for(int i = 0; i < COUT_ROWS_COLUMS; i++) 
   { 
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         if(!list_cells[i][j]) {
            return true;
         }
      }
   }
   return false;
}
