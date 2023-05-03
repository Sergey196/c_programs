
#include <iostream> 
#include <string.h>

struct Data
{
   uint8_t a { 0x11 };  
   uint16_t b { 0x2233 }; 
   uint8_t c { 0x44 }; 
   uint32_t d { 0x55667788 };
};
 
int main()
{
   Data data; 
   uint32_t array[4] { 0, 0, 0, 0 };
   memcpy(array, &data, 16); 
   for(int i = 0; i < 4; i++)
   {
     std::cout << "TEST = " << std::hex << array[i] << std::endl;  
   }
   return 0; 
}
