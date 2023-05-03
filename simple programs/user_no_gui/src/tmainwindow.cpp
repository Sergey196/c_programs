/*
 * Copyright 2022 <copyright holder> <email>
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

#include "tmainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QGuiApplication>
#include <QScreen>

TMainWindow::TMainWindow()
{
   QRect screenGeometry = QGuiApplication::screens().at(0)->geometry();
   setGeometry(0, 0, screenGeometry.width(), screenGeometry.height());
    
   QFrame *mainFr = new QFrame();
   QVBoxLayout *mainLay = new QVBoxLayout(mainFr);
   
   QPushButton *btn = new QPushButton("Выход", mainFr);

   mainLay->addWidget(btn);
   setCentralWidget(mainFr);
   
   connect(btn, &QPushButton::released, []() { system("pkill -KILL -u $(whoami)"); });
}
