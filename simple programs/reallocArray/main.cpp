
#include <stdlib.h>
#include <iostream>
#include <string>

struct Data
{
   std::string dataIn;  
};
 
int main()
{
   Data *array;
   array = (Data *)malloc(3 *sizeof(Data));
   std::cout << "TEST size = " << sizeof(array) << std::endl;
   for(int i = 0; i < 3; i++)
   {
      array[i].dataIn = std::to_string(i).c_str();
   }
   for(int i = 0; i < 3; i++)
   {
      std::cout << "TEST = " << array[i].dataIn << std::endl;
   }
   std::cout << "TEST size = " << sizeof(array) << std::endl;
   array = (Data *)std::realloc(array, sizeof(Data) * 5);
   
   for(int i = 3; i < 5; i++)
   {
      array[i].dataIn = std::to_string(i).c_str();
   }
   for(int i = 0; i < 5; i++)
   {
      std::cout << "TEST = " << array[i].dataIn << std::endl;
   }
   return 0;
}
