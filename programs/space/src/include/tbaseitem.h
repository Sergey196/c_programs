#ifndef TBASEITEM_H
#define TBASEITEM_H
 
 
const int WIDTH { 420 };
const int HEIGHT { 500 };
const int FIELD_SIZE { 30 };
const int COUT_ROWS { 40 };
const int COUT_COLUMS { 37 };
const int PANEl_X0 { 60 };
const int PANEl_X1 { 360 };
const int PANEl_Y0  { 60 };
const int PANEl_Y1  { 360 };
const unsigned int ONE_MKS_IN_NS { 1000 };
const unsigned int ONE_MS_IN_NS { ONE_MKS_IN_NS * 1000 };
const unsigned int ONE_SEC_IN_NS { 1000 * ONE_MS_IN_NS };
const unsigned int SLEEP_INTERVAl { 10000 };
//const unsigned int SLEEP_INTERVAl { 1000000 };
const unsigned int START_INTERVAl { 100 };
//const unsigned int START_INTERVAl { 1 };
const unsigned int SCORES_INTERVAl { 2 };
const int MIN_INTERVAL { 20 };
const int LINE_SIZE { 8 };
const int POS_BLOCKS { 34 };
const int SHIP_FIELD { 4 };

enum CellValue
{
   FREE = 0,
   BLOCK = 1,
   TUREL = 2,
   PATRON_SHIP = 3,
   PATRON_USER = 4
};

struct CellInfo
{
  int x;
  int y;
};

struct ShipInfo
{
   CellInfo cell;
   int start_pos_y;
   bool is_right_left;
};





#endif
