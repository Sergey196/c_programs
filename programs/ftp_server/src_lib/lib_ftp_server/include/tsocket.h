#ifndef TSOCKET_H
#define TSOCKET_H

#include "lib_ftp_constants.h"
#include <arpa/inet.h>  
#include <vector>
#include <fstream>

namespace _ftp_server
{ 
   class TLogic;
   class TSocket
   {
      public:
          TSocket(TConfig info, TLogic *logic);
          void start();
          void sendPackage(int sock, TMessage *message);
          bool recvMessage(int sock, TMessage *message);
          void closeConnection(int dicr);
      private:
          TConfig info;
          TLogic *logic;
          std::vector<int> clients;
          struct sockaddr_in address; 
          int master_socket;
          fd_set readfds;
   };
};

#endif // TSOCKET_H
