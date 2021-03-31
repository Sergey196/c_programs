#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <thread>
#include <algorithm>

int main(void)
{
  key_t k1 = ftok("/var", 'c');
  key_t k2 = ftok("/var", 'd');

  int mq1 = msgget(k1, 0644 | IPC_CREAT);
  int mq2 = msgget(k2, 0644 | IPC_CREAT);
    
    char b2[256] = "TEST1";
    char b1[256] = "";
    
    std::thread sendMy([&](){
       while(true)
       {
          size_t l = strlen(b2); 
          msgsnd(mq2, &b2, l, 0); 
          sleep(1);
       }
    });
    
    std::thread readMy([&](){
       while(true)
       {
          msgrcv(mq1, &b1, sizeof(b1), 0, 0);
          printf("%s\n", b1); 
          sleep(1);
       }
    });
    
    while(true)
    {
        
    }
    
  return 0;
} 
