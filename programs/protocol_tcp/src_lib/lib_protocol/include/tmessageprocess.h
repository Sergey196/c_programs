#ifndef TMESSAGEPROCESS_H
#define TMESSAGEPROCESS_H

#include "lib_protocol_constants.h"
#include <netinet/in.h> 

namespace _protocol
{
   class TMessageProcess
   {
      public: 
         TMessageProcess(TSocetSettings _settings) { settings = _settings; }
         ~TMessageProcess();
         void initSocket();
         void closeSocket();
         bool messageRequest(TMessage *message);
         bool messageResponse(TMessage &message);
      
      private:
         TSocetSettings settings; 
         int sockfd;
   };
}

#endif // TMESSAGEPROCESS_H
