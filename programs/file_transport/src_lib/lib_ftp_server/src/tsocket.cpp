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
    
   thread_local static int socketDiscr = 0; 
   thread_local static SSL *ssl = nullptr;
   //-----------------------------------------------------------------------------
   TSocket::TSocket(TConfig _info, TLogic *_logic)
   {
      info = _info;
      logic = _logic;

      //init_openssl();
      create_context();
      configure_context();
      create_socket(info.port);
   }
   //-----------------------------------------------------------------------------
   TSocket::~TSocket()
   {
      SSL_CTX_free(ctxSSL);
      cleanup_openssl();
      close(master_socket); 
   }
   //-----------------------------------------------------------------------------
   void TSocket::init_openssl()
   { 
       SSL_load_error_strings();	
       OpenSSL_add_ssl_algorithms();
   }
   //-----------------------------------------------------------------------------
   void TSocket::create_socket(int port)
   {
       struct sockaddr_in addr;
   
       addr.sin_family = AF_INET;
       addr.sin_port = htons(port);
       //addr.sin_addr.s_addr = INADDR_ANY;  
       inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
   
       master_socket = socket(AF_INET, SOCK_STREAM, 0);
       if (master_socket < 0) 
       {
   	      perror("Unable to create socket");
   	      exit(EXIT_FAILURE);
       }
   
       if (bind(master_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
       {
   	      perror("Unable to bind");
   	      exit(EXIT_FAILURE);
       }
   
       if (listen(master_socket, 1) < 0) 
       {
   	      perror("Unable to listen");
   	      exit(EXIT_FAILURE);
       }
   }
   //-----------------------------------------------------------------------------
   void TSocket::cleanup_openssl()
   {
       EVP_cleanup();
   }
   //-----------------------------------------------------------------------------
   void TSocket::create_context()
   {
       const SSL_METHOD *method = DTLS_server_method();
       ctxSSL = SSL_CTX_new(method);
       if (!ctxSSL) 
       {
   	      perror("Unable to create SSL context");
   	      //ERR_print_errors_fp(stderr);
   	      exit(EXIT_FAILURE);
       }
   }
   //-----------------------------------------------------------------------------
   void TSocket::configure_context()
   {
       SSL_CTX_set_ecdh_auto(ctxSSL, 1);
   
       /* Set the key and cert */
       if (SSL_CTX_use_certificate_file(ctxSSL, "cert.pem", SSL_FILETYPE_PEM) <= 0) 
       {
           //ERR_print_errors_fp(stderr);
   	       exit(EXIT_FAILURE);
       }
   
       if (SSL_CTX_use_PrivateKey_file(ctxSSL, "key.pem", SSL_FILETYPE_PEM) <= 0 ) 
       {
           //ERR_print_errors_fp(stderr);
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
          //FD_ZERO(&readfds);  
       
          //FD_SET(master_socket, &readfds);  
          //FD_SET(STDIN_FILENO, &readfds);
          //max_sd = master_socket;  
              
          /*for(int sd : clients)
          {  
                   
              if(sd > 0) 
              {
                  FD_SET(sd , &readfds); 
              }
                   
              if(sd > max_sd)  
              {
                  max_sd = sd;  
              }
          }  
       
          int activity = select(max_sd + 1 , &readfds , NULL , NULL , NULL); 
         
          if ((activity < 0) && (errno != EINTR))  
          {  
              printf("select error");  
          }  */
             
              
          //if (FD_ISSET(master_socket, &readfds))  
          //{  
              std::cout << "TEST1" << std::endl; 
              new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
              if(new_socket < 0)  
              {  
                  perror("accept");  
                  exit(EXIT_FAILURE);  
              } 
              std::cout << "TEST2" << std::endl;
               
              printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));  
              puts("Welcome message sent successfully");  
              
              
              //clients.push_back(new_socket);
              
              printf("Adding to list of sockets as %d\n" , new_socket);
              std::thread([this, new_socket] 
              {
                 socketDiscr = new_socket;
                 std::cout << "TEST = " << socketDiscr << std::endl;
                 ssl = SSL_new(ctxSSL);
                 SSL_set_fd(ssl, socketDiscr);
                 if(SSL_accept(ssl) <= 0) 
                 {
                    std::cout << "TEST error" << std::endl;
                    return; 
                   //ERR_print_errors_fp(stderr);
                 }
                 logic->createNewSesion();  
              }).detach();

          //}  
          usleep(info.sleepInterval);
      }  
   }
   //-----------------------------------------------------------------------------
   void TSocket::sendPackage(TMessage *message)
   {
      //int valsend = send(sock, message, sizeof(TMessage), 0);
      SSL_write(ssl, message, sizeof(TMessage)); 
   }
   //-----------------------------------------------------------------------------
   int TSocket::recvMessage(TMessage *message)
   {
      //int valread = recv(sock, message, sizeof(TMessage), 0); 
      
      return SSL_read(ssl, message, sizeof(TMessage));
   }
   //-----------------------------------------------------------------------------
   void TSocket::closeConnection()
   {
      /*std::remove_if(clients.begin(), clients.end(), [](int num) {
        return num == socketDiscr;
      }); 
      SSL_shutdown(ssl);
      SSL_free(ssl);*/
      close(socketDiscr);
   }
}
