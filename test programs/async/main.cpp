#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <future>
#include <unistd.h>



int main()
{ 
   /*auto a1 = std::async([]
   {
      std::cout << "TEST1" << std::endl;  
      sleep(3); 
      std::cout << "TEST2" << std::endl; 
   });
    
   auto a2 = std::async([]
   {
      std::cout << "TEST3" << std::endl;  
      sleep(7); 
      std::cout << "TEST4" << std::endl; 
   });
   
   auto a3 = std::async(std::launch::deferred, []
   {
      std::cout << "TEST5" << std::endl;  
      sleep(3); 
      std::cout << "TEST6" << std::endl; 
   });*/
   
   
  for(int i = 0; i < 5; i++) 
   {
   std::thread([&]
   {
      std::cout << "TEST1" << std::endl;  
      sleep(3); 
      std::cout << "TEST2" << std::endl; 
   }).detach();
    
   std::thread([&]
   {
      std::cout << "TEST3" << std::endl;  
      sleep(7); 
      std::cout << "TEST4" << std::endl;
   }).detach();
   
   std::cout << "TEST6 = " << i << std::endl; 
   }
  
   
   return 0;
}
