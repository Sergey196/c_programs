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

enum CellValue
{
   FREE,
   SELECT,
   MINE,
   MINE_BOM
};

struct CellState
{
   CellValue value { FREE };
   int coutMines { 0 };
   bool isCheck { false };
};

#endif
