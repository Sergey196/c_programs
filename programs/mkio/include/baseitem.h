#ifndef TDEFINES_BASEITEM_H
#define TDEFINES_BASEITEM_H 1

const int WIDTH { 600 };
const int HEIGHT { 600 };
const int COUT_INPUT_BITES { 16 };
const int COUT_FULL_BITES { 20 };
const int FIRST_POSITION_INPUT_BITE { 3 };
const int MAX_INPUT_VALUE { 0xFFFF };

enum CommandType
{
   sendData,
   dataWord,
   requestWord
};

#endif
