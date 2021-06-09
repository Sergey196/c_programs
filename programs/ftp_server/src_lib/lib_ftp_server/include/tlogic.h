#ifndef TLOGIC_H
#define TLOGIC_H

#include <fstream>
#include "lib_ftp_constants.h"

namespace _ftp_server
{ 
   class TSocket; 
   class TLogic
   {
   public:
       TLogic(TConfig _info);
       void start();
       void createNewSesion(int sock);
   private:
       void startLoudFile(char *command);
       void sendData();
       void endSesion();
       TSocket *socket;
   };
}

#endif // TLOGIC_H
