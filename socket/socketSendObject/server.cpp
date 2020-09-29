// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#include <thread>
#include <algorithm>
#include <iostream>


class Message 
{  
public:
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
    
    
    std::thread sendMy([&](){
       while(true)
       {
          //std::string hello = "Hello from server\n"; 
           
          Message messageSend; 
          messageSend.age = 5;
          messageSend.ss = 4;
          messageSend.weight = 10;
          messageSend.name[1] = 'f';
          messageSend.name[2] = 'c';
          //strcpy(messageSend.name, "server");
          send(new_socket , &messageSend , sizeof(messageSend) , 0 ); 
          sleep(1);
       }
    });
    
    std::thread readMy([&](){
       while(true)
       {
          Message messageSend; 
          valread = read(new_socket , &messageSend, sizeof(messageSend)); 
          std::cout << "age = " << messageSend.age << std::endl;
          std::cout << "ss = " << messageSend.ss << std::endl;
          std::cout << "weight = " << messageSend.weight << std::endl;
          std::cout << "name = " << messageSend.name << std::endl;
          //printf("%s\n",buffer ); 
          sleep(1);
       }
    });
    
    while(true)
    {
        
    }
    
    //valread = read( new_socket , buffer, 1024); 
    //printf("%s\n",buffer ); 
    //send(new_socket , hello , strlen(hello) , 0 ); 
    //printf("Hello message sent\n"); 
    return 0; 
}  
