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

#include "tcontroller.h"
#include "tmainwindow.h"
#include "tlogic.h"

TController *TController::instance { nullptr };
//---------------------------------------------------------------------------
TController *TController::getInstance()
{
   if(!instance)
   {
      instance = new TController(); 
   }
   return instance;
}
//---------------------------------------------------------------------------
void TController::init()
{
   pointOnLogic = new TLogic(); 
   pointOnGui = new TMainWindow();
}
//---------------------------------------------------------------------------
TController::~TController()
{
   delete pointOnGui;
   delete pointOnLogic;
}
//---------------------------------------------------------------------------
void TController::start()
{
    pointOnGui->show();
}
//---------------------------------------------------------------------------
void TController::setNewValue(int value)
{
   pointOnLogic->setNewValue(value); 
}
//---------------------------------------------------------------------------
bool TController::getImpulsState(int index)
{
   return pointOnLogic->getImpulsState(index); 
}
//---------------------------------------------------------------------------
std::string TController::getCommandInfo()
{
   return pointOnLogic->getCommandInfo(); 
}
//---------------------------------------------------------------------------
void TController::setCommandType(CommandType type)
{
   pointOnLogic->setCommandType(type);
}
//---------------------------------------------------------------------------
void TController::setRangeValue(int begin, int end, int value)
{
   pointOnLogic->setRangeValue(begin, end, value);  
}
//---------------------------------------------------------------------------
int TController::getRangeValue(int begin, int end)
{
   return pointOnLogic->getRangeValue(begin, end); 
}
//---------------------------------------------------------------------------
int TController::getMessageValue()
{
   return pointOnLogic->getMessageValue();  
}
//---------------------------------------------------------------------------
void TController::clickBitePanel(int position)
{
   pointOnLogic->clickBitePanel(position);
}
