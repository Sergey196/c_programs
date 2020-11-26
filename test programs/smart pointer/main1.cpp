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
   std::unique_ptr<int> x_ptr(new int(42));
   std::unique_ptr<int> y_ptr;


   y_ptr = std::move(x_ptr);
   
   std::cout << "TEST1 = " << x_ptr.get() << std::endl;
   std::cout << "TEST2 = " << y_ptr.get() << std::endl;
   
   return 0;
}
 
