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

#ifndef TLOGIC_H
#define TLOGIC_H

#include <string>
#include "baseitem.h"

class TController;

class TLogic
{
   public:
      TLogic();
      void setNewValue(int value);
      bool getImpulsState(int index) { return impulsState[index]; }
      std::string getCommandInfo();
      void setCommandType(CommandType _type);
      void setRangeValue(int begin, int end, int value);
      int getRangeValue(int begin, int end);
      int getMessageValue();
      void clickBitePanel(int position);
   private:
      std::string getDirection();  
      std::string getCommandDrivar(int value);
      std::string getFormat(); 
      std::string getCommandWordInfo(); 
      int convertBoolPartToInt(int begin, int end); 
      void clearImpuls(); 
      void shangeLastBite();
      void writeToFile();
      void readFromFile();
      void updateSinchroimpuls();
      std::string getRequestWordInfo();
      CommandType typeCmd { sendData };
      TController *pointOnController;
      bool impulsState[COUT_FULL_BITES];
};

#endif // TLOGIC_H
