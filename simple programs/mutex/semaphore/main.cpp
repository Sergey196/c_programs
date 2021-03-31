
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    std::vector<int> v;
    
    int i = 0;
    std::thread sendMy([&](){
       while(true)
       {
          pthread_mutex_lock(&mutex); 
          std::cout << "TEST1" << std::endl;
          v.push_back(i);
          pthread_mutex_unlock(&mutex);
       }
    });
    
    std::thread readMy([&](){
       while(true)
       {
          auto it = find_if(v.begin(), v.end(), [&] (int j) { return i == j; } );
          if(it != v.end())
          {
              pthread_mutex_lock(&mutex); 
              std::cout << "TEST2" << std::endl;
              v.erase(it);
              i++;
              pthread_mutex_unlock(&mutex);
          }
       }
    });
    
    while(true)
    {
        
    }
    

    return 0;
}
