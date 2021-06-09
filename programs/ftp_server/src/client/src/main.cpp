
#include <iostream>


#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 
#include <iostream>
#include <fstream>
#include <cstring>
#include "lib_ftp_constants.h"

#define PORT 8081
   
int main() 
{ 
    int sock = 0; 
    struct sockaddr_in serv_addr; 
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
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    std::ofstream outfile { "2.pdf", std::ios::binary };
    
    _ftp_server::TMessage message;
    message.command = _ftp_server::commandStart;
    strcpy(message.data, "1.pdf");
    send(sock, &message, sizeof(_ftp_server::TMessage), 0);
    
    sleep(1);
    
    message.command = _ftp_server::commandData;
    send(sock, &message, sizeof(_ftp_server::TMessage), 0);
    
    while(true)
    { 
        usleep(1000); 
        memset(message.data, 0, sizeof(message.data));
        int res = recv(sock, &message, sizeof(_ftp_server::TMessage), 0); 
        
        std::cout << "TEST recv = " << res <<  std::endl; 
        
        if(message.command == _ftp_server::commandData)
        {
           std::cout << "TEST1" <<  std::endl;  
           outfile.write(message.data, sizeof(message.data)); 
           send(sock, &message, sizeof(_ftp_server::TMessage), 0);
        }
        else if(message.command == _ftp_server::commandEnd)
        {
           std::cout << "TEST2" <<  std::endl;   
           outfile.close(); 
           send(sock, &message, sizeof(_ftp_server::TMessage), 0); 
        }
    }  
    outfile.close();
    
    return 0; 
}
