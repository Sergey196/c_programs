
#include <atomic>
#include <thread>
#include <iostream>
#include <unistd.h>

class SpinLock {
    std::atomic_flag locked = ATOMIC_FLAG_INIT ;
public:
    void lock() {
        while (locked.test_and_set(std::memory_order_acquire)) { ; }
    }
    void unlock() {
        locked.clear(std::memory_order_release);
    }
};

int main()
{
   SpinLock lockSp; 
   std::thread tr1([&lockSp]() {
      for(int i = 0; i < 500; i++) 
      {
         lockSp.lock(); 
         std::cout << "TEST1 = " << i << std::endl; 
         lockSp.unlock(); 
         usleep(1500);
      }
   }); 
   
   std::thread tr2([&lockSp]() {
      for(int i = 0; i < 500; i++) 
      {
         lockSp.lock();  
         std::cout << "TEST2 = " << i << std::endl;
         lockSp.unlock(); 
         usleep(1000);
      }
   });
   tr1.detach();
   tr2.detach();
   sleep(50);
}
