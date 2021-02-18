// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 
#include <iostream>
#define PORT 8080 
   
int main() { 
    int sockfd; 
    char buffer[1024]; 
    char hello[] = "Hello from client"; 
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int len = sizeof(servaddr); 
      
    while(true)
    {
       sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr)); 
          
       recvfrom(sockfd, (char *)buffer, 1024,  MSG_DONTWAIT, (struct sockaddr *) &servaddr, (socklen_t*)&len); 
       
       std::cout << "TEST = " << buffer << std::endl;
       memset(buffer, 0, sizeof(buffer));
       sleep(10); 
    }
  
    close(sockfd); 
    return 0; 
} 

