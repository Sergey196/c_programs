#include <unistd.h>
#include <iostream>
#include "gui.h"
#include "logic.h"
#include "controler.h"

Gui::Gui(Controler *_pointControler)
{
   pointControler = _pointControler;  
}
//-------------------------------------------------------------------------
Gui::~Gui()
{
   endwin();
}
//-------------------------------------------------------------------------
void Gui::repaint()
{
   bool switchCell { true };  
   auto paintColorCell = [this](int x, int y, bool &switchCell) {
      if(switchCell) {
          attron(COLOR_PAIR(GRASS_PAIR_BLACK));
          mvhline(x, y, ' ', 1);
          attroff(COLOR_PAIR(GRASS_PAIR_BLACK));
          switchCell = false;
      } else {
          attron(COLOR_PAIR(GRASS_PAIR_WHITE));
          mvhline(x, y, ' ', 1);
          attroff(COLOR_PAIR(GRASS_PAIR_WHITE)); 
          switchCell = true;
      } 
   };
   
   for(int i = 0; i < COUT_CELLS; i++) {
      for(int j = 0; j < COUT_CELLS; j++) { 
         paintColorCell(i, j, switchCell);
      }
      switchCell = !switchCell;
   }
   auto paintCell = [this](int x, int y) {
      CELL_STATE cell = pointControler->getCellValue(x, y);   
      //std::cout << "TEST1 = " << cell << std::endl;
      switch(cell)
      {

         case SELECT_START:
         {
             attron(COLOR_PAIR(GRASS_PAIR_BLUE));
             mvhline(x, y, 's', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_BLUE));
             break;
         }
         case SELECT_END:
         {
             attron(COLOR_PAIR(GRASS_PAIR_CYAN));
             mvhline(x, y, 'e', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_CYAN));
             break;
         }
         case WHITE_PAVN:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'p', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case WHITE_ROOK:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'r', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case WHITE_KNIGHT:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'h', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case WHITE_BISHOP:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'b', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case WHITE_QUEEN:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'q', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case WHITE_KING:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'k', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case BLACK_PAVN:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'p', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case BLACK_ROOK:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'r', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case BLACK_KNIGHT:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'h', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case BLACK_BISHOP:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'b', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case BLACK_QUEEN:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'q', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         case BLACK_KING:
         {
             attron(COLOR_PAIR(GRASS_PAIR_GREEN));
             mvhline(x, y, 'k', 1);
             attroff(COLOR_PAIR(GRASS_PAIR_GREEN));
             break;
         }
         default: {}
      }
   };
   for(int i = 0; i < COUT_CELLS; i++) {
      for(int j = 0; j < COUT_CELLS; j++) { 
          paintCell(i, j);
      }
   } 
}
//-------------------------------------------------------------------------
void Gui::keyPress(int key)
{
   switch (key) {
      case KEY_LEFT: {
         break;
      }
      case KEY_RIGHT: {
         break;
      }
      case KEY_UP: {
         break;
      }
      case KEY_DOWN: {
         break;
      }
      case 'q': {
         stopFlag = true; 
         break;
      }
      default: break;
   }
}
