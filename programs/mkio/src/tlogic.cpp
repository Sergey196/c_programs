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

#include "tlogic.h"
#include "tcontroller.h"
#include <iostream>
#include <math.h>
#include <stdio.h>

TLogic::TLogic()
{
   pointOnController = TController::getInstance();
   //clearImpuls();
   readFromFile();
}
//---------------------------------------------------------------------------
void TLogic::readFromFile()
{
   char *buffer { nullptr };
   int length;
   FILE *file = fopen("./info", "r");
   if(file) {
      fseek(file, 0, SEEK_END);
      length = ftell(file);
      fseek(file, 0, SEEK_SET);
      buffer = new char[length];
      fread(buffer, 1, length, file);
      for(int i = 0; i < COUT_INPUT_BITES; i++)
      {
         impulsState[i + FIRST_POSITION_INPUT_BITE] = buffer[i] == '1' ? true : false;
      }
      delete buffer;
      fclose(file);
      updateSinchroimpuls();
      shangeLastBite();
   } else {
      clearImpuls(); 
      writeToFile();
   } 
}
//---------------------------------------------------------------------------
void TLogic::writeToFile()
{
   FILE *file = fopen("info", "w+");
   char array[COUT_INPUT_BITES];
   for(int i = 0; i < COUT_INPUT_BITES; i++)
   {
      array[i] = 0; 
      array[i] = impulsState[i + FIRST_POSITION_INPUT_BITE] ? '1' : '0';  
   }
   fwrite(array, sizeof(array), 1, file); 
   fclose(file);
}
//---------------------------------------------------------------------------
void TLogic::setNewValue(int value)
{
   //clearImpuls(); 
   setRangeValue(FIRST_POSITION_INPUT_BITE, 18, value);
   shangeLastBite();
   writeToFile();
}
//---------------------------------------------------------------------------
void TLogic::clearImpuls()
{
   impulsState[0] = true;
   impulsState[1] = true;
   impulsState[2] = false;
   for(int i = 0; i < COUT_INPUT_BITES; i++)
   {
      impulsState[i + FIRST_POSITION_INPUT_BITE] = false;
   }  
   shangeLastBite();
}
//---------------------------------------------------------------------------
void TLogic::setCommandType(CommandType _type) 
{ 
    typeCmd = _type; 
    updateSinchroimpuls();
    writeToFile();
}
//---------------------------------------------------------------------------
void TLogic::updateSinchroimpuls()
{
    if(typeCmd == dataWord) {
       impulsState[0] = false;
       impulsState[1] = false;
       impulsState[2] = true;  
    } else {
       impulsState[0] = true;
       impulsState[1] = true;
       impulsState[2] = false;
    }  
}
//---------------------------------------------------------------------------
std::string TLogic::getCommandInfo()
{
   /*if(std::accumulate(impulsState, impulsState + COUT_FULL_BITES, 0) == 2)
   {
      return "Пустая команда";
   }*/
   if(typeCmd == sendData) {
      //return getFormat() + getAddres() + getDirection() + getSubAddres() + getCoutData();  
      return getCommandWordInfo();
   } else if(typeCmd == dataWord) {
      return "Данные : " + std::to_string(convertBoolPartToInt(3, 18));
   } else if(typeCmd == requestWord) {
      return getRequestWordInfo();
   } else {
      return ""; 
   }
}
//---------------------------------------------------------------------------
int TLogic::convertBoolPartToInt(int begin, int end)
{
   int cout = end - begin; 
   int value { 0 }; 
   int degree { 0 };
   
   while(cout >= 0)
   {
      value += (impulsState[begin + cout] * (pow(2, degree))); 
      cout--; 
      degree++;
   }
   return value;
}
//---------------------------------------------------------------------------
std::string TLogic::getDirection()
{
   if(impulsState[8]) {
      return "КШ<-ОУ\n"; 
   } else {
      return "КШ->ОУ\n";  
   }
}
//---------------------------------------------------------------------------
std::string TLogic::getCommandDrivar(int value)
{
   if(value == 0) {
      return "Принять управление интерфейсом";
   } else if(value == 1) {
      return "Синхронизация"; 
   } else if(value == 2) {
      return "Передать ОС";  
   } else if(value == 3) {
      return "Начать самоконтроль";  
   } else if(value == 4) {
      return "Блокировать передатчик";  
   } else if(value == 5) {
      return "Разблокировать передатчик";  
   } else if(value == 6) {
      return "Блокировать признак неисправности ОУ";  
   } else if(value == 7) {
      return "Разблокировать признак неисправности ОУ";  
   } else if(value == 8) {
      return "Установит ОУ в исходное состояние";  
   } else if(((value > 8) && (value < 16)) || (value > 21)) {
      return "Резерв";   
   } else if(value == 16) {
      return "Передать векторное слово";    
   } else if(value == 17) {
      return "Синхронизация с СД";    
   } else if(value == 18) {
      return "Передать последнюю комманду";    
   } else if(value == 19) {
      return "Передать слово ВСК ОУ";    
   } else if(value == 20) {
      return "Блокировать i-й передатчик";    
   } else if(value == 21) {
      return "Разблоркировать i-й передатчик";    
   } else {
      return "";   
   }
}
//---------------------------------------------------------------------------
std::string TLogic::getRequestWordInfo()
{
   std::string result; 
   result += "Адрес ОУ: " + std::to_string(convertBoolPartToInt(3, 7)) + "\n";
   if(impulsState[8])
   {
      result += "Ошибка в сообщении(9)\n"; 
   }
   if(impulsState[9])
   {
      result += "Передача ОС(10)\n"; 
   }
   if(impulsState[10])
   {
      result += "Запрос на обслуживание(11)\n"; 
   }
   if(impulsState[14])
   {
      result += "Принятя груповая комманда(15)\n"; 
   }
   if(impulsState[15])
   {
      result += "Абонент занят(16)\n"; 
   }
   if(impulsState[16])
   {
      result += "Неисправность абонента(17)\n"; 
   }
   if(impulsState[17])
   {
      result += "Принято управление интерфейсом(18)\n"; 
   }
   if(impulsState[18])
   {
      result += "Неисправность ОУ(19)\n"; 
   }
   return result;
}
//---------------------------------------------------------------------------
std::string TLogic::getFormat()
{

   return ""; 
}
//---------------------------------------------------------------------------
std::string TLogic::getCommandWordInfo()
{
   auto isNoWordData = [](int value) {
      return (value == 0) || (value == 1) || (value == 2) || (value == 3) || (value == 4) || (value == 5) || (value == 6) || (value == 7) || (value == 8);
   };
   auto isWordData = [](int value) {
      return (value == 16) || (value == 17) || (value == 18) || (value == 19) || (value == 20) || (value == 21);
   };
   
   auto getSubadres = [](int value) {
      if(value == 30) {
         return "Подадрес : " + std::to_string(value) + " (признак тестирования)\n";
      } else {
         return "Подадрес : " + std::to_string(value) + "\n"; 
      }
   };
   
   int format { 0 };
   std::string result; 
   int addres = convertBoolPartToInt(3, 7);
   bool direction = impulsState[8];
   int subAddres = convertBoolPartToInt(9, 13);
   int dataCount = convertBoolPartToInt(14, 18);
   if((addres == 31) && !direction) {
       result += "Груповая комманда\n";
       if((subAddres != 0) && (subAddres != 31)) {
          format = 7; 
          result += getSubadres(subAddres);
          result += "Число СД: " + std::to_string(dataCount == 0 ? 32 : dataCount) + "\n";
       } else if(isNoWordData(dataCount)) {
          format = 9;  
          result += "Код КУ: " + getCommandDrivar(dataCount) + "\n";
       } else if(isWordData(dataCount)) { 
          format = 10;  
          result += "Код КУ: " + getCommandDrivar(dataCount) + "\n";
       }
           
   } else if(addres != 31) {
      result += "Адрес ОУ: " + std::to_string(convertBoolPartToInt(3, 7)) + "\n";
      if(subAddres != 0 && subAddres != 31) {
          result += getSubadres(subAddres);
          result += getDirection();
          result += "Число СД: " + std::to_string(dataCount == 0 ? 32 : dataCount) + "\n";
          if(direction) {
             format = 2; 
          } else {
             format = 1; 
          }
      } else {
          //result += "Режим управления\n"; 
          result += getDirection(); 
          if(isNoWordData(dataCount)) {
             format = 4; 
          } else if(isWordData(dataCount)) {
             if(direction) {
                format = 5;  
             } else {
                format = 6;   
             }
          }
          result += "Код КУ: " + getCommandDrivar(dataCount) + "\n";
      }
   }
   if(format != 0) { 
      return "Формат сообщения: " + std::to_string(format) + "\n" + result; 
   } else {
      return "Неизвестная комманда";  
   }
}
//---------------------------------------------------------------------------
void TLogic::setRangeValue(int begin, int end, int value)
{
   int countRange = end - begin;
   while(countRange >= 0)
   {
      impulsState[begin + countRange] = value & 1;
      value /= 2;
      countRange--; 
   }
   shangeLastBite();
   writeToFile();
}
//---------------------------------------------------------------------------
int TLogic::getRangeValue(int begin, int end)
{
   return convertBoolPartToInt(begin, end);
}
//---------------------------------------------------------------------------
int TLogic::getMessageValue()
{
   return convertBoolPartToInt(3, 18); 
}
//---------------------------------------------------------------------------
void TLogic::clickBitePanel(int position)
{
   impulsState[position] ^= 1;   
   shangeLastBite();
   writeToFile();
}
//---------------------------------------------------------------------------
void TLogic::shangeLastBite()
{
   int parity { 1 };
   for(int i = 0; i < COUT_INPUT_BITES; i++)
   {
      if(impulsState[i + FIRST_POSITION_INPUT_BITE]) {
         parity++;  
      } 
   } 
   impulsState[19] = !(parity & 1);
}
