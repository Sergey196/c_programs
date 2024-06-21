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
       pointOnControler->startGame(); 
       repaint();
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
void TGui::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setFont(QFont("times", 18));
   
   auto printField = [&painter](int count, int x, int y) {
       if(count == 0) {
          painter.setBrush(Qt::white);    
       } else if(count == 2) {
          painter.setBrush(Qt::darkYellow);    
       } else if(count == 4) {
          painter.setBrush(Qt::darkGray);  
       } else if(count == 8) {
           painter.setBrush(Qt::gray);   
       } else if(count == 16) {
           painter.setBrush(Qt::lightGray);   
       } else if(count == 32) {
           painter.setBrush(Qt::green);   
       } else if(count == 64) {
           painter.setBrush(Qt::blue);   
       } else if(count == 128) {
           painter.setBrush(Qt::cyan);   
       } else if(count == 256) {
           painter.setBrush(Qt::magenta);   
       } else if(count == 512) {
           painter.setBrush(Qt::yellow);   
       } else if(count == 1024) {
           painter.setBrush(Qt::darkRed);   
       } else if(count == 2048) {
           painter.setBrush(Qt::darkBlue);   
       }
       painter.drawRect((x + 2) * FIELD_SIZE, (y + 2) * FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);  
       painter.drawText((x + 2) * FIELD_SIZE, (y + 2) * FIELD_SIZE, FIELD_SIZE, FIELD_SIZE, Qt::AlignCenter, /*(count > 0) ? QString::number(count) : ""*/QString::number(count));
   };
   
   for(int i = 0; i < COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         printField(pointOnControler->getCellValue(i, j), i, j);
      }
   }
}
//---------------------------------------------------------------------------
void TGui::keyPressEvent(QKeyEvent *event)
{
   if(!state_game) {
      return; 
   } 
   pointOnControler->keyPress(event->key());
   repaint();
   
}
//---------------------------------------------------------------------------
void TGui::setGameState(bool state)
{
   state_game = state;
   std::cout << "TEST state = " << state << std::endl; 
}
