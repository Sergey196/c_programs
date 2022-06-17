#include "tmessageprocess.h"

#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>

namespace _protocol
{
   void TMessageProcess::initSocket()
   {
      struct sockaddr_in sockddr; 
      sockfd = socket(AF_INET, SOCK_DGRAM, 0);
      
      memset(&sockddr, 0, sizeof(sockddr)); 
      sockddr.sin_family = AF_INET; 
      sockddr.sin_port = htons(settings.port); 
      sockddr.sin_addr.s_addr = INADDR_ANY; 
      
      if(settings.isServer)
      {
         struct sockaddr_in cliaddr; 
         memset(&cliaddr, 0, sizeof(cliaddr)); 
         
         bind(sockfd, (const struct sockaddr *)&sockddr, sizeof(sockddr));
         
         sendAdr = cliaddr;
      }
      else
      {
         sendAdr = sockddr; 
      }
   }
   //-----------------------------------------------------------------------------
   TMessageProcess::~TMessageProcess()
   {
      close(sockfd);
   }
   //-----------------------------------------------------------------------------
   void TMessageProcess::closeSocket()
   {
      close(sockfd);
   }
   //-----------------------------------------------------------------------------
   void TMessageProcess::messageRequest(TMessage &message)
   {
      sendto(sockfd, &message, sizeof(TMessage),  MSG_CONFIRM, (const struct sockaddr *) &sendAdr, sizeof(sockaddr));
   }
   //-----------------------------------------------------------------------------
   bool TMessageProcess::messageResponse(TMessage &message)
   {
      socklen_t len = sizeof(sockaddr);
      int size = recvfrom(sockfd, &message, sizeof(TMessage),  MSG_DONTWAIT, (struct sockaddr *) &sendAdr, &len);
      return size > 0;
   }
}
