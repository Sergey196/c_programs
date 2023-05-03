#include <cstring>
#include <iostream>

int main()
{
   int *array = new int[400];
   memset(array, 0xA5, sizeof(int) * 400);
   std::cout << "INT size = " << sizeof(int) << std::endl;
   std::cout << "INT* size = " << sizeof(int*) << std::endl;


   array -= 10;

   delete[] array;
}
