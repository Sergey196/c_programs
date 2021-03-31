// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

#include <thread>
#include <algorithm>
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
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
          std::string hello = "Hello from client\n"; 
          send(sock , hello.c_str() , hello.length() , 0 ); 
          sleep(1);
       }
    });
    
    std::thread readMy([&](){
       while(true)
       {
          valread = read( sock , buffer, 1024); 
          printf("%s\n",buffer ); 
          sleep(1);
       }
    });
    
    while(true)
    {
        
    }
    return 0; 
}  

