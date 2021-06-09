// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 
#include <iostream>
#include <bitset>
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
    
    std::bitset<8> bits { "11111111" };
    std::cout << "TEST1 = " << bits.test(3) << std::endl;
    //bits.set(3);
    
    //std::cout << "TEST2 = " << bits.test(3) << std::endl;
    //std::cout << "TEST3 = " << sizeof(bits) << std::endl;
      
    while(true)
    {
       sendto(sockfd, &bits, sizeof(bits), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr)); 
          
       //recvfrom(sockfd, (char *)buffer, 1024,  MSG_DONTWAIT, (struct sockaddr *) &servaddr, (socklen_t*)&len); 
       
       //std::cout << "TEST = " << buffer << std::endl;
       //memset(buffer, 0, sizeof(buffer));
       sleep(1); 
    }
  
    close(sockfd); 
    return 0; 
} 

