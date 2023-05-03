#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

class Controler;

class Gui : public QMainWindow
{
   public:
      Gui(Controler *_pointControler);
      ~Gui();
   private:   
      void repaint(); 
      void keyPress(int key);
      Controler *pointControler;
      bool stopFlag { false };
};

#endif // GUI_H
