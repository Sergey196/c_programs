

#ifndef TCONTROLLER_H
#define TCONTROLLER_H

#include "tgui.h"
#include "tlogic.h"

class TController
{
   public:
      TController(); 
      ~TController();
      void start();
      void startGame() { logic->startGame(); }
      CellState getCellValue(int x, int y);
      void selectCell(int x, int y);
      void gameStatus(bool status);
   private:
      TGui *gui;
      TLogic *logic;
};

#endif // TCONTROLLER_H
