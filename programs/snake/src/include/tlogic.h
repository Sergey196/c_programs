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
#include <queue>
#include <QTimer>
#include <QObject>

class TController;

class TLogic: public QObject
{
public: 
   TLogic(TController *pointOnControler); 
   void startGame();
   CellValue getCellValue(int x, int y) { return field[x][y]; }
   void setDirection(Direction _direction);
   
private:
   void foodRandom(int coutFields); 
   TController *pointOnControler;
   CellValue field[COUT_ROWS_COLUMS][COUT_ROWS_COLUMS] { { FREE } };
   //CellCoordinats randomCellsCoordinateContener[100];
   std::queue<CellCoordinats> snakeCells;
   Direction direction { RIGHT };
   int coutFood { 0 };
   QTimer timerStep;
   int interval { 1000 };
private slots:
    void step();
};

#endif // TLOGIC_H
