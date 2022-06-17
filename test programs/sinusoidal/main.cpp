#include <iostream>
#include <math.h>

const int LENGTH_SIN { 300 };
const float OFFSET { -25 };
const int AMPLITUDE { 50 };
const int COUT_AMPLITUDE { 3 };

int main()
{
   float angle; 
   for(int i = 0; i < COUT_AMPLITUDE; i++)
   {
      angle = 0.0;
      for (int j = 0; j < LENGTH_SIN; j++)
      {
         std::cout << "TEST = " << (AMPLITUDE * sin(angle) + OFFSET) << std::endl;
         angle += M_PI / LENGTH_SIN;
      }
   }
}
