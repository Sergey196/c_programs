
#include "controller.h"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication a(argc, argv); 
    Controller controller;

    if(argc < 3)
    {
       return 0;
    }

    controller.start(atoi(argv[1]), atoi(argv[2]));
    
    return a.exec();
}
