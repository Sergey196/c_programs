#ifndef TBASEITEM_H
#define TBASEITEM_H
 
 
const int WIDTH { 420 };
const int HEIGHT { 500 };
const int FIELD_SIZE { 30 };
const int COUT_ROWS_COLUMS { 10 };
const int PANEl_X0 { 60 };
const int PANEl_X1 { 360 };
const int PANEl_Y0  { 60 };
const int PANEl_Y1  { 360 };
const int FIGURE_COORDINATES_COUT { 4 };

enum CellValue
{
   FIGURE_DOWN,
   FREE,
   FIGURE_STATIC
};

enum Direction
{
   UP,
   DOWN,
   LEFT,
   RIGHT
};

enum ResultOperation
{
   RUN,
   STOP,
   ERROR
};

enum FIGURE
{
   J,
   I,
   O,
   L,
   Z,
   T,
   S
};

struct CellCoordinats
{
   int x;
   int y;
};


#endif
