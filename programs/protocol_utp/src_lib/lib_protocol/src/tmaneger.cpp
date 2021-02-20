#include "tmaneger.h"
#include <unistd.h>
#include <thread>

namespace _protocol
{
   TManeger::TManeger(LibProtocolSettings _settings)
   {
      settings = _settings;
   }
   //-----------------------------------------------------------------------------
   void TManeger::start()
   {
      std::thread([&]
      {
         while(true)
         {
            sleep(settings.periodHardBeart);
         }
      }).detach(); 
      
      std::thread([&]
      {
         while(true)
         {
            sleep(settings.perioProcessMessages);
         }
      }).detach(); 
   }
}
