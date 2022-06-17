#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>
#include <mutex>

int main()
{
   std::vector<int> v;
   v.push_back(1);
   v.push_back(1);
   v.push_back(2);
   v.push_back(2);
   v.push_back(2);
   v.push_back(2);
   v.push_back(3);
   v.push_back(4);
   v.push_back(4);
   
   
   
   std::for_each(v.begin(), v.end(), [&](auto& item) -> void 
   {
       if (item == 2) 
       { 
          std::cout << "TEST = " << item << std::endl;
          v.erase(v.begin());
       }
   });
}
