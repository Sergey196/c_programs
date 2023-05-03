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
    
    //////////////////////
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100;
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)))
    {
        return 0;
    }
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)))
    {
        return 0;
    }
    //////////////////////
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int len = sizeof(servaddr); 
      
    while(true)
    {
       int result = sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr)); 
       std::cout << "TEST1 = " << result << std::endl;  
       result = recvfrom(sockfd, (char *)buffer, 1024,  MSG_WAITALL, (struct sockaddr *) &servaddr, (socklen_t*)&len); 
       std::cout << "TEST1 = " << result << std::endl;
       std::cout << "TEST = " << buffer << std::endl;
       memset(buffer, 0, sizeof(buffer));
       usleep(100000); 
    }
  
    close(sockfd); 
    return 0; 
} 

