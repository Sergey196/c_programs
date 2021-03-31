// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
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
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    //char buffer[1024] = {0}; 
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    struct sockaddr saddr = {AF_UNIX, "serverMy"};
   
    if (connect(sock, &saddr, sizeof(saddr))) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    while(true)
    {
       Message messageSend1; 
       messageSend1.age = 5;
       messageSend1.ss = 4;
       messageSend1.weight = 10;
       strcpy(messageSend1.name, "server");
       send(sock , &messageSend1 , sizeof(Message) , 0 ); 
       
       Message messageSend2;  
       valread = read( sock , &messageSend2, sizeof(Message)); 
       std::cout << "age = " << messageSend2.age << std::endl;
       std::cout << "ss = " << messageSend2.ss << std::endl;
       std::cout << "weight = " << messageSend2.weight << std::endl;
       std::cout << "name = " << messageSend2.name << std::endl;
       sleep(1); 
    }
    
    return 0; 
}  

