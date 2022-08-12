#ifndef TDEFINES_LIB_INTEGRITY_CONSTANTS_H
#define TDEFINES_LIB_INTEGRITY_CONSTANTS_H 1

#include <memory>
#include <ctime>

namespace _protocol
{          
   enum messageType
   {
      messageSimple,         
      messageHeartBeat
   };

   const int messageSize = 10000;  
   const int messageCout = 1000; 
   const int messageTimeout = 1;
   const int timeoutHeartBeatMaxCout = 10;
    
   struct TMessage
   {
      _protocol::messageType typeMessage { messageHeartBeat };
      char data[_protocol::messageSize] { 0 };
   };

   struct TSocetSettings
   {
      int port { 8080 };
      bool isServer { false };
   };
// 
   class TMessageResponseIface
   {
      public:
         virtual void messageResponse(TMessage message) = 0;
         virtual void heartBeatState(bool state) = 0;
   };
   
   struct LibProtocolSettings
   {
      int periodHardBeart { 1 };      
      int perioProcessMessages { 1 };
      TSocetSettings socetSettings;
      std::weak_ptr<TMessageResponseIface> messageResponseIface;
   };

}

#endif
