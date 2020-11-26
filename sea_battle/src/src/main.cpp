
#include "controller.h"
#include <QApplication>

int main(int argc, char** argv)
{
    /*QApplication app(argc, argv);
    sea_battle sea_battle;
    sea_battle.show()
    return app.exec();*/
    
    QApplication a(argc, argv); 
    Controller controller;
    controller.start();
    
    return a.exec();
}
