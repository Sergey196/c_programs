// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 
#include <iostream>
#define PORT 8888 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))) 
    { 
        perror("setsockopt"); 
    } 
    
    if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout))) 
    { 
        perror("setsockopt"); 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    //int status = fcntl(sock, F_SETFL, O_NONBLOCK);
    
    while(true)
    { 
        std::cout << "TEST1 = " << sock << std::endl;  
        std::string hello = "Hello from client = " + std::to_string(argc); 
        int res1 = send(sock, hello.c_str(), hello.length(), 0); 
        int res2 = recv(sock, buffer, 1024, 0);  
        std::cout << "TEST2 = " << buffer << std::endl; 
        memset(buffer, 0, sizeof(buffer));
        sleep(1); 
    }  
    
    return 0; 
}  

