#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    mymsg mb;
    
    
    int fd;
    char send[1024];
    
    if ((fd=open("/dev/tty", O_RDWR | O_NONBLOCK | O_CLOEXEC | O_NOCTTY)) < 0)
    {
	   fprintf(stderr, "%s: Cannot open terminal: %s (error %d)\n", argv[0], strerror(errno), errno);
    } 
    
    while(true)
    {
       	if(read(fd, send, sizeof(send)) >= 0)
	    {
          
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
              }
           }
        
        }
        
        if (msgrcv(mq, &mb, sizeof(mymsg), node_address, IPC_NOWAIT) >= 0)
		{
           printf("%s\n", mb.mtext); 
        }
    }
    
   return 0;
} 
 
 
