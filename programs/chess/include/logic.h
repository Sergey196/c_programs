#ifndef LOGIC_H
#define LOGIC_H

#include "baseitem.h"

class Controler;

class Logic
{
   public:
       Logic(Controler *_pointControler);
       void refresh();
       void selectUp();
       void selectDown();
       void selectLeft();
       void selectRight();
       CELL_STATE getCellValue(int x, int y) { return cells[x][y]; }
   private:
       void changeNewField();
       CELL_STATE cells[COUT_CELLS][COUT_CELLS];
       CellInfo selectCell { 0, 0 };
       Controler *pointControler;
       
};

#endif // LOGIC_H
