#include <unistd.h>
#include <vector>
#include <thread>
#include <iostream>
#include <atomic>

int main(int argc, char *argv[])
{
  std::atomic<std::vector<unsigned long>> vec; 
  int cout = 1000;
  unsigned long index = 0;

  std::thread([&]
  {
     for (int i = 0; i < cout; i++)
     {
        index++;
        vec.load().push_back(index);
        std::cout << "TEST1 = " << vec.load().size() << std::endl;
     }
  }).detach(); 

  std::thread([&]
  {
     for (int i = 0; i < cout; i++)
     {
        index++;
        vec.load().push_back(index);
        std::cout << "TEST2 = " << vec.load().size() << std::endl;
     }
  }).detach(); 

  sleep(10);
  
  
  return 0;
} 
