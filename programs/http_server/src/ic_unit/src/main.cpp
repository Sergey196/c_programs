// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <iostream>

int main(int argc, char const *argv[]) 
{ 
    int server_fd; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024]; 

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
    }  
    
    address.sin_family = AF_INET; 
    //address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(8001); 
    inet_pton(AF_INET, "127.0.0.1", &(address.sin_addr.s_addr));
    
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
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen); 
        std::cout << "TEST1 = " << client_socket << std::endl;
        if (client_socket < 0) 
        { 
            perror("accept"); 
        } 
        
        int resultRecv = recv(client_socket, buffer, sizeof(buffer), 0); 
        
        std::cout << "TEST2 = " << resultRecv << std::endl;
        
        if (resultRecv == -1) 
        {
            std::cout << "SocketError1 = " << resultRecv <<  std::endl;
            close(client_socket);
        } 
        else if(resultRecv == 0)
        {
            std::cout << "Socket close = " << resultRecv <<  std::endl;
            close(client_socket); 
        }
        
        std::cout << "TEST3 = " << buffer << std::endl;
        
        //////////////////////////////////////
        std::string hello = "HTTP/1.1 200 OK\r\nVersion: HTTP/1.1\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: <title>Test C++ HTTP Server</title>\n<h1>Test page</h1>\n<p>This is body of the test page...</p>\n<h2>Request headers</h2>\n<pre>" + std::string(buffer) + "</pre>\n<em><small>Test C++ Http Server</small></em>\n\r\n\r\n";

        int resultSend = send(client_socket, hello.c_str(), hello.length(), 0); 
        
        std::cout << "TEST4 = " << resultSend << std::endl;
        
        if (resultSend == -1) 
        {
            std::cout << "SocketError2 = " << resultSend <<  std::endl;
        } 
        close(client_socket);
    }  
    
    close(server_fd);
    
    return 0; 
}  
 
