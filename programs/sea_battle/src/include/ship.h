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

#ifndef SHIP_H
#define SHIP_H

class Ship
{
public:
    Ship(int _coutCell) { coutCell = _coutCell; coutNormalCell = _coutCell; }

    bool isActive() { return isActiveFlag; }
    void setActive() { isActiveFlag = true; }
    void setInActive() { isActiveFlag = false; }
    int getCoutCell() { return coutCell; }
    void refreshState() { isActiveFlag = false; coutNormalCell = coutCell; destroyFlag = false; }
    bool isDestroy() { return destroyFlag; }
    void setDestroyFlag() { destroyFlag = true; }
private:
   int coutCell;
   int coutNormalCell;
   bool isActiveFlag { false };
   bool destroyFlag { false };
};

#endif // SHIP_H
