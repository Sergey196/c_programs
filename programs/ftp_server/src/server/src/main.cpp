
#include <iostream>


// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <fcntl.h>
#include "lib_ftp_constants.h"
#include "tserveriface.h"

int main() 
{ 
    _ftp_server::TServerIface *iface = new _ftp_server::TServerIface(); 
    _ftp_server::TConfig info;
    iface->init(info);
    iface->start();
    
    /*int server_fd, new_socket; 
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
    
    std::ifstream input_file { "1.pdf", std::ios::binary };
    
    _ftp_server::TMessage message;
    unsigned long i = 0;
    while (!input_file.eof())
    {
       memset(message.data, 0, sizeof(message.data));
       input_file.read(message.data, sizeof(message.data));
       int res = send(new_socket, &message, sizeof(_ftp_server::TMessage), 0); 
       std::cout << "TEST1 send = " << i <<  std::endl; 
       std::cout << "TEST2 send = " << res <<  std::endl; 
       i++;
       usleep(1000); 
    }
    message.command = _ftp_server::commandEnd;
    send(new_socket, &message, sizeof(_ftp_server::TMessage), 0); 
    input_file.close();
    std::cout << "TEST end send" << std::endl; */

    
    
    
    return 0; 
}  
