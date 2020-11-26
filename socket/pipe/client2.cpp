#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <algorithm>

#define MAX_BUF 1024

int main()
{
    int fd1, fd2;
    std::string myfifo1 = "pipeMy1";
    std::string myfifo2 = "pipeMy2";
    char buf[MAX_BUF];

    fd1 = open(myfifo1.c_str(), O_RDWR);
    
    mkfifo(myfifo2.c_str(), 0666);
    fd2 = open(myfifo2.c_str(), O_RDWR);
    
    
    std::thread sendMy([&](){
       while(true)
       {
          write(fd2, "send client2", sizeof("send client2"));
          usleep(100);
       }
    });
    
    std::thread readMy([&](){
       while(true)
       {
          read(fd1, buf, MAX_BUF);
          printf("Received: %s\n", buf);
          usleep(100);
       }
    });
    
    while(true)
    {
        
    }
    
    close(fd1);
    close(fd2);

    return 0;
}
