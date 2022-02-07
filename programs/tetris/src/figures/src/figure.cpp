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

#include "figure.h"

void Figure::stepDown()
{
   for(int i = 0; i < FIGURE_COORDINATES_COUT; i++)
   {
      newCoordinates[i].y = newCoordinates[i].y++; 
   }
}
//---------------------------------------------------------------------------
void Figure::applayPosition()
{
   for(int i = 0; i < FIGURE_COORDINATES_COUT; i++)
   {
      coordinates[i].y = newCoordinates[i].y; 
      coordinates[i].x = newCoordinates[i].x; 
   }  
}
