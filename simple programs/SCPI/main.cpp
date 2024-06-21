// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 
#include <iostream>
#define PORT 5555 

int sock = 0; 
char buffer[4096]; 

void print_idn()
{
    std::string cmd = "*IDN?\n"; 
    int res1 = send(sock, cmd.c_str(), cmd.length(), 0); 
        
    int res2 = recv(sock, buffer, sizeof(buffer), 0); 
    
    std::cout << "TEST1 = " << res1 <<  std::endl; 
    std::cout << "TEST2 = " << res2 <<  std::endl; 
    std::cout << "TEST3 = " << buffer << std::endl; 
}

void print_ese()
{
    std::string cmd = "*TRIGger:COUNt?\n"; 
    int res1 = send(sock, cmd.c_str(), cmd.length(), 0); 
        
    int res2 = recv(sock, buffer, sizeof(buffer), 0); 
    
    std::cout << "TEST1 = " << res1 <<  std::endl; 
    std::cout << "TEST2 = " << res2 <<  std::endl; 
    std::cout << "TEST3 = " << buffer << std::endl; 
}

void create_file()
{
    FILE *ptr = fopen("filename.bmp", "w");
    if(ptr == NULL) {
       return; 
    }
    
    std::string cmd = "DISPlay:DATA?\n"; 
    
    int size { 0 };
    
    for(int i = 0; i < 800; i++)
    { 
       memset(buffer, 0, sizeof(buffer));
       int res1 = send(sock, cmd.c_str(), cmd.length(), 0); 
           
       int res2 = recv(sock, buffer, sizeof(buffer), 0); 
       
       //std::cout << "TEST1 = " << res1 <<  std::endl; 
       //std::cout << "TEST2 = " << res2 <<  std::endl; 
       //std::cout << "TEST3 = " << buffer << std::endl; 
       
       if(i == 0) {
          char string_size[] = { buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8], buffer[9], buffer[10], '\0' }; 
          sscanf(string_size, "%d", &size);
          std::cout << "TEST size = " << size <<  std::endl; 
          fwrite(buffer + 11, res2 - 11, 1, ptr); //11
          size -= res2 - 12;
       } else {
          fwrite(buffer, res2, 1, ptr); //11 
           size -= res2;
       }
       
       std::cout << "TEST size - = " << size <<  std::endl; 
       
       if(size == 0) {
          break;  
       }
    } 
    
    fclose(ptr); 
}
   
int main(int argc, char const *argv[]) 
{ 
    struct sockaddr_in serv_addr; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "192.168.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    
    struct timeval timeout;
    timeout.tv_sec = 20;
    timeout.tv_usec = 0;
    
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))) 
    { 
        perror("setsockopt"); 
    } 
    
    if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout))) 
    { 
        perror("setsockopt"); 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    //int status = fcntl(sock, F_SETFL, O_NONBLOCK);
    
    print_ese();

    return 0; 
}  

 
