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
#include <iostream>
#include <QGuiApplication>
#include <QScreen>
#include <QFrame>
#include <QVBoxLayout>
#include <QToolBar>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>

TGui::TGui(TController *_pointOnControler)
{
    pointOnControler = _pointOnControler;
    QRect screenGeometry = QGuiApplication::screens().at(0)->geometry();
    int x = (screenGeometry.width() - WIDTH) / 2;
    int y = (screenGeometry.height() - HEIGHT) / 2;
    setGeometry(x, y, WIDTH, HEIGHT);
    
    QFrame *mainfr = new QFrame();
    QWidget *drawPanel = new QWidget();
    QVBoxLayout *mainLay = new QVBoxLayout(mainfr);
    setCentralWidget(mainfr);
    
    QToolBar* ptb = new QToolBar("Linker ToolBar");
    ptb->addAction("Старт", this, [this]() {
       //pointOnControler->startGame(); 
    });
    ptb->addAction("Выход", this, [this]() {
       close(); 
    });
    
    mainLay->addWidget(ptb);
    mainLay->addWidget(drawPanel);
    
    ptb->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    drawPanel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
//---------------------------------------------------------------------------
void TGui::mousePressEvent(QMouseEvent *event)
{
   QPoint posMouse = event->pos();
   if((posMouse.x() >= MARGN + (FIELD_SIZE * 8)) || (posMouse.x() <= MARGN) || (posMouse.y() >= MARGN + (FIELD_SIZE * 8)) || (posMouse.y() <= MARGN))
   {
      return;
   } else {
      int x = (posMouse.x() - MARGN) / FIELD_SIZE;
      int y = (posMouse.y() - MARGN) / FIELD_SIZE;
      pointOnControler->cellClick(x, y);
      repaint();
   }
}
//---------------------------------------------------------------------------
void TGui::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setFont(QFont("times", 18));
   bool isWhiteBlack { true };
   
   auto printField = [&painter, this](CellInfo info) {
      if(pointOnControler->getCellEvent(info.coordinats.x, info.coordinats.y) == STEP) {
          painter.setBrush(Qt::cyan);    
      } else if(pointOnControler->getCellEvent(info.coordinats.x, info.coordinats.y) == ATTACK) {
          painter.setBrush(Qt::darkCyan);   
      }
      painter.drawRect((info.coordinats.x * FIELD_SIZE) + MARGN, (info.coordinats.y * FIELD_SIZE) + MARGN, FIELD_SIZE, FIELD_SIZE);  
      QPixmap pixmap;
      switch(info.value)
      {
         case FREE_VALUE: 
             break;
         case WHITE_PAWN: 
             pixmap.load(":/white_pawn");
             break;
         case WHITE_KNIGHT: 
             pixmap.load(":/white_knight");
             break;
         case WHITE_ROOK: 
            pixmap.load(":/white_rook");
            break;
         case WHITE_BISHOP: 
             pixmap.load(":/white_bishop");
             break;
         case WHITE_QUEEN: 
             pixmap.load(":/white_quen");
             break;
         case WHITE_KING: 
             pixmap.load(":/white_king");
             break;
         case BLACK_PAWN: 
             pixmap.load(":/black_pawn");
             break;
         case BLACK_KNIGHT: 
             pixmap.load(":/black_knight");
             break;
         case BLACK_ROOK: 
             pixmap.load(":/black_rook");
             break;
         case BLACK_BISHOP: 
             pixmap.load(":/black_bishop");
             break;
         case BLACK_QUEEN: 
             pixmap.load(":/black_quen");
             break;
         case BLACK_KING: 
             pixmap.load(":/black_king");
             break;
      }
      
      painter.drawPixmap((info.coordinats.x * FIELD_SIZE) + MARGN + 1, (info.coordinats.y * FIELD_SIZE) + MARGN + 1, FIELD_SIZE - 2, FIELD_SIZE - 2, pixmap);
   };
   
   auto paintcolor = [&painter, &isWhiteBlack]() {
      if(isWhiteBlack) {
         painter.setBrush(Qt::white);    
      } else {
         painter.setBrush(Qt::darkGray);    
      }
      isWhiteBlack = !isWhiteBlack;
   };
   
   for(int j = 0; j < COUT_ROWS_COLUMS; j++)
   {
      paintcolor();
      for(int i = 0; i < COUT_ROWS_COLUMS; i++)
      {
         paintcolor();
         printField(CellInfo { pointOnControler->getCellValue(i, j), CellCoordinats { i, j } });
      }
   }
}
