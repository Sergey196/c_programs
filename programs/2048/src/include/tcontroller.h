

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
      int getCellValue(int x, int y) { return logic->getCellValue(x, y); }
      void startGame() { logic->startGame(); }
      void setGameState(bool state) { gui->setGameState(state); }
      void keyPress(int key) { logic->keyPress(key); }
   private:
      TGui *gui;
      TLogic *logic;
};

#endif // TCONTROLLER_H
