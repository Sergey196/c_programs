#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <thread>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

#define MSGKEY	100


struct  mymsg 
{
   long  mtype;     /* message type */
   char  mtext[1024];  /* message text */
};

std::vector<std::string> split(std::string str, std::string delimiter)
{
   std::vector<std::string> list;
   size_t pos = 0;
   std::string token;
   while ((pos = str.find(delimiter)) != std::string::npos) {
       token = str.substr(0, pos);
       list.push_back(token);
       str.erase(0, pos + delimiter.length());
   }
   list.push_back(str);
   return list;
};


int main(int argc, char const *argv[])
{
  
  if(argc < 2)
  {
     return 0; 
  }
  
  int node_address = std::atol(argv[1]);
  int mq = msgget(MSGKEY, 0644 | IPC_CREAT);
    
    std::thread sendMy([&]() 
    {
       size_t l;  
       mymsg mb;
       char send[1024] = "";
       while(fgets(send, sizeof(send), stdin) != NULL)
       {
          if((l = strlen(send)) == 0) 
          { 
             continue; 
          }
          if(send[l - 1] == '\n') 
          { 
              send[l - 1] = 0; l--; 
          }
          
          if(l == 0)
          {
             continue;  
          }
          
          std::string fullMessage = std::string(send);
          std::string stringIds = fullMessage.substr(0, fullMessage.find(" "));
          std::string currentMessage = fullMessage.substr(fullMessage.find(" ") + 1, fullMessage.length());
          
          auto ids = split(stringIds, ",");
          
          
          for (auto id : ids) // access by reference to avoid copying
          {  
             mb.mtype = std::stol(id);
             strcpy(mb.mtext, currentMessage.c_str()); 
             
             if(msgsnd(mq, &mb, sizeof(mymsg), 0) == -1) 
             {
                 perror("msgsnd()");
                 break;
             }
          }
       }
    });
    
    std::thread readMy([&]()
    {
       mymsg mb; 
       while(true)
       {
          msgrcv(mq, &mb, sizeof(mymsg), node_address, 0);
          printf("%s\n", mb.mtext); 
       }
    });
    
    while(true)
    {
        
    }
    
  return 0;
} 
 
 
