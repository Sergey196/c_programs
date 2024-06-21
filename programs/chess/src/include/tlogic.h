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
      void start();
      CellValue getCellValue(int x, int y) { return fieldFigures[x][y]; }
      CellEvent getCellEvent(int x, int y) { return fieldEvents[x][y]; }
      void cellClick(int x, int y);
   private:
      bool checkPos(int x, int y);
      bool checkWhiteStep(int x, int y);
      bool checkBlackStep(int x, int y);
      void setStep(int x, int y);
      void selectNewFigure(int x, int y);
      void setWhitePawnSteps(int x, int y);
      void setBlackPawnSteps(int x, int y);
      void setKnightSteps(int x, int y, bool (TLogic::*func)(int, int));
      void setBishopSteps(int x, int y, bool (TLogic::*func)(int, int));
      void setRookSteps(int x, int y, bool (TLogic::*func)(int, int));
      void setQueenSteps(int x, int y, bool (TLogic::*func)(int, int));
      void setKingWhiteSteps(int x, int y);
      void setKingBlackSteps(int x, int y);
      void updateWhitePawnSteps(int x, int y);
      void updateBlackPawnSteps(int x, int y);
      void updateKingSteps(int x, int y, bool (TLogic::*func)(int, int));
      bool updateWhiteStep(int x, int y);
      bool updateBlackStep(int x, int y);
      void updateAttckState();
      TController *pointOnControler;
      CellValue fieldFigures[COUT_ROWS_COLUMS][COUT_ROWS_COLUMS];
      CellEvent fieldEvents[COUT_ROWS_COLUMS][COUT_ROWS_COLUMS];
      CellAttack fieldWhiteAttack[COUT_ROWS_COLUMS][COUT_ROWS_COLUMS];
      CellAttack fieldBlackAttack[COUT_ROWS_COLUMS][COUT_ROWS_COLUMS];
      CellCoordinats selectFigure;
      
      bool isWhiteBlack { true };
      bool isCheck { false };
};

#endif // TLOGIC_H
