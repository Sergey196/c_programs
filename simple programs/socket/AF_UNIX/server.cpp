// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream> 
#include <algorithm>

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    //char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    struct sockaddr saddr = {AF_UNIX, "/opt/ttyMy"};
       
    if (bind(server_fd, &saddr, sizeof(saddr))) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    
    for(int i = 0; i < 20; i++)
    {
       std::string hello = "Hello from server"; 
       send(new_socket, hello.c_str() , hello.length(), 0); 
       read(new_socket, buffer, 1024); 
       printf("%s\n",buffer);
       sleep(1);
    }
    
    sleep(5);
    
    close(server_fd);
    
    //valread = read( new_socket , buffer, 1024); 
    //printf("%s\n",buffer ); 
    //send(new_socket , hello , strlen(hello) , 0 ); 
    //printf("Hello message sent\n"); 
    return 0; 
}  
