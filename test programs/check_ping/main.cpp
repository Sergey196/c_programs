#include <iostream>

int main()
{
   int x = system("ping -w 1 8.8.8.8 > /dev/null 2>&1"); 
   std::cout << "TEST2 = " << x << std::endl; 
   return 0; 
}
