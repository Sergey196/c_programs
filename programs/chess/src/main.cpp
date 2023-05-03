#include "gui.h"
#include "logic.h"
#include "controler.h"
//#include <curses.h>

//const int GRASS_PAIR { 1 };

int main()
{
    Controler controler; 
    Gui gui(&controler);
    Logic logic(&controler);
    controler.setPointes(&logic, &gui);
    controler.start();
    
	/*initscr();			
    //////////////////////////////////////////////////////
    start_color();
    init_pair(GRASS_PAIR, COLOR_YELLOW, COLOR_GREEN);
    
    attron(COLOR_PAIR(GRASS_PAIR));
    for (int i = 0; i < 1; i++) {
        //mvhline(i, 0, ' ', COLS);
    }
    mvwprintw(stdscr, 0, 0, "%s", "jksdgkdgklsdg");
    attroff(COLOR_PAIR(GRASS_PAIR));
    /////////////////////////////////////////////////////
	refresh();			
	getch();		
	endwin();	*/

    return 0;
}


