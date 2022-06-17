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

#include "tlogic.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <random>
#include "tcontroller.h"

TLogic::TLogic(TController *_pointOnControler)
{
   pointOnControler = _pointOnControler;
   connect(&timerStep, &QTimer::timeout, this, &TLogic::step);
}
//---------------------------------------------------------------------------
void TLogic::startGame()
{
    
}
//---------------------------------------------------------------------------
void TLogic::setDirection(Direction _direction) 
{ 
    
}
//---------------------------------------------------------------------------
void TLogic::step()
{
    
}
