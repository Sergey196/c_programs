#ifndef TMANEGER_H
#define TMANEGER_H

namespace _protocol
{
   struct LibProtocolSettings
   {
      int port { 8080 };       
   };
    
    
   class TManeger
   {
      public:
         TManeger(LibProtocolSettings settings);
         void start();
      private:
         LibProtocolSettings settings;
   };
   
   
   class TProtocolMesIface
   {
      public: 
          virtual void messageRequest(void *mes) = 0; 
          virtual void messageResponse(void *mes) = 0;
          virtual void hardBeatResponse() = 0;
   };
}

#endif // TMANEGER_H
