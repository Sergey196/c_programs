#ifndef TDEFINES_LIB_INTEGRITY_CONSTANTS_H
#define TDEFINES_LIB_INTEGRITY_CONSTANTS_H 1

#include <memory>
#include <ctime>

namespace _ftp_server
{          
   enum commands
   {
      commandStart,        
      commandData,
      commandEnd
   };
   //-----------------------------------------------------------------------------
   const int messageSize = 512;  
   //----------------------------------------------------------------------------- 
   
   //----------------------------------------------------------------------------- 
   struct TMessage
   {
      commands command;
      char data[messageSize] { 0 };
   };
   //-----------------------------------------------------------------------------
   struct TConfig
   {
      int port { 8080 }; 
      int sleepInterval { 2000 };
   };
}

#endif
