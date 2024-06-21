

#ifndef TCONTROLLER_H
#define TCONTROLLER_H

#include "tgui.h"
#include "tlogic.h"

class TController
{
   public:
      TController(); 
      ~TController();
      void startGui();
      CellValue getCellValue(int x, int y);
      CellEvent getCellEvent(int x, int y);
      void cellClick(int x, int y);
   private:
      TGui *gui;
      TLogic *logic;
};

#endif // TCONTROLLER_H
