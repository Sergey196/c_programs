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
   
   auto printField = [&painter](CellInfo info) {
       if(info.value == FREE) {
          painter.setBrush(Qt::gray);    
       } else if(info.value == FOOD) {
          painter.setBrush(Qt::white);  
       } else if(info.value == SNAKE) {
           painter.setBrush(Qt::red);   
       }
       
       painter.drawRect((info.coordinats.x + 2) * FIELD_SIZE, (info.coordinats.y + 2) * FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);  
   };
   
   for(int i = 0; i < COUT_ROWS_COLUMS; i++)
   {
      for(int j = 0; j < COUT_ROWS_COLUMS; j++)
      {
         printField(CellInfo { pointOnControler->getCellValue(i, j), CellCoordinats { i, j } });
      }
   }
}
//---------------------------------------------------------------------------
void TGui::keyPressEvent(QKeyEvent *event)
{

}
//---------------------------------------------------------------------------
void TGui::setGameState(bool state)
{
   std::cout << "TEST = " << state << std::endl; 
}
