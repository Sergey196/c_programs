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
         void messageHeartBeatProcess();
         void chechHeartBeatTimeoutProcess();

         LibProtocolSettings settings;
         std::shared_ptr<TMessageProcess> messageProcess;
         bool heartBetaFlag { false };
         int coutTimeoutHeartBeat { 0 };
   };
}

#endif // TMANEGER_H
