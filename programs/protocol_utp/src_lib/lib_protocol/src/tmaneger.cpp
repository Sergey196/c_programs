#include "tmaneger.h"
#include "tmessageprocess.h"
#include <unistd.h>
#include <cstring>
#include <thread>
#include <ctime>
#include <iostream>

namespace _protocol
{
   TManeger::TManeger(LibProtocolSettings _settings)
   {
      settings = _settings;
      messageProcess = new TMessageProcess(settings.socetSettings);
      pthread_mutex_init (&messMutex, NULL);
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
            checkMessagesProcess();
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
      if(numberMessage >= messageCout)
      {
         numberMessage = 0;
         clearMessagesState(messageCout/2, messageCout);
      } 
      else if((numberMessage > messageCout/2) && (numberMessage < messageCout))
      {
         clearMessagesState(0, messageCout/2); 
      }
      
      TMessage mesToSend;
      mesToSend.idMessage = numberMessage;
      mesToSend.time = time(0);
      mesToSend.typeMessage = messagePequest;
      //memcpy(mesToSend.data, message, messageSize);
      memcpy(mesToSend.data, message, size);

      messageProcess->messageRequest(mesToSend);
      pthread_mutex_lock (&messMutex);
      listOfMess.push_back(mesToSend);
      pthread_mutex_unlock (&messMutex); 
      isMessageSend[mesToSend.idMessage] = false;

      numberMessage++;
   }
   //-----------------------------------------------------------------------------
   void TManeger::messageResponseProcess()
   {
      TMessage message;
      if(messageProcess->messageResponse(message))
      {
         if(message.typeMessage == messageHeartBeat)
         {
            coutTimeoutHeartBeat = 0;
         }
         else if(message.typeMessage == messageConfirmation)
         {
            if(!isMessageSend[message.idMessage])
            {
               isMessageSend[message.idMessage] = true;
            }
         }
         else if(message.typeMessage == messagePequest)
         {
            settings.messageResponseIface.lock()->messageResponse(message);
            TMessage messageConf;
            messageConf.idMessage = message.idMessage;
            messageConf.typeMessage = messageConfirmation;
            messageProcess->messageRequest(messageConf);
         }
      }
      else
      {
         std::cout << "TEST No Mesasage" << std::endl;
      }
   }
   //-----------------------------------------------------------------------------
   void TManeger::checkMessagesProcess()
   {
       std::time_t currentTime = time(0);
       pthread_mutex_lock (&messMutex);
       for(auto ptr = listOfMess.begin(); ptr < listOfMess.end(); ptr++)
       {
           TMessage massage = *ptr;
           if (isMessageSend[massage.idMessage])
           {
              listOfMess.erase(ptr);
           }

           if(currentTime - massage.time >= messageTimeout)
           {
              messageProcess->messageRequest(massage);
           }
       };
       pthread_mutex_unlock (&messMutex);        
   }
   //-----------------------------------------------------------------------------
   void TManeger::messageHeartBeatProcess()
   {
       TMessage mesToSend;
       messageProcess->messageRequest(mesToSend);
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
   //-----------------------------------------------------------------------------
   void TManeger::clearMessagesState(int beginIndex, int endIndex)
   {
      for(int i = beginIndex; i < endIndex; i++)
      {
          isMessageSend[i] = true;
      }
   }
}
