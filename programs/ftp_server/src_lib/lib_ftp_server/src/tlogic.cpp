#include "tlogic.h"
#include "tsocket.h"
#include "unistd.h"
#include <cstring>
#include <iostream>

namespace _ftp_server
{ 
   thread_local static std::ifstream file;
   thread_local static int socketDiscr = 0;

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
   void TLogic::createNewSesion(int sock)
   {
      socketDiscr = sock;
      while(true)  
      {
         TMessage message;
         int result = socket->recvMessage(socketDiscr, &message); 
         
         if(result == -1)
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
         usleep(100);
      }
   }
   //-----------------------------------------------------------------------------
   void TLogic::startLoudFile(char *command)
   {
      std::cout << "TEST startLoudFile" << std::endl; 
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
      }
      socket->sendPackage(socketDiscr, &message);
   }
   //-----------------------------------------------------------------------------
   void TLogic::endSesion()
   {
      std::cout << "TEST endSesion" << std::endl;  
      socket->closeConnection(socketDiscr); 
   }
}
