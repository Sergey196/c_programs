// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#include <iostream>


struct Message 
{  
    int age; 
    long ss;
    float weight;
    char name[7];
}; 

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    //char buffer[1024] = {0}; 
    //char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    struct sockaddr saddr = {AF_UNIX, "serverMy"};
       
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
    
    
    while(true)
    {
       Message messageSend1; 
       messageSend1.age = 5;
       messageSend1.ss = 4;
       messageSend1.weight = 10;
       strcpy(messageSend1.name, "server");
       send(new_socket , &messageSend1 , sizeof(Message) , 0 ); 
       
       Message messageSend2;  
       valread = read( new_socket , &messageSend2, sizeof(Message)); 
       std::cout << "age = " << messageSend2.age << std::endl;
       std::cout << "ss = " << messageSend2.ss << std::endl;
       std::cout << "weight = " << messageSend2.weight << std::endl;
       std::cout << "name = " << messageSend2.name << std::endl;
       sleep(1); 
    }
    
    //valread = read( new_socket , buffer, 1024); 
    //printf("%s\n",buffer ); 
    //send(new_socket , hello , strlen(hello) , 0 ); 
    //printf("Hello message sent\n"); 
    return 0; 
}  
