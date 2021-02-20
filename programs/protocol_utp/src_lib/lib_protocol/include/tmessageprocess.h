#ifndef TMESSAGEPROCESS_H
#define TMESSAGEPROCESS_H

namespace _protocol
{
   struct LibProtocolSocketSettings
   {
      int periodHardBeart { 1000 };      
      int perioProcessMessages { 1000 };
      LibProtocolSettings socetSettings;
   };

   class TMessageProcess
   {
      public:
         TMessageProcess();
   };
}

#endif // TMESSAGEPROCESS_H
