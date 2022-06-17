
#include <QApplication>
#include "tcontroller.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv); 
    TController controller;
    controller.start();
    return a.exec();
}
