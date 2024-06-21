#ifndef TBASEITEM_H
#define TBASEITEM_H
 
 
const int WIDTH { 420 };
const int HEIGHT { 500 };
const int FIELD_SIZE { 30 };
const int COUT_ROWS_COLUMS { 26 };
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
const unsigned int SCORES_INTERVAl { 10 };
const int MIN_INTERVAL { 20 };

enum CellValue
{
   FREE = 0,
   BLOCK = 1,
   TUREL = 3,
   PATRON = 4,
};

struct CellCoordinats
{
   int x;
   int y;
};



#endif
