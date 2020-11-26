/*
 * Copyright 2020 utkinsv <email>
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

#ifndef MAINGUI_H
#define MAINGUI_H

#include <QMainWindow>
class QFrame;
class Controller;

class MainGui : public QMainWindow
{
public:
    MainGui(Controller *_controller);
    void start();
private:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent( QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintField();
    void paintEnemyField();
    void paintShipsField();
    void paintBeatField();
    void paintReservShip();
    
    Controller *controller;
    int xpos = -1;
    int ypos = -1;
    bool reservShipChangeFlag { false };
    bool verticalOrHorisontal { true };
};

#endif // MAINGUI_H
