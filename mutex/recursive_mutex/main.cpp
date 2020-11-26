#include <unistd.h> 
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>
#include <mutex>

std::recursive_mutex mut;

int main()
{
    std::vector<int> v;
    
    int i = 0;
    int j = -2;
    std::thread sendMy([&](){
       while(true)
       {
          std::cout << "TEST1" << std::endl;
          mut.lock();
          v.push_back(i);
          i++;
          mut.unlock();
       }
    });
    
    std::thread readMy([&](){
       while(true)
       {
          mut.lock(); 
          auto it = find_if(v.begin(), v.end(), [&] (int m) { return j == m; } );
          if(it != v.end())
          {
              std::cout << "TEST2" << std::endl;
              v.erase(it);
              j++;
          }
       }
       mut.unlock();
    });
    
    while(true)
    {
        
    }
    

    return 0;
}
