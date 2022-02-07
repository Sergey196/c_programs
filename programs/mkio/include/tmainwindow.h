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

#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include "baseitem.h"

class TController;
class QSpinBox;
class QStackedWidget;

const int COUT_INPUTS { 4 };

class TMainWindow: public QMainWindow
{
   Q_OBJECT 
   public:
      TMainWindow();
   private:   
      void repaintImpuls(); 
      void repaintStyle();
      bool flagChangeInput { false };
      TController *pointOnController;
private slots:
    void fgsgsdgsdf(int) {}
};

class TBitesPanel: public QFrame
{
   Q_OBJECT 
   public: 
      TBitesPanel(QWidget *parent = nullptr);
      void setWord(int index);
      //void update();
   private:
      //QLabel *inputBinaresValueLbl[COUT_INPUT_BITES]; 
      //QLabel *inputBinaresLbl[COUT_FULL_BITES]; 
      QStackedWidget *stack;
      TController *pointOnController; 
      bool flagChangeInput { false };
};

#endif // TMAINWINDOW_H
