#ifndef PIPCONNECTPLAYERS_H
#define PIPCONNECTPLAYERS_H

#include <string>
#include <constants.h>

class Controller;

class PipConnectPlayers
{
public:
    PipConnectPlayers(Controller *_controller) { controller = _controller; }
    ~PipConnectPlayers();
    
    void start(int _idRunProgramm, int _idAnotherPlaer);

    void sendMessage(std::string request, _baseitem::messageType type);
private:
    Controller *controller; 
    int mq;
    int fd;
    int idRunProgramm;
    int idAnotherPlaer;
};

#endif // PIPCONNECTPLAYERS_H
