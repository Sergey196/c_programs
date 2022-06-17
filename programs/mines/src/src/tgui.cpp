/*
 * Copyright 2021 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tgui.h"
#include "tcontroller.h"
#include <QGuiApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QFrame>
#include <QToolBar>
#include <QVBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>

TGui::TGui(TController *_pointOnControler)
{
    pointOnControler = _pointOnControler;
    QRect screenGeometry = QGuiApplication::screens().at(0)->geometry();
    int x = (screenGeometry.width() - WIDTH) / 2;
    int y = (screenGeometry.height() - HEIGHT) / 2;
    setGeometry(x, y, WIDTH, HEIGHT);
    
    QFrame *mainfr = new QFrame();
    QFrame *drawfr = new QFrame();
    QVBoxLayout *mainLay = new QVBoxLayout(mainfr);
    setCentralWidget(mainfr);
    
    QToolBar* ptb = new QToolBar("Linker ToolBar");
    ptb->addAction("Старт", this, [this]() {
       startGameFlag = true; 
       pointOnControler->startGame(); 
       repaint();
    });
    ptb->addAction("Выход", this, [this]() {
       close(); 
    });
    
    mainLay->addWidget(ptb);
    mainLay->addWidget(drawfr);
    
    ptb->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    drawfr->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
//---------------------------------------------------------------------------
void TGui::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setFont(QFont("times", 18));
   
   auto printField = [&painter](CellInfo info) {
       if(info.state.value == NONE) {
          painter.setBrush(Qt::gray);  
       } else if(info.state.value == MINE_NONE) {
          painter.setBrush(Qt::gray);    
       } else if(info.state.value == FREE) {
          painter.setBrush(Qt::white);  
       } else if(info.state.value == MINE_BOM) {
           painter.setBrush(Qt::red);   
       }
       
       painter.drawRect((info.x + 2) * FIELD_SIZE, (info.y + 2) * FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);  
       painter.drawText((info.x + 2) * FIELD_SIZE, (info.y + 2) * FIELD_SIZE, FIELD_SIZE, FIELD_SIZE, Qt::AlignCenter, ((info.state.coutMines > 0) && (info.state.value == FREE)) ? QString::number(info.state.coutMines) : "");
   };
   
   for(int i = 0; i < COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         printField(CellInfo { i, j, pointOnControler->getCellValue(i, j) });
      }
   }
}
//---------------------------------------------------------------------------
void TGui::mousePressEvent(QMouseEvent* event)
{
   if((event->button() != Qt::RightButton) || !startGameFlag)
   {
      return;
   }
   
   QPoint posMouse = event->pos();
   
   if(((posMouse.x() >= PANEl_X0) && (posMouse.x() <= PANEl_X1)) && ((posMouse.y() >= PANEl_Y0) && (posMouse.y() <= PANEl_Y1)))
   {
      int x = (event->pos().x()/FIELD_SIZE) - 2;
      int y = (event->pos().y()/FIELD_SIZE) - 2;
      pointOnControler->selectCell(x, y);
      repaint();
   }
}
//---------------------------------------------------------------------------
void TGui::gameStatus(bool status)
{
   startGameFlag = false; 
   std::cout << "TEST = " << status << std::endl;
}
