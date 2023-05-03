#include "logic.h"
#include <cstring>

//-------------------------------------------------------------------------
Logic::Logic(Controler *_pointControler)
{
   pointControler = _pointControler; 
}
//-------------------------------------------------------------------------
void Logic::selectUp()
{
   if(selectCell.y >= COUT_CELLS - 1) {
      return; 
   } 
   selectCell.y = selectCell.y + 1; 
}
//-------------------------------------------------------------------------
void Logic::selectDown()
{
   if(selectCell.y < 1) {
      return; 
   } 
   selectCell.y = selectCell.y - 1; 
}
//-------------------------------------------------------------------------
void Logic::selectLeft()
{
   if(selectCell.x >= COUT_CELLS - 1) {
      return; 
   } 
   selectCell.x = selectCell.x + 1;  
}
//-------------------------------------------------------------------------
void Logic::selectRight()
{
   if(selectCell.x < 1) {
      return; 
   } 
   selectCell.x = selectCell.x - 1;  
}
//-------------------------------------------------------------------------
void Logic::changeNewField()
{
    for(int i = 0; i < COUT_CELLS; i++) {
       for(int j = 0; j < COUT_CELLS; j++) { 
          if(cells[i][j] == SELECT_START) {
             cells[i][j] = EMPTY; 
          }  
       }
    }
    CELL_STATE feels = cells[selectCell.x][selectCell.y];
    switch (feels) {
       case EMPTY: {
          cells[selectCell.x][selectCell.y] = SELECT_END;  
          break;
       }
       case WHITE_PAVN: case BLACK_PAVN: {
          
          break;
       }
       default: break;
   }
}
//-------------------------------------------------------------------------
void Logic::refresh()
{
   for(int i = 0; i < COUT_CELLS; i++) {
      for(int j = 0; j < COUT_CELLS; j++) { 
         cells[i][j] = EMPTY;  
      }
   }
   
   cells[0][0] = BLACK_ROOK;
   cells[0][7] = BLACK_ROOK;
   cells[7][0] = WHITE_ROOK;
   cells[7][7] = WHITE_ROOK;
   cells[0][1] = WHITE_KNIGHT;
   cells[0][6] = WHITE_KNIGHT;
   cells[7][1] = BLACK_KNIGHT;
   cells[7][6] = BLACK_KNIGHT;
   cells[0][2] = WHITE_BISHOP;
   cells[0][5] = WHITE_BISHOP;
   cells[7][2] = BLACK_BISHOP;
   cells[7][5] = BLACK_BISHOP;
   cells[0][3] = WHITE_QUEEN;
   cells[0][4] = WHITE_KING;
   cells[7][3] = BLACK_QUEEN;
   cells[7][4] = BLACK_KING;
   for(int i = 0; i < COUT_CELLS; i++) {
      cells[1][i] = WHITE_PAVN; 
      cells[6][i] = BLACK_PAVN; 
   }
   
   selectCell.x = 0;
   selectCell.y = 0;
}
