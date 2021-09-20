// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>

#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
    }  
    
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))) 
    { 
        perror("setsockopt"); 
    } 
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout))) 
    { 
        perror("setsockopt"); 
    } 
    
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    { 
        perror("bind failed"); 
    } 
    
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
    } 
    
    while(true)
    { 
       new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen); 
       if (new_socket < 0) 
       { 
           perror("accept"); 
       } 
       else
       {
          break; 
       }
    }
    
    //fcntl(new_socket, F_SETFL, O_NONBLOCK);

    while(true)
    { 
        //////////////////////////////////////////
        /*int error_code;
        socklen_t error_code_size = sizeof(error_code);
        getsockopt(new_socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
        
        if(error_code > 0)
        {
           continue; 
        }*/
        
        std::cout << "TEST0 = " << error_code <<  std::endl;
        //////////////////////////////////////
        std::string hello = "Hello from server"; 
        int res1 = send(new_socket, hello.c_str(), hello.length(), 0); 
        int res2 = recv(new_socket, buffer, 1024, 0);  
        
        std::cout << "TEST1 = " << res1 <<  std::endl; 
        std::cout << "TEST2 = " << res2 <<  std::endl; 
        std::cout << "TEST3 = " << buffer << std::endl; 
        memset(buffer, 0, sizeof(buffer));
        sleep(1); 
    }  
    return 0; 
}  
 
