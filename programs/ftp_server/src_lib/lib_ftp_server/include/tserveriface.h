#ifndef TSERVERIFACE_H
#define TSERVERIFACE_H

#include "lib_ftp_constants.h"

namespace _ftp_server
{ 
   class TLogic; 
   class TServerIface
   {
      public:
          TServerIface();
          void init(TConfig info);
          void start();
      private:
          TLogic *logic;
   };
};

#endif // TSERVERIFACE_H
