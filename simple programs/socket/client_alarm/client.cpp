// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 
#include <iostream>
#include <signal.h>
#define PORT 8080 
   
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
    if(inet_pton(AF_INET, "192.168.1.178", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    

    signal(SIGALRM, NULL); 
    alarm(1); 
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    alarm(0);
    //int status = fcntl(sock, F_SETFL, O_NONBLOCK);
    
    while(true)
    { 
        std::string hello = "Hello from server"; 
        int res1 = send(sock, hello.c_str(), hello.length(), 0); 
        
        int res2 = recv(sock, buffer, 1024, 0);  
        
        std::cout << "TEST1 = " << res1 <<  std::endl; 
        std::cout << "TEST2 = " << res2 <<  std::endl; 
        std::cout << "TEST3 = " << buffer << std::endl; 
        memset(buffer, 0, sizeof(buffer));
        sleep(10); 
    }  
    
    return 0; 
}  

