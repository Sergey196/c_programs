#include "tmaneger.h"
#include "tmessageprocess.h"
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <thread>
#include <ctime>
#include <iostream>
#include <algorithm>

namespace _protocol
{
   TManeger::TManeger(LibProtocolSettings _settings)
   {
      settings = _settings;
      messageProcess = std::make_shared<TMessageProcess>(settings.socetSettings);
   }
   //-----------------------------------------------------------------------------
   void TManeger::start()
   {
      messageProcess->initSocket();
      std::thread([this]
      {
         while(true)
         {
            messageHeartBeatProcess();
            sleep(settings.periodHardBeart);
         }
      }).detach(); 
      
      std::thread([this]
      {
         while(true)
         {
            messageResponseProcess();
            sleep(settings.perioProcessMessages);
         }
      }).detach(); 

      std::thread([this]
      {
         while(true)
         {
            chechHeartBeatTimeoutProcess();
            sleep(settings.perioProcessMessages);
         }
      }).detach();
   }
   //-----------------------------------------------------------------------------
   void TManeger::messageRequest(void *message, int size)
   {
      TMessage *mesToSend = new TMessage;
      mesToSend->typeMessage = messageSimple;
      memcpy(mesToSend->data, message, size);
      std::thread([this, mesToSend] 
      { 
         while(true) 
         {
            if(messageProcess->messageRequest(mesToSend))
            {
               delete mesToSend; 
               break; 
            }
         }
      }).detach();
   }
   //-----------------------------------------------------------------------------
   void TManeger::messageResponseProcess()
   {
      std::thread([this] 
      {  
         TMessage message;
         if(messageProcess->messageResponse(message))
         {
            if(message.typeMessage == messageHeartBeat)
            {
               coutTimeoutHeartBeat = 0;
            }
            else if(message.typeMessage == messageSimple)
            {
               settings.messageResponseIface.lock()->messageResponse(message);
            }
         }
         else
         {
            std::cout << "TEST No Mesasage" << std::endl;
         }
      }).detach();
   }
   //-----------------------------------------------------------------------------
   void TManeger::messageHeartBeatProcess()
   {
       TMessage *mesToSend = new TMessage;
       messageProcess->messageRequest(mesToSend);
       delete mesToSend;
   }
   //-----------------------------------------------------------------------------
   void TManeger::chechHeartBeatTimeoutProcess()
   {
       if(coutTimeoutHeartBeat < timeoutHeartBeatMaxCout)
       {
          coutTimeoutHeartBeat++;
       }
       else
       {
          settings.messageResponseIface.lock()->heartBeatState(false);
       }
   }
}
