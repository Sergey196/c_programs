#ifndef TBASEITEM_H
#define TBASEITEM_H
 
 
const int WIDTH { 500 };
const int HEIGHT { 500 };
const int MARGN { 45 };
const int FIELD_SIZE { 50 };
const int COUT_ROWS_COLUMS { 8 };

enum CellValue
{
   FREE_VALUE,
   WHITE_PAWN,
   WHITE_KNIGHT,
   WHITE_ROOK,
   WHITE_BISHOP,
   WHITE_QUEEN,
   WHITE_KING,
   BLACK_PAWN,
   BLACK_KNIGHT,
   BLACK_ROOK,
   BLACK_BISHOP,
   BLACK_QUEEN,
   BLACK_KING
};

enum CellEvent
{
   FREE_EVENT,
   STEP,
   ATTACK
};

enum CellAttack
{
   FREE_STATE,
   ATTACK_STATE
};


struct CellCoordinats
{
   int x;
   int y;
};


#endif
