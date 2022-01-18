
#include <QApplication>
#include "tcontroller.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv); 
    TController controller;
    controller.startGui();
    return a.exec();
}
