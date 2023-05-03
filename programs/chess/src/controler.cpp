#include "controler.h"
#include "logic.h"
#include "gui.h"

void Controler::start()
{
   pointGui->start();
}
//-------------------------------------------------------------------------
CELL_STATE Controler::getCellValue(int x, int y)
{
   return pointLogic->getCellValue(x, y); 
}
//-------------------------------------------------------------------------
void Controler::refresh()
{
   pointLogic->refresh(); 
}
