#ifndef TDEFINES_LIB_INTEGRITY_CONSTANTS_H
#define TDEFINES_LIB_INTEGRITY_CONSTANTS_H 1

namespace _integrity_control
{
   /**
   * @brief Типы подсчётов контрольных сумм
   * 
   */
   enum hashCountingMethod
   {
      md5,         
      crc8,
      crc32,
   };

   const int fileBuferSize = 512;   ///< Максимальный размер части файла для заполнения буфера
   const int maxObjectSize = 512;   ///< Максимальный размер объекта
   const int gostsumSize = 32;      ///< Размер результата подсчёта контрольной суммы алгоритма гост 2012
   const int md5Size = 16;          ///< Размер результата подсчёта контрольной суммы алгоритма md5
   
   /**
   * @brief Информация об объекте для буфера подсчёта контрольной суммы
   * 
   */
   struct ObjectInfo
   {
      int objectSize;       ///< Размер объекта
      void *objectPointer;  ///< Указатель на обект
   };

}

#endif
