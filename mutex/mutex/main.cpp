
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>
#include <mutex>

std::mutex mut;

int main()
{
    std::vector<int> v;
    
    int i = 0;
    std::thread sendMy([&](){
       while(true)
       {
          if(!mut.try_lock())
          {
              std::cout << "TEST1" << std::endl;
              v.push_back(i);
              mut.unlock();
          }
       }
    });
    
    std::thread readMy([&](){
       while(true)
       {
          auto it = find_if(v.begin(), v.end(), [&] (int j) { return i == j; } );
          if(it != v.end())
          {
              if(!mut.try_lock())
              {
                 std::cout << "TEST2" << std::endl;
                 v.erase(it);
                 i++;
                 mut.unlock();
              }
          }
       }
    });
    
    while(true)
    {
        
    }
    

    return 0;
}
