

#include "maingui.h"
#include "controller.h"
#include <iostream>
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPushButton>

MainGui::MainGui(Controller *_controller)
{
   setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
   setGeometry(0, 0, 1601, 1000);
   controller = _controller;
   
   QPushButton *restartBtn = new QPushButton("Переиграть", this);
   restartBtn->setFixedSize(QSize(110, 50));
   restartBtn->setGeometry(100, 685, 110, 50);
   restartBtn->show();
   connect(restartBtn, &QPushButton::released, [this]() {
      controller->reloadToDefault();
   });
}
//---------------------------------------------------------------------------
void MainGui::reloadToDefaultGui()
{
    xpos = -1;
    ypos = -1;
    reservShipChangeFlag = false;
    verticalOrHorisontal = true;
}
//---------------------------------------------------------------------------
void MainGui::start()
{
   show();
}
//---------------------------------------------------------------------------
void MainGui::paintEvent(QPaintEvent *)
{
   paintField();
   paintEnemyField();
   paintFieldState();
   paintReservShip();
}
//---------------------------------------------------------------------------
void MainGui::paintField()
{
   int i = 0;
   int j = 0; 

   QPainter painter(this);

   auto drawWaterField = [&]() {
       painter.setBrush(Qt::blue);
       painter.drawRect((i + 2) * _baseitem::CELL_WIDTH_HIIGHT, (j + 2) * _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT);
   };

   painter.setFont(QFont("times",22));
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 2, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "А");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 3, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Б");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 4, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "В");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 5, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Г");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 6, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Д");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 7, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Е");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 8, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Ж");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 9, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "З");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 10, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "И");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 11, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "К");

   for(int i = 0; i < _baseitem::COUT_ROWS_COLUMS; i++)
   {
      painter.drawText(_baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT * (i + 2), _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, QString::number(i));
   }

   for(i = 0; i < _baseitem::COUT_ROWS_COLUMS; i++)
   {
      for(j = 0; j < _baseitem::COUT_ROWS_COLUMS; j++)
      {
          drawWaterField();
      }
   }
   
   painter.setBrush(Qt::transparent);
   painter.drawRect(_baseitem::SHIP_RESERV_PANEl_X0, _baseitem::SHIP_RESERV_PANEl_Y0, _baseitem::SHIP_RESERV_PANEl_WIDTH, _baseitem::SHIP_RESERV_PANEl_HEIGHT);
}
//---------------------------------------------------------------------------
void MainGui::paintEnemyField()
{
   QPainter painter(this);
   
   painter.setFont(QFont("times",22));
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 14, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "А");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 15, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Б");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 16, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "В");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 17, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Г");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 18, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Д");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 19, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Е");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 20, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "Ж");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 21, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "З");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 22, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "И");
   painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 23, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, "К");
   
   for(int i = 0; i < _baseitem::COUT_ROWS_COLUMS; i++)
   {
      painter.drawText(_baseitem::CELL_WIDTH_HIIGHT * 13, _baseitem::CELL_WIDTH_HIIGHT * (i + 2), _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT, Qt::AlignCenter, QString::number(i));
   }
}
//---------------------------------------------------------------------------
void MainGui::paintReservShip()
{
   QPainter painter(this); 
   painter.setBrush(Qt::black); 
   
   int coutCellFreeShip = controller->getCoutCellsFreeShip();
   if(coutCellFreeShip != -1)
   {
      painter.drawRect(((_baseitem::SHIP_RESERV_PANEl_X1 - _baseitem::SHIP_RESERV_PANEl_X0 - (_baseitem::CELL_WIDTH_HIIGHT * coutCellFreeShip))/2) + _baseitem::SHIP_RESERV_PANEl_X0, _baseitem::SHIP_RESERV_PANEl_Y0 + 15, _baseitem::CELL_WIDTH_HIIGHT * coutCellFreeShip, _baseitem::CELL_WIDTH_HIIGHT);
   }
   
   if(reservShipChangeFlag)
   {
      if(verticalOrHorisontal)
      {
        painter.drawRect(xpos, ypos, _baseitem::CELL_WIDTH_HIIGHT * coutCellFreeShip, _baseitem::CELL_WIDTH_HIIGHT);
      }
      else
      {
         painter.drawRect(xpos, ypos, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT * coutCellFreeShip);
      }
   }
   
}
//---------------------------------------------------------------------------
void MainGui::paintFieldState()
{
    int i = 0;
    int j = 0;  
    QPainter painter(this); 
    
   auto fieldPainter = [&](int typePlayer, _baseitem::cellState cellStatus) {
       int x0 = -1;
       int y0 = -1;

       if(typePlayer == _baseitem::PLAYER_INDEX)
       {
          x0 = (i + 2) * _baseitem::CELL_WIDTH_HIIGHT;
          y0 = (j + 2) * _baseitem::CELL_WIDTH_HIIGHT;
       }
       else if(typePlayer == _baseitem::ENEMY_INDEX)
       {
           x0 = (i + 14) * _baseitem::CELL_WIDTH_HIIGHT;
           y0 = (j + 2) * _baseitem::CELL_WIDTH_HIIGHT;
       }

       if(cellStatus == _baseitem::free_normal || cellStatus == _baseitem::enemy_ship_normal)
       {
          painter.setBrush(Qt::blue);
          painter.drawRect(x0, y0, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT);
       }
       else if(cellStatus == _baseitem::free_beat)
       {
           painter.setBrush(Qt::blue);
           painter.drawRect(x0, y0, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT);
           painter.setBrush(Qt::red);
           painter.drawEllipse(QPointF(x0 + (_baseitem::CELL_WIDTH_HIIGHT/2), y0 + (_baseitem::CELL_WIDTH_HIIGHT/2)), _baseitem::CELL_WIDTH_HIIGHT/2, _baseitem::CELL_WIDTH_HIIGHT/2);
       }
       else if(cellStatus == _baseitem::ship_normal)
       {
           painter.setBrush(Qt::black);
           painter.drawRect(x0, y0, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT);
       }
       else if(cellStatus == _baseitem::ship_beat)
       {
           painter.setBrush(Qt::black);
           painter.drawRect(x0, y0, _baseitem::CELL_WIDTH_HIIGHT, _baseitem::CELL_WIDTH_HIIGHT);
           painter.setBrush(Qt::red);
           painter.drawEllipse(QPointF(x0 + (_baseitem::CELL_WIDTH_HIIGHT/2), y0 + (_baseitem::CELL_WIDTH_HIIGHT/2)), _baseitem::CELL_WIDTH_HIIGHT/2, _baseitem::CELL_WIDTH_HIIGHT/2);
       }
   };
    

    for(i = 0; i < _baseitem::COUT_ROWS_COLUMS; i++)
    {
       for(j = 0; j < _baseitem::COUT_ROWS_COLUMS; j++)
       {
          fieldPainter(_baseitem::PLAYER_INDEX, controller->getCellStatus(_baseitem::PLAYER_INDEX, i, j));
          fieldPainter(_baseitem::ENEMY_INDEX, controller->getCellStatus(_baseitem::ENEMY_INDEX, i, j));
       }
    }
}
//---------------------------------------------------------------------------
void MainGui::mousePressEvent( QMouseEvent* event)
{
   if(event->button() == Qt::LeftButton && !reservShipChangeFlag)
   {
      return;
   }

   QPoint posMouse = event->pos();

   if(((posMouse.x() >= _baseitem::SHIP_RESERV_PANEl_X0) && (posMouse.x() <= _baseitem::SHIP_RESERV_PANEl_X1)) && ((posMouse.y() >= _baseitem::SHIP_RESERV_PANEl_Y0) && (posMouse.y() <= _baseitem::SHIP_RESERV_PANEl_Y1)) && controller->getCoutCellsFreeShip() != -1)
   {
      reservShipChangeFlag = true;
      xpos = posMouse.x();
      ypos = posMouse.y();
      repaint();
   }
};
//---------------------------------------------------------------------------
void MainGui::mouseReleaseEvent(QMouseEvent *event) 
{
   if(reservShipChangeFlag)
   {
      if(event->button() == Qt::LeftButton)
      {
         verticalOrHorisontal = !verticalOrHorisontal;
      }
      else
      {
          reservShipChangeFlag = false;

          controller->addNewShip(((int)xpos/_baseitem::CELL_WIDTH_HIIGHT) - 2, ((int)ypos/_baseitem::CELL_WIDTH_HIIGHT) - 2, controller->getCoutCellsFreeShip(), verticalOrHorisontal);
          xpos = -1;
          ypos = -1;
          verticalOrHorisontal = true;
      }
      repaint();
   }
   else
   {
      controller->cellAtacker(((int)event->pos().x()/_baseitem::CELL_WIDTH_HIIGHT) - 14, ((int)event->pos().y()/_baseitem::CELL_WIDTH_HIIGHT) - 2);
   }
}
//---------------------------------------------------------------------------
void MainGui::mouseMoveEvent(QMouseEvent *event)
{
   if(reservShipChangeFlag)
   {
      xpos = event->pos().x();
      ypos = event->pos().y();
      repaint();  
   }
}
