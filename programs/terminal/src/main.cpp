
#include "tmainwindow.h"
#include <QApplication>

int main(int argc, char** argv)
{
   QApplication a(argc, argv);
   TMainWindow program; 
   program.show();
   return a.exec(); 
}
