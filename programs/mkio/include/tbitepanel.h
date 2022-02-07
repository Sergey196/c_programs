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

#ifndef TBITEPANEL_H
#define TBITEPANEL_H

#include <QLabel>

class TController;

class TBitePanel : public QLabel
{
   public:
      TBitePanel(int _position, QWidget* parent = nullptr);
   private:
      void mouseDoubleClickEvent(QMouseEvent *event) override; 
      TController *pointOnController;  
      int position { -1 }; 
};

#endif // TBITEPANEL_H
