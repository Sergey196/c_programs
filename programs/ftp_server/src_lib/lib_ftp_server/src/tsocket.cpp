#include "tsocket.h"
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
#include <string.h>
#include <iostream>
#include "unistd.h"
#include "tlogic.h"
#include <algorithm>
#include <thread>

namespace _ftp_server
{
   TSocket::TSocket(TConfig _info, TLogic *_logic)
   {
      info = _info;
      logic = _logic;
      
      int opt = true;  
           
      char buffer[1025];  //data buffer of 1K 
           
      //create a master socket 
      if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
      {  
          perror("socket failed");  
          exit(EXIT_FAILURE);  
      }  
       
      //set master socket to allow multiple connections , 
      //this is just a good habit, it will work without this 
      if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0 )  
      {  
          perror("setsockopt");  
          exit(EXIT_FAILURE);  
      }  
      
      //type of socket created 
      address.sin_family = AF_INET;  
      address.sin_addr.s_addr = INADDR_ANY;  
      address.sin_port = htons(info.port);  
           
      //bind the socket to localhost port 8888 
      if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
      {  
          perror("bind failed");  
          exit(EXIT_FAILURE);  
      }  
      printf("Listener on port %d \n", info.port);  
           
      //try to specify maximum of 3 pending connections for the master socket 
      if (listen(master_socket, 3) < 0)  
      {  
          perror("listen");  
          exit(EXIT_FAILURE);  
      }  
        
   }
   //-----------------------------------------------------------------------------
   void TSocket::start()
   {
      int max_sd;  
      int new_socket;  
      //accept the incoming connection 
      int addrlen = sizeof(address);  
      puts("Waiting for connections ...");   
      
      while(true)  
      { 
          FD_ZERO(&readfds);  
       
          FD_SET(master_socket, &readfds);  
          FD_SET(STDIN_FILENO, &readfds);
          max_sd = master_socket;  
              
          for(int sd : clients)
          {  
                   
              if(sd > 0) 
              {
                  FD_SET( sd , &readfds); 
              }
                   
              if(sd > max_sd)  
              {
                  max_sd = sd;  
              }
          }  
       
          int activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
         
          if ((activity < 0) && (errno != EINTR))  
          {  
              printf("select error");  
          }  
           
              
          if (FD_ISSET(master_socket, &readfds))  
          {  
              std::cout << "TEST1" << std::endl; 
              if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)  
              {  
                  perror("accept");  
                  exit(EXIT_FAILURE);  
              } 
              std::cout << "TEST2" << std::endl;
               
              printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));  
              puts("Welcome message sent successfully");  
              
              
              clients.push_back(new_socket);
              
              printf("Adding to list of sockets as %d\n" , new_socket);
              std::thread([this, new_socket] 
              {
                 logic->createNewSesion(new_socket);  
              }).detach();

          }  
          usleep(info.sleepInterval);
      }  
   }
   //-----------------------------------------------------------------------------
   void TSocket::sendPackage(int sock, TMessage *message)
   {
      int valsend = send(sock, message, sizeof(TMessage), 0);
   }
   //-----------------------------------------------------------------------------
   bool TSocket::recvMessage(int sock, TMessage *message)
   {
      int valread = recv(sock, message, sizeof(TMessage), 0); 
      
      return valread;  
   }
   //-----------------------------------------------------------------------------
   void TSocket::closeConnection(int dicr)
   {
      std::remove_if(clients.begin(), clients.end(), [dicr](int num) {
        return num == dicr;
      });
      close(dicr); 
   }
}
