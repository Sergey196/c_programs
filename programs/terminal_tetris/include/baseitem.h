#ifndef TDEFINES_BASEITEM_H
#define TDEFINES_BASEITEM_H 1

const int COUT_ROWS_WIDTH { 25 };
const int COUT_ROWS_HEIGHT { 25 };
const int FIGURE_CELL_COUT { 4 };
const unsigned int ONE_SECOND_IN_NS { 1000000000 };

enum CellValue { FREE, BLOCK_WALL, BLOCK_SLEEP, BLOCK_ACTIVE };
enum Direction { UP, DOWN, LEFT, RIGHT };
enum Figure { I, T, J, S, Z, O, L };

struct NewFigureInfo
{
   Direction derection; 
   Figure figure;
   int x;
   int y;
};

struct CellCoordinats
{
   int x;
   int y;
};

#endif
