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
   int *a = new int(42); 
   std::shared_ptr<int> x_ptr(a);
   std::shared_ptr<int> y_ptr;

   y_ptr = x_ptr;
   std::cout << *x_ptr << "\t" << *y_ptr << std::endl;

   
   return 0;
}
 
 
