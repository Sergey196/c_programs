#include <iostream>
#include <thread>
#include <pthread.h> 
#include <unistd.h>

pthread_cond_t count_nonzero;  
pthread_mutex_t count_lock;  

void run_thread()
{
   std::cout << "TEST3" << std::endl; 
   std::cout << "TEST1 lock" << std::endl; 
   pthread_cond_wait(&count_nonzero, &count_lock);
   std::cout << "TEST1 unlock" << std::endl; 
   std::cout << "TEST4" << std::endl; 
}

int main()
{
   std::cout << "TEST1" << std::endl; 
   std::thread threadTel(&run_thread);
   //pthread_mutex_lock(&count_lock);  
   threadTel.detach();
   sleep(5);
   pthread_cond_signal(&count_nonzero);  
   //pthread_mutex_unlock(&count_lock);  
   std::cout << "TEST2" << std::endl; 
   sleep(5);
   int result = system("dir");
   std::cout << result << std::endl;
   result = system("xgxghxf");
   std::cout << result << std::endl;
   return 0; 
}
