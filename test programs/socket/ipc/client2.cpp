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
    
    char b1[256] = "TEST2";
    char b2[256] = "";
    
    int i = 0;
    
    std::thread sendMy([&](){
       while(true)
       {
          i++; 
          b1[1] = i + '0'; 
          size_t l = strlen(b1); 
          msgsnd(mq1, &b1, l, 0); 
          sleep(5);
       }
    });
    
    std::thread readMy([&](){
       while(true)
       {
          msgrcv(mq2, &b2, sizeof(b2), 0, 0);
          printf("%s\n", b2); 
          sleep(1);
       }
    });
    
    while(true)
    {
        
    }
    
  return 0;
} 
