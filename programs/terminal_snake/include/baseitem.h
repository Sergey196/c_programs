#ifndef TDEFINES_BASEITEM_H
#define TDEFINES_BASEITEM_H 1

const int COUT_ROWS_WIDTH { 50 };
const int COUT_ROWS_HEIGHT { 25 };
const unsigned int ONE_SECOND_IN_NS { 1000000000 };

enum CellValue
{
   FREE,
   FOOD,
   SNAKE,
   BLOCK
};

enum Direction
{
   UP,
   DOWN,
   LEFT,
   RIGHT
};

struct CellCoordinats
{
   int x;
   int y;
};

#endif
