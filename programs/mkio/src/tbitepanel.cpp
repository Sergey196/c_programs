#include <iostream>
#include "tbitepanel.h"
#include "tcontroller.h"

TBitePanel::TBitePanel(int _position, QWidget *parent):QLabel(parent) 
{ 
    position = _position; 
    pointOnController = TController::getInstance();
    setText("0");
}
//---------------------------------------------------------------------------
void TBitePanel::mouseDoubleClickEvent(QMouseEvent *event)
{
   (void)event; 
   pointOnController->clickBitePanel(position); 
   emit pointOnController->update();
}
