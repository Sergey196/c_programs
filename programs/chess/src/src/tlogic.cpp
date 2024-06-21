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
#include "tcontroller.h"

TLogic::TLogic(TController *_pointOnControler)
{
   pointOnControler = _pointOnControler;
}
//---------------------------------------------------------------------------
void TLogic::start()
{
   memset(fieldFigures, FREE_VALUE, sizeof(fieldFigures));
   memset(fieldEvents, FREE_EVENT, sizeof(fieldEvents));
   fieldFigures[0][0] = WHITE_ROOK;
   fieldFigures[7][0] = WHITE_ROOK;
   fieldFigures[1][0] = WHITE_KNIGHT;
   fieldFigures[6][0] = WHITE_KNIGHT;
   fieldFigures[2][0] = WHITE_BISHOP;
   fieldFigures[5][0] = WHITE_BISHOP;
   fieldFigures[3][0] = WHITE_QUEEN;
   fieldFigures[4][0] = WHITE_KING;
   fieldFigures[0][1] = WHITE_PAWN;
   fieldFigures[1][1] = WHITE_PAWN;
   fieldFigures[2][1] = WHITE_PAWN;
   fieldFigures[3][1] = WHITE_PAWN;
   fieldFigures[4][1] = WHITE_PAWN;
   fieldFigures[5][1] = WHITE_PAWN;
   fieldFigures[6][1] = WHITE_PAWN;
   fieldFigures[7][1] = WHITE_PAWN;

   fieldFigures[0][7] = BLACK_ROOK;
   fieldFigures[7][7] = BLACK_ROOK;
   fieldFigures[1][7] = BLACK_KNIGHT;
   fieldFigures[6][7] = BLACK_KNIGHT;
   fieldFigures[2][7] = BLACK_BISHOP;
   fieldFigures[5][7] = BLACK_BISHOP;
   fieldFigures[3][7] = BLACK_QUEEN;
   fieldFigures[4][7] = BLACK_KING;
   fieldFigures[0][6] = BLACK_PAWN;
   fieldFigures[1][6] = BLACK_PAWN;
   fieldFigures[2][6] = BLACK_PAWN;
   fieldFigures[3][6] = BLACK_PAWN;
   fieldFigures[4][6] = BLACK_PAWN;
   fieldFigures[5][6] = BLACK_PAWN;
   fieldFigures[6][6] = BLACK_PAWN;
   fieldFigures[7][6] = BLACK_PAWN;
   
   /*fieldWhiteAttack[0][2] = ATTACK_STATE;
   fieldWhiteAttack[1][2] = ATTACK_STATE;
   fieldWhiteAttack[2][2] = ATTACK_STATE;
   fieldWhiteAttack[3][2] = ATTACK_STATE;
   fieldWhiteAttack[4][2] = ATTACK_STATE;
   fieldWhiteAttack[5][2] = ATTACK_STATE;
   fieldWhiteAttack[6][2] = ATTACK_STATE;
   fieldWhiteAttack[7][2] = ATTACK_STATE;
   
   fieldBlackAttack[0][5] = ATTACK_STATE;
   fieldBlackAttack[1][5] = ATTACK_STATE;
   fieldBlackAttack[2][5] = ATTACK_STATE;
   fieldBlackAttack[3][5] = ATTACK_STATE;
   fieldBlackAttack[4][5] = ATTACK_STATE;
   fieldBlackAttack[5][5] = ATTACK_STATE;
   fieldBlackAttack[6][5] = ATTACK_STATE;
   fieldBlackAttack[7][5] = ATTACK_STATE;*/
}
//---------------------------------------------------------------------------
void TLogic::selectNewFigure(int x, int y)
{
   selectFigure.x = x;
   selectFigure.y = y; 
}
//---------------------------------------------------------------------------
bool TLogic::checkPos(int x, int y)
{
   return !((x < 0) || (x > COUT_ROWS_COLUMS - 1) || (y < 0) || (y > COUT_ROWS_COLUMS - 1));
}
//---------------------------------------------------------------------------
bool TLogic::checkWhiteStep(int x, int y)
{
   if(!checkPos(x, y)) {
      return false;
   }
   if((fieldFigures[x][y] == WHITE_PAWN) || (fieldFigures[x][y] == WHITE_ROOK) || (fieldFigures[x][y] == WHITE_BISHOP) || (fieldFigures[x][y] == WHITE_QUEEN) || (fieldFigures[x][y] == WHITE_KING)) {
      return false;
   }
   setStep(x, y);
   return true;
}
//---------------------------------------------------------------------------
bool TLogic::checkBlackStep(int x, int y)
{
   if(!checkPos(x, y)) {
      return false;
   }
   if((fieldFigures[x][y] == BLACK_PAWN) || (fieldFigures[x][y] == BLACK_KNIGHT) || (fieldFigures[x][y] == BLACK_ROOK) || (fieldFigures[x][y] == BLACK_BISHOP) || (fieldFigures[x][y] == BLACK_QUEEN) || (fieldFigures[x][y] == BLACK_KING)) {
      return false;
   }
   setStep(x, y);
   return true;
}
//---------------------------------------------------------------------------
void TLogic::setStep(int x, int y)
{
   if(fieldFigures[x][y] != FREE_VALUE) {
      fieldEvents[x][y] = ATTACK;
   } else {
      fieldEvents[x][y] = STEP;
   }
}
//---------------------------------------------------------------------------
void TLogic::setWhitePawnSteps(int x, int y)
{
   selectNewFigure(x, y);
   if(y == 1) {
      if(fieldFigures[x][y + 1] == FREE_VALUE) {
         checkWhiteStep(x, y + 1);
      }
      if(fieldFigures[x][y + 2] == FREE_VALUE) {
         checkWhiteStep(x, y + 2);
      }
      return;
   }
   if(fieldFigures[x][y + 1] == FREE_VALUE) {
      checkWhiteStep(x, y + 1);
   }
   if((x > 0) && (fieldFigures[x - 1][y + 1] != FREE_VALUE)) {
      checkWhiteStep(x - 1, y + 1);
   }
   if((x < COUT_ROWS_COLUMS - 1) && (fieldFigures[x + 1][y + 1] != FREE_VALUE)) {
      checkWhiteStep(x + 1, y + 1);
   }
}
//---------------------------------------------------------------------------
void TLogic::setBlackPawnSteps(int x, int y)
{
   selectNewFigure(x, y);
   if(y == COUT_ROWS_COLUMS - 2) {
      if(fieldFigures[x][y - 1] == FREE_VALUE) {
         checkBlackStep(x, y - 1);
      }
      if(fieldFigures[x][y - 2] == FREE_VALUE) {
         checkBlackStep(x, y - 2);
      }
      return;
   }
   if(fieldFigures[x][y - 1] == FREE_VALUE) {
      checkBlackStep(x, y - 1);
   }
   if(x > 0) {
      if(fieldFigures[x - 1][y - 1] != FREE_VALUE) {
         checkBlackStep(x - 1, y - 1);
      }
   }
   if(x < COUT_ROWS_COLUMS - 1) {
      if(fieldFigures[x + 1][y - 1] != FREE_VALUE) {
         checkBlackStep(x + 1, y - 1);
      }
   }
}
//---------------------------------------------------------------------------
void TLogic::setBishopSteps(int x, int y, bool (TLogic::*func)(int, int))
{
   selectNewFigure(x, y);
   int current_x = x;
   int current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x++;
      current_y++;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x--;
      current_y--;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x--;
      current_y++;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x++;
      current_y--;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
}
//---------------------------------------------------------------------------
void TLogic::setKnightSteps(int x, int y, bool (TLogic::*func)(int, int))
{
   selectFigure.x = x;
   selectFigure.y = y;
   int new_pos_x;
   int new_pos_y;
   new_pos_x = x - 2;
   new_pos_y = y - 1;
   (this->*func)(new_pos_x, new_pos_y);
   new_pos_x = x - 1;
   new_pos_y = y - 2;
   (this->*func)(new_pos_x, new_pos_y);
   new_pos_x = x + 1;
   new_pos_y = y - 2;
   (this->*func)(new_pos_x, new_pos_y);
   new_pos_x = x + 2;
   new_pos_y = y - 1;
   (this->*func)(new_pos_x, new_pos_y);
   new_pos_x = x - 2;
   new_pos_y = y + 1;
   (this->*func)(new_pos_x, new_pos_y);
   new_pos_x = x - 1;
   new_pos_y = y + 2;
   (this->*func)(new_pos_x, new_pos_y);
   new_pos_x = x + 1;
   new_pos_y = y + 2;
   (this->*func)(new_pos_x, new_pos_y);
   new_pos_x = x + 2;
   new_pos_y = y + 1;
   (this->*func)(new_pos_x, new_pos_y);
}
//---------------------------------------------------------------------------
void TLogic::setRookSteps(int x, int y, bool (TLogic::*func)(int, int))
{
   selectNewFigure(x, y);
   int current_x = x;
   int current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x++;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_y++;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x--;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_y--;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
}
//---------------------------------------------------------------------------
void TLogic::setQueenSteps(int x, int y, bool (TLogic::*func)(int, int))
{
   selectNewFigure(x, y);
   int current_x = x;
   int current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x++;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_y++;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x--;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_y--;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x++;
      current_y++;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x--;
      current_y--;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x--;
      current_y++;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
   current_x = x;
   current_y = y;
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) {
      current_x++;
      current_y--;
      if(!(this->*func)(current_x, current_y)) {
         break;
      }
      if(fieldEvents[current_x][current_y] == ATTACK) {
         break;
      }
   }
}
//---------------------------------------------------------------------------
void TLogic::setKingWhiteSteps(int x, int y)
{
   if(!checkPos(x, y)) {
      return;
   }
   selectNewFigure(x, y);
   if(fieldBlackAttack[x + 1][y] == FREE_STATE) {
      checkWhiteStep(x + 1, y);
   }
   if(fieldBlackAttack[x][y + 1] == FREE_STATE) {
      checkWhiteStep(x, y + 1);
   }
   if(fieldBlackAttack[x - 1][y] == FREE_STATE) {
      checkWhiteStep(x - 1, y);
   }
   if(fieldBlackAttack[x][y - 1] == FREE_STATE) {
      checkWhiteStep(x, y - 1);
   }
   if(fieldBlackAttack[x + 1][y + 1] == FREE_STATE) {
      checkWhiteStep(x + 1, y + 1);
   }
   if(fieldBlackAttack[x - 1][y - 1] == FREE_STATE) {
      checkWhiteStep(x - 1, y - 1);
   }
   if(fieldBlackAttack[x + 1][y - 1] == FREE_STATE) {
      checkWhiteStep(x + 1, y - 1);
   }
   if(fieldBlackAttack[x - 1][y + 1] == FREE_STATE) {
      checkWhiteStep(x - 1, y + 1);
   }
}
//---------------------------------------------------------------------------
void TLogic::setKingBlackSteps(int x, int y)
{
   if(!checkPos(x, y)) {
      return;
   }
   selectNewFigure(x, y);
   if(fieldWhiteAttack[x + 1][y] == FREE_STATE) {
      checkBlackStep(x + 1, y);
   }
   if(fieldWhiteAttack[x][y + 1] == FREE_STATE) {
      checkBlackStep(x, y + 1);
   }
   if(fieldWhiteAttack[x - 1][y] == FREE_STATE) {
      checkBlackStep(x - 1, y);
   }
   if(fieldWhiteAttack[x][y - 1] == FREE_STATE) {
      checkBlackStep(x, y - 1);
   }
   if(fieldWhiteAttack[x + 1][y + 1] == FREE_STATE) {
      checkBlackStep(x + 1, y + 1);
   }
   if(fieldWhiteAttack[x - 1][y - 1] == FREE_STATE) {
      checkBlackStep(x - 1, y - 1);
   }
   if(fieldWhiteAttack[x + 1][y - 1] == FREE_STATE) {
      checkBlackStep(x + 1, y - 1);
   }
   if(fieldWhiteAttack[x - 1][y + 1] == FREE_STATE) {
      checkBlackStep(x - 1, y + 1);
   }
}
//---------------------------------------------------------------------------
bool TLogic::updateWhiteStep(int x, int y)
{
   if(!checkPos(x, y)) {
      return false;
   }
   if((fieldFigures[x][y] == WHITE_PAWN) || (fieldFigures[x][y] == WHITE_ROOK) || (fieldFigures[x][y] == WHITE_BISHOP) || (fieldFigures[x][y] == WHITE_QUEEN) || (fieldFigures[x][y] == WHITE_KING)) {
      return false;
   }
   if(fieldFigures[x][y] == BLACK_KING) {
      isCheck = true; 
      return false;
   }
   fieldWhiteAttack[x][y] = ATTACK_STATE;
   return true; 
}
//---------------------------------------------------------------------------
bool TLogic::updateBlackStep(int x, int y)
{
   if(!checkPos(x, y)) {
      return false;
   }
   if((fieldFigures[x][y] == BLACK_PAWN) || (fieldFigures[x][y] == BLACK_KNIGHT) || (fieldFigures[x][y] == BLACK_ROOK) || (fieldFigures[x][y] == BLACK_BISHOP) || (fieldFigures[x][y] == BLACK_QUEEN) || (fieldFigures[x][y] == BLACK_KING)) {
      return false;
   }
   if(fieldFigures[x][y] == WHITE_KING) {
      isCheck = true; 
      return false;
   }
   fieldBlackAttack[x][y] = ATTACK_STATE;
   return true;
}
//---------------------------------------------------------------------------
void TLogic::updateWhitePawnSteps(int x, int y)
{
   updateWhiteStep(x + 1, y + 1);
   updateWhiteStep(x - 1, y + 1);
}
//---------------------------------------------------------------------------
void TLogic::updateBlackPawnSteps(int x, int y)
{
   updateBlackStep(x + 1, y - 1);
   updateBlackStep(x - 1, y - 1);
}
//---------------------------------------------------------------------------
void TLogic::updateKingSteps(int x, int y, bool (TLogic::*func)(int, int))
{
   (this->*func)(x + 1, y);
   (this->*func)(x, y + 1);
   (this->*func)(x - 1, y);
   (this->*func)(x, y - 1);
   (this->*func)(x + 1, y + 1);
   (this->*func)(x - 1, y - 1);
   (this->*func)(x + 1, y - 1);
   (this->*func)(x - 1, y + 1);
}
//---------------------------------------------------------------------------
void TLogic::updateAttckState()
{
   
   auto setNewState = [this](int x, int y) {
      switch(fieldFigures[x][y])
      {
         case FREE_VALUE: 
             break;
         case WHITE_PAWN: 
             updateWhitePawnSteps(x, y);
             break;
         case WHITE_KNIGHT: 
             setKnightSteps(x, y, &TLogic::updateWhiteStep);
             break;
         case WHITE_ROOK: 
             setRookSteps(x, y, &TLogic::updateWhiteStep); 
             break;
         case WHITE_BISHOP: 
             setBishopSteps(x, y, &TLogic::updateWhiteStep); 
             break;
         case WHITE_QUEEN: 
             setQueenSteps(x, y, &TLogic::updateWhiteStep); 
             break;
         case WHITE_KING: 
             updateKingSteps(x, y, &TLogic::updateWhiteStep); 
             break;
         case BLACK_PAWN: 
             updateBlackPawnSteps(x, y);
             break;
         case BLACK_KNIGHT: 
             setKnightSteps(x, y, &TLogic::updateBlackStep);
             break;
         case BLACK_ROOK: 
             setRookSteps(x, y, &TLogic::updateBlackStep); 
             break;
         case BLACK_BISHOP: 
             setBishopSteps(x, y, &TLogic::updateBlackStep); 
             break;
         case BLACK_QUEEN: 
             setQueenSteps(x, y, &TLogic::updateBlackStep); 
             break;
         case BLACK_KING: 
             updateKingSteps(x, y, &TLogic::updateBlackStep); 
             break;
      }  
   };
   
   memset(fieldWhiteAttack, FREE_STATE, sizeof(fieldWhiteAttack));
   memset(fieldBlackAttack, FREE_STATE, sizeof(fieldBlackAttack));
      
   for(int i = 0; i < COUT_ROWS_COLUMS - 1; i++) 
   {
      for(int j = 0; j < COUT_ROWS_COLUMS - 1; j++) 
      {
         setNewState(i, j);
      }
   }
}
//---------------------------------------------------------------------------
void TLogic::cellClick(int x, int y)
{
   CellValue valueFigure = fieldFigures[selectFigure.x][selectFigure.y];
   CellEvent eventValue = fieldEvents[x][y];
   memset(fieldEvents, FREE_EVENT, sizeof(fieldEvents));
   if(eventValue != FREE_EVENT) {
      fieldFigures[selectFigure.x][selectFigure.y] = FREE_VALUE;
      fieldFigures[x][y] = valueFigure;
      isWhiteBlack = !isWhiteBlack;
      updateAttckState();
   } else {
      switch(fieldFigures[x][y])
      {
         case FREE_VALUE: 
             break;
         case WHITE_PAWN: 
             if(!isWhiteBlack) {
                return;
             }
             setWhitePawnSteps(x, y);
             break;
         case WHITE_KNIGHT: 
             if(!isWhiteBlack) {
                return;
             }
             setKnightSteps(x, y, &TLogic::checkWhiteStep);
             break;
         case WHITE_ROOK: 
             if(!isWhiteBlack) {
                return;
             }
            setRookSteps(x, y, &TLogic::checkWhiteStep);
            break;
         case WHITE_BISHOP: 
             if(!isWhiteBlack) {
                return;
             }
             setBishopSteps(x, y, &TLogic::checkWhiteStep);
             break;
         case WHITE_QUEEN: 
             if(!isWhiteBlack) {
                return;
             }
             setQueenSteps(x, y, &TLogic::checkWhiteStep);
             break;
         case WHITE_KING: 
             if(!isWhiteBlack) {
                return;
             }
             setKingWhiteSteps(x, y);
             break;
         case BLACK_PAWN: 
             if(isWhiteBlack) {
                return;
             }
             setBlackPawnSteps(x, y);
             break;
         case BLACK_KNIGHT: 
             if(isWhiteBlack) {
                return;
             }
             setKnightSteps(x, y, &TLogic::checkBlackStep);
             break;
         case BLACK_ROOK: 
             if(isWhiteBlack) {
                return;
             }
             setRookSteps(x, y, &TLogic::checkBlackStep);
             break;
         case BLACK_BISHOP: 
             if(isWhiteBlack) {
                return;
             }
             setBishopSteps(x, y, &TLogic::checkBlackStep);
             break;
         case BLACK_QUEEN: 
             if(isWhiteBlack) {
                return;
             }
             setQueenSteps(x, y, &TLogic::checkBlackStep);
             break;
         case BLACK_KING: 
             if(isWhiteBlack) {
                return;
             }
             setKingBlackSteps(x, y);
             break;
      }  
   }
}

