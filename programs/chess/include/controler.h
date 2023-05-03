#ifndef CONTROLER_H
#define CONTROLER_H

#include "baseitem.h"

class Logic;
class Gui;

class Controler
{
   public:
      void setPointes(Logic *_pointLogic, Gui *_pointGui) { pointLogic = _pointLogic; pointGui = _pointGui; } 
      void start();
      CELL_STATE getCellValue(int x, int y);
      void refresh();
   private:  
      Logic *pointLogic;  
      Gui *pointGui;  

};

#endif // CONTROLER_H
