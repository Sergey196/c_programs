#include "tmessageprocess.h"

#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <iostream>

namespace _protocol
{
   void TMessageProcess::initSocket()
   {
      int main_sock = socket(AF_INET, SOCK_STREAM, 0);  
      
      struct timeval timeout;
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      
      setsockopt(main_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)); 
      setsockopt(main_sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)); 
      if(settings.isServer)
      { 
         int new_socket; 
         struct sockaddr_in address; 
         int addrlen = sizeof(address); 
         
         address.sin_family = AF_INET; 
         address.sin_addr.s_addr = INADDR_ANY; 
         address.sin_port = htons(settings.port); 
         
         
         bind(main_sock, (struct sockaddr *)&address, sizeof(address)); 
         listen(main_sock, 3); 
         
         while(true)
         { 
            new_socket = accept(main_sock, (struct sockaddr *)&address, (socklen_t*)&addrlen); 
            if (!(new_socket < 0)) 
            { 
                break;
            } 
         }
         
         sockfd = new_socket;
      }
      else
      {
         struct sockaddr_in serv_addr; 
         
         serv_addr.sin_family = AF_INET; 
         serv_addr.sin_port = htons(settings.port); 
            
         // Convert IPv4 and IPv6 addresses from text to binary form 
         inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); 
         
         connect(main_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); 
         
         sockfd = main_sock; 
      }
   }
   //-----------------------------------------------------------------------------
   TMessageProcess::~TMessageProcess()
   {
      close(sockfd);
   }
   //-----------------------------------------------------------------------------
   void TMessageProcess::closeSocket()
   {
      close(sockfd);
   }
   //-----------------------------------------------------------------------------
   bool TMessageProcess::messageRequest(TMessage *message)
   {
      int result = send(sockfd, message, sizeof(TMessage), 0); 
      return result > 0;
   }
   //-----------------------------------------------------------------------------
   bool TMessageProcess::messageResponse(TMessage &message)
   {
      int result = recv(sockfd, &message, sizeof(TMessage), 0); 
      return result > 0;
   }
}
