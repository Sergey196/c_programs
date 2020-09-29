// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

#include <thread>
#include <algorithm>
#include <iostream>

struct Message 
{  
    int age; 
    long ss;
    float weight;
    char name[7];
}; 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    //char buffer[1024] = {0}; 
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    struct sockaddr saddr = {AF_UNIX, "serverMy"};
   
    if (connect(sock, &saddr, sizeof(saddr))) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    std::thread sendMy([&](){
       while(true)
       {
          Message messageSend; 
          messageSend.age = 5;
          messageSend.ss = 4;
          messageSend.weight = 10;
          strcpy(messageSend.name, "client");
          send(sock , &messageSend , sizeof(messageSend) , 0 ); 
          sleep(1);
       }
    });
    
    std::thread readMy([&](){
       while(true)
       {
          Message messageSend;  
          valread = read( sock , &messageSend, sizeof(messageSend)); 
          std::cout << "age = " << messageSend.age << std::endl;
          std::cout << "ss = " << messageSend.ss << std::endl;
          std::cout << "weight = " << messageSend.weight << std::endl;
          std::cout << "name = " << messageSend.name << std::endl;
          sleep(1);
       }
    });
    
    while(true)
    {
        
    }
    return 0; 
}  

