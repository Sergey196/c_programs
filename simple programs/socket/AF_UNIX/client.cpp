// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream> 
#include <algorithm>
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    struct sockaddr saddr = {AF_UNIX, "/opt/ttyMy"};
   
    if (connect(sock, &saddr, sizeof(saddr))) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    for(int i = 0; i < 20; i++)
    {
       std::string hello = "Hello from client"; 
       send(sock, hello.c_str() , hello.length(), 0); 
       read(sock, buffer, 1024); 
       printf("%s\n", buffer);
       sleep(1);
    }
    
    close(sock);
    
    return 0; 
}  

