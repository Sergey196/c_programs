#include "tserveriface.h"
#include "tlogic.h"

namespace _ftp_server
{ 
   TServerIface::TServerIface()
   {
   
   }
   //-----------------------------------------------------------------------------
   void TServerIface::init(TConfig _info)
   {
      logic = new TLogic(_info); 
   }
   //-----------------------------------------------------------------------------
   void TServerIface::start()
   {
      logic->start();  
   }
}
