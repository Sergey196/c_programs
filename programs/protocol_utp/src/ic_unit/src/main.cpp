
#include <iostream>
#include <cstring>
#include <memory> 
#include <unistd.h>
#include "tmaneger.h"
#include "lib_protocol_constants.h"

class Data
{
   public:
      int a { 0 };  
      int b { 1 };
};

class TMessageResponseIfaceClass : public _protocol::TMessageResponseIface
{
   void messageResponse(_protocol::TMessage message)
   {
      Data data; 
      memcpy(&data, message.data, _protocol::messageSize); 
      std::cout << "TEST messageResponse a = " << data.a<< std::endl;
      std::cout << "TEST messageResponse b = " << data.b << std::endl;
   }
   void heartBeatState(bool state)
   {
      std::cout << "TEST heartBeatState = " << state << std::endl;  
   }
};



int main(int argc, char const *argv[]) 
{
    if(argc < 2)
    {
       return 0; 
    }
    
   std::shared_ptr<TMessageResponseIfaceClass> ifaceProtocolProcess = std::make_shared<TMessageResponseIfaceClass>();
   _protocol::LibProtocolSettings settings; 
   settings.messageResponseIface = ifaceProtocolProcess;
   settings.socetSettings.isServer = atoi(argv[1]);
   std::cout << "TEST server = " << settings.socetSettings.isServer << std::endl;   
   
   _protocol::TManeger maneger(settings);
   maneger.start();
   
   
   while(true)
   {
      sleep(1);
      if(settings.socetSettings.isServer)
      {
         Data data;
         data.a = 10;
         data.b = 20;
         maneger.messageRequest(&data, sizeof(Data));
      }
      else
      {
         Data data;
         data.a = 40;
         data.b = 50;
         maneger.messageRequest(&data, sizeof(Data));
      }
   }
   
   return 0; 
}
