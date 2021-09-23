#ifndef TSOCKET_H
#define TSOCKET_H

#include "lib_ftp_constants.h"
#include <arpa/inet.h>  
#include <vector>
#include <fstream>
#include <openssl/ssl.h>

namespace _ftp_server
{ 
   class TLogic;
   class TSocket
   {
      public:
          TSocket(TConfig info, TLogic *logic);
          ~TSocket();
          void start();
          void sendPackage(TMessage *message);
          int recvMessage(TMessage *message);
          void closeConnection();
      private:
          void init_openssl();
          void create_socket(int port);
          void cleanup_openssl();
          void create_context();
          void configure_context();
          
          TConfig info;
          TLogic *logic;
          //std::vector<int> clients;
          struct sockaddr_in address; 
          int master_socket;
          fd_set readfds;
          SSL_CTX *ctxSSL;
   };
};

#endif // TSOCKET_H
