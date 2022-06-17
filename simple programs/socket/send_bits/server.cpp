// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#include <bitset>

#define PORT 8080 
int main() { 
    int sockfd; 
    char buffer[1024]; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int len = sizeof(servaddr);
    
    std::bitset<8> bits(0x2);
    
    while(true)
    {
       recvfrom(sockfd, &bits, sizeof(bits), MSG_DONTWAIT, ( struct sockaddr *) &cliaddr, (socklen_t*)&len); 
       std::cout << "TEST = " << bits.test(3) << std::endl;
       //sendto(sockfd, (const char *)hello, strlen(hello),  MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
       //memset(buffer, 0, sizeof(buffer));
       sleep(1);  
    }
    return 0; 
} 
 
