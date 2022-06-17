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

#ifndef TGUI_H
#define TGUI_H

#include <QMainWindow>
#include "tbaseitem.h"

class TController;

struct CellInfo
{
   int x;
   int y;
   CellState state;
};

class TGui : public QMainWindow
{
   public:
      TGui(TController *pointOnControler);
      void gameStatus(bool status);
   private:
      void paintEvent(QPaintEvent *) override;
      void mousePressEvent( QMouseEvent* event) override;  
      TController *pointOnControler;
      bool startGameFlag { false };
};

#endif // TGUI_H
