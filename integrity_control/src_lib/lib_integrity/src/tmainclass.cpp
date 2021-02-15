#include "tmainclass.h"
#include "hashgenerator.h"
#include <thread>
#include <unistd.h>
#include <iostream>

namespace _integrity_control
{
   //----------------------------------------------------------------------------- 
   bool GroupIface::checkHash()
   { 
      return calcData() == hashEtalon; 
   }
   //-----------------------------------------------------------------------------
   std::string GroupDbArrayObjectsIface::calcData()
   {
      std::string allInfo;
      for(auto object : objects)
      {
         allInfo += object->convertDataToString(); 
      }
      return HashGenerator::calcHashString(allInfo, crc32);
   }
   //-----------------------------------------------------------------------------
   std::string GroupDbFileIface::calcData()
   {
      return HashGenerator::calcHash(fileDir, md5); 
   }
   //-----------------------------------------------------------------------------
   //-----------------------------------------------------------------------------
   //-----------------------------------------------------------------------------
   //-----------------------------------------------------------------------------
   //-----------------------------------------------------------------------------
   //-----------------------------------------------------------------------------
   //-----------------------------------------------------------------------------
   void DataChecksumMonitoring::init(LibIntegritySettings _settings)
   {
      settings = _settings; 
      settings.dbIface->getListObjectsGroup(listObjectGrops);
      settings.dbIface->getListPoGroup(listPoGrops);
      
   }
   //-----------------------------------------------------------------------------
   void DataChecksumMonitoring::startIntegrity()
   {
      std::thread([&]
      {
         while(true)
         {
            checkHashPo();
            sleep(settings.periodIntegrityPo);
         }
      }).detach();
      
      std::thread([&]
      {
         while(true)
         { 
            checkHashData();
            sleep(settings.periodIntegrityData);    
         }
      }).detach();
   }
   //-----------------------------------------------------------------------------
   void DataChecksumMonitoring::setIntegrityState(bool state)
   {
      stopIntegrityDataFlag = state;
   }
   //-----------------------------------------------------------------------------
   void DataChecksumMonitoring::checkHashData()
   {
       if(stopIntegrityDataFlag)
       {
          return;
       }
       for (auto dataGroup : listObjectGrops) 
       {
          settings.ifaceClass->dataIntegrityViolation(dataGroup->getIndexGroup(), dataGroup->checkHash());
       }
   }
   //-----------------------------------------------------------------------------
   void DataChecksumMonitoring::checkHashPo()
   {
       std::thread([this]
       {
           for (auto dataGroup : listPoGrops) 
           {
              settings.ifaceClass->poIntegrityViolation(dataGroup->getIndexGroup(), dataGroup->checkHash());
           }
       }).detach();
   }
}
