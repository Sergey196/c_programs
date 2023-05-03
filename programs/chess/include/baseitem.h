#ifndef TDEFINES_BASEITEM_H
#define TDEFINES_BASEITEM_H 1

const int COUT_CELLS { 8 };

const int GRASS_PAIR_BLACK { 1 };
const int GRASS_PAIR_RED { 2 };
const int GRASS_PAIR_GREEN { 3 };
const int GRASS_PAIR_YELLOW { 4 };
const int GRASS_PAIR_BLUE { 5 };
const int GRASS_PAIR_MAGENTA { 6 };
const int GRASS_PAIR_CYAN { 7 };
const int GRASS_PAIR_WHITE { 8 };

enum CELL_STATE
{
   EMPTY,
   SELECT_START,
   SELECT_END,
   WHITE_PAVN,
   WHITE_ROOK,
   WHITE_KNIGHT,
   WHITE_BISHOP,
   WHITE_QUEEN,
   WHITE_KING,
   BLACK_PAVN,
   BLACK_ROOK,
   BLACK_KNIGHT,
   BLACK_BISHOP,
   BLACK_QUEEN,
   BLACK_KING
};

struct CellInfo
{
   int x;
   int y;
};

#endif
