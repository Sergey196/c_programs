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

#ifndef TCONTROLLER_H
#define TCONTROLLER_H

#include <QObject>
#include <string>
#include "baseitem.h"

class TMainWindow;
class TLogic;

class TController: public QObject
{
   Q_OBJECT 
   public:
      static TController *getInstance(); 
      ~TController(); 
      void init();
      void start();
      void setNewValue(int value);
      void setCommandType(CommandType type);
      bool getImpulsState(int index);
      std::string getCommandInfo();
      void setRangeValue(int begin, int end, int value);
      int getRangeValue(int begin, int end);
      int getMessageValue();
      void clickBitePanel(int position);
   private:
      TMainWindow *pointOnGui; 
      TLogic *pointOnLogic;
      static TController *instance;
   signals: 
      void update();  
};

#endif // TCONTROLLER_H
