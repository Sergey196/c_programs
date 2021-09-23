#include "tlogic.h"
#include "tsocket.h"
#include "unistd.h"
#include <cstring>
#include <iostream>

namespace _ftp_server
{ 
   thread_local static std::ifstream file;

   //-----------------------------------------------------------------------------
   TLogic::TLogic(TConfig _info)
   {
      socket = new TSocket(_info, this);
   }
   //-----------------------------------------------------------------------------
   void TLogic::start()
   {
      socket->start(); 
   }
   //-----------------------------------------------------------------------------
   void TLogic::createNewSesion()
   {
      while(true)  
      {
         TMessage message;
         int result = socket->recvMessage(&message); 
         
         std::cout << "TEST1 = " << message.command << std::endl;
         std::cout << "TEST2 = " << result << std::endl;
         
         if(result < 1)
         {
            continue;  
         }
         
         switch(message.command) 
         {
            case commandStart:
            {
               startLoudFile(message.data);
               break; 
            }
            case commandData:
            {
               sendData(); 
               break; 
            }
            case commandEnd:
            {
               endSesion(); 
               return;
            }
         }
         usleep(1000);
      }
   }
   //-----------------------------------------------------------------------------
   void TLogic::startLoudFile(char *command)
   {
      std::cout << "TEST startLoudFile = " << command << std::endl; 
      file.open(command, std::ios::binary );
      
      if(file.fail())
      {
         endSesion(); 
      }
   }
   //-----------------------------------------------------------------------------
   void TLogic::sendData()
   {
      std::cout << "TEST sendData" << std::endl; 
      //char buffer[messageSize];
      TMessage message; 
      message.command = commandData;
      memset(message.data, 0, sizeof(message.data));
      if(!file.eof())
      {
         file.read(message.data, sizeof(message.data));
      }
      else
      {
         message.command = commandEnd; 
         file.close();
         std::cout << "TEST endFile" << std::endl;
      }
      socket->sendPackage(&message);
   }
   //-----------------------------------------------------------------------------
   void TLogic::endSesion()
   {
      std::cout << "TEST endSesion" << std::endl;  
      socket->closeConnection(); 
   }
}
