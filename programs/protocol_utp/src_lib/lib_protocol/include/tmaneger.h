#ifndef TMANEGER_H
#define TMANEGER_H

#include <vector>
#include <memory>
#include <stdlib.h>
#include "lib_protocol_constants.h"

namespace _protocol
{
   class TMessageProcess;
   
   class TManeger
   {
      public:
         TManeger(LibProtocolSettings settings);
         void start();
         void messageRequest(void *message, int size);

      private:
         void messageResponseProcess();
         void checkMessagesProcess();
         void messageHeartBeatProcess();
         void chechHeartBeatTimeoutProcess();
         void clearMessagesState(int beginIndex, int endIndex);

         LibProtocolSettings settings;
         std::shared_ptr<TMessageProcess> messageProcess;

         std::vector<TMessage> listOfMess;
         bool isMessageSend[_protocol::messageCout] { true };
         unsigned int numberMessage { 0 };
         bool heartBetaFlag { false };
         int coutTimeoutHeartBeat { 0 };
         pthread_mutex_t messMutex; 
   };
}

#endif // TMANEGER_H
