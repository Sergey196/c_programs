#include "tbuffer.h"
#include "lib_integrity_constants.h"
#include <iostream>
#include <cstring>
#include <sstream>

namespace _integrity_control
{
   void TBuffer::convertObjectToChar(unsigned char *array, void *object, int sizeObject)
   {
      memcpy(array, object, sizeObject); 
   }
   //-----------------------------------------------------------------------------
   TBufferCrc32::TBufferCrc32()
   {
       for (unsigned int i = 0; i < 256; i++)
       {
           crc = i;
           for (int j = 0; j < 8; j++)
               crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
           crc_table[i] = crc;
       };
       crc = 0xFFFFFFFFUL;
   }
   //-----------------------------------------------------------------------------
   void TBufferCrc32::addNewData(unsigned char *value, int length)
   {
       while(length--)
       {
          crc = crc_table[(crc ^ *value++) & 0xFF] ^ (crc >> 8);
       }
   }
   //-----------------------------------------------------------------------------
   std::string TBufferCrc32::calculateResult()
   {
      return std::to_string(crc ^ 0xFFFFFFFFUL);
   }
   //-----------------------------------------------------------------------------
   void TBufferCrc8::addNewData(unsigned char *value, int length)
   {
       while(length--)
       {
          crc ^= *value++;
          for (int i = 0; i < 8; i++)
          {
             crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
          }
       }
   }
   //-----------------------------------------------------------------------------
   TBufferMd5::TBufferMd5()
   {
      MD5_Init(&md5handler);
   }
   //-----------------------------------------------------------------------------
   void TBufferMd5::addNewData(unsigned char *value, int length)
   {
       MD5_Update(&md5handler, value, length);
   }
   //-----------------------------------------------------------------------------
   std::string TBufferMd5::calculateResult()
   {
      unsigned char result[md5Size];
      MD5_Final(result, &md5handler);
      std::stringstream ss;
      for(int i = 0; i < md5Size; i++)
      {
         ss << std::hex << (int)result[i]; 
      } 
      return ss.str();
   }
}
