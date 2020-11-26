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

#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    void setDefault();
    void setShip(int shipId);

    bool isShip() { return isShipFlag; }
    bool isBroken() { return brokenFlag; }
    void cellAtacker() { brokenFlag = true; }
    void refreshState() { brokenFlag = false; isShipFlag = false; idShip = -1; }
private:
   bool brokenFlag {false};   
   bool isShipFlag {false};   
   int idShip { -1 };
};

#endif // CELL_H
