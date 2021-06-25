#include "hashgenerator.h"
#include <cstring>
#include <fstream>
#include <iostream>

namespace _integrity_control
{
   //-----------------------------------------------------------------------------
   std::string HashGenerator::calcHash(std::vector<std::string> filesPath, hashCountingMethod typeHashCalculate)
   {
       TBuffer *buffer = nullptr;
       changeTypeBuffer(buffer, typeHashCalculate);
       bufferFilling(filesPath, buffer);
       return buffer->calculateResult();
   }
   //-----------------------------------------------------------------------------
   void HashGenerator::bufferFilling(std::vector<std::string> filesPath, TBuffer *buffer)
   {
       for (auto file : filesPath) // access by reference to avoid copying
       {
          unsigned char bufferArray[fileBuferSize];
          std::ifstream input_file(file);
          
          if(input_file.fail())
          {
             continue; 
          }
          while (!input_file.eof())
          {
             memset(bufferArray, 0, sizeof(bufferArray));
             input_file.read((char *)bufferArray, sizeof(bufferArray));
             buffer->addNewData(bufferArray, input_file.gcount());
          }
       }
   }
   //-----------------------------------------------------------------------------
   std::string HashGenerator::calcHash(std::vector<ObjectInfo> objects, hashCountingMethod typeHashCalculate)
   {
       TBuffer *buffer = nullptr;
       changeTypeBuffer(buffer, typeHashCalculate);
       bufferFilling(objects, buffer);
       return buffer->calculateResult();
   }
   //-----------------------------------------------------------------------------
   void HashGenerator::bufferFilling(std::vector<ObjectInfo> objects, TBuffer *buffer)
   {
       for (auto objectInfo : objects) // access by reference to avoid copying
       {
          unsigned char objectArray[maxObjectSize];
          memset(objectArray, 0, sizeof(objectArray));
          TBuffer::convertObjectToChar(objectArray, objectInfo.objectPointer, objectInfo.objectSize);
          buffer->addNewData(objectArray, maxObjectSize);
       }
   }
   //-----------------------------------------------------------------------------
   std::string HashGenerator::calcHashString(std::string data, hashCountingMethod typeHashCalculate)
   {
       TBuffer *buffer = nullptr;
       changeTypeBuffer(buffer, typeHashCalculate);
       buffer->addNewData((unsigned char *)data.c_str(), data.length());
       return buffer->calculateResult();
   }
   //-----------------------------------------------------------------------------
   void HashGenerator::changeTypeBuffer(TBuffer *&buffer, hashCountingMethod typeHashCalculate)
   {
       switch (typeHashCalculate)
       {
          case crc32:
          {
             buffer = new TBufferCrc32();
             break;
          }
          case crc8:
          {
             buffer = new TBufferCrc8();
             break;
          }
          case md5:
          { 
             buffer = new TBufferMd5();
             break;
          }
          default:
             return;
       }
   }
}
