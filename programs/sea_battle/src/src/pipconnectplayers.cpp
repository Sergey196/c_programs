#include "pipconnectplayers.h"
#include <thread>
#include <sys/msg.h>

//#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>
#include <string.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>

//#include <sys/types.h>
//#include <errno.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include "controller.h"


#define MSGKEY	100

struct  mymsg
{
   long  mtype;
   _baseitem::messageType typeMessage;
   char data[100];
};
//---------------------------------------------------------------------------
PipConnectPlayers::~PipConnectPlayers()
{
   msgctl(mq, 0, NULL);
}
//---------------------------------------------------------------------------
void PipConnectPlayers::start(int _idRunProgramm, int _idAnotherPlaer)
{
    idRunProgramm = _idRunProgramm;
    idAnotherPlaer = _idAnotherPlaer;

    mq = msgget(MSGKEY, 0644 | IPC_CREAT);
    fd = open("/dev/tty", O_RDWR | O_NONBLOCK | O_CLOEXEC | O_NOCTTY);
    
    std::thread([=]
    {
       while(true)
       {
          mymsg response;
          msgrcv(mq, &response, sizeof(mymsg), idRunProgramm, 0);

          controller->messageResponse(std::string(response.data), response.typeMessage);
       }
    }).detach();
}
//---------------------------------------------------------------------------
void PipConnectPlayers::sendMessage(std::string request, _baseitem::messageType type)
{
   mymsg response;
   response.mtype = idAnotherPlaer;
   response.typeMessage = type;
   strcpy(response.data, request.c_str());

   msgsnd(mq, &response, sizeof(mymsg), 0);
}
