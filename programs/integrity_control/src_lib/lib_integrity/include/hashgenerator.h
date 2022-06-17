#ifndef HASHGENERATOR_H
#define HASHGENERATOR_H

#include "lib_integrity_constants.h"
#include "tbuffer.h"
#include <vector>

namespace _integrity_control
{
   /**
   * @brief Интерфейс подсчётов контрольных сумм
   * 
   */
   class HashGenerator
   {
      public:
          /**
          * @brief Подсчёт контрольной суммы файлов
          * 
          * @param filesPath Список директорий файлов
          * @param typeHashCalculate Способ подсчёта контрольной суммы
          * @return Вычесленная контрольная сумма
          */
          static std::string calcHash(std::vector<std::string> filesPath, hashCountingMethod typeHashCalculate);
          /**
          * @brief Подсчёт контрольной суммы объектов
          * 
          * @param objects Список объектов
          * @param typeHashCalculate Способ подсчёта контрольной суммы
          * @return Вычесленная контрольная сумма
          */
          static std::string calcHash(std::vector<ObjectInfo> objects, hashCountingMethod typeHashCalculate);
          /**
          * @brief Подсчёт контрольной суммы строки
          * 
          * @param data Строка
          * @param typeHashCalculate Способ подсчёта контрольной суммы
          * @return Вычесленная контрольная сумма
          */
          static std::string calcHashString(std::string data, hashCountingMethod typeHashCalculate);
       private:
           /**
           * @brief Разбор каждого файлов по частям и загрузка полученных результатов в буфер
           * 
           * @param filesPath Список директорий файлов
           * @param buffer Указатель на класс буффера
           */
           static void bufferFilling(std::vector<std::string> filesPath, TBuffer *buffer);
           /**
           * @brief Загрузка данных каждого объекта в буфер
           * 
           * @param objects Список информации об объектах
           * @param buffer Указатель на класс буффера
           */
           static void bufferFilling(std::vector<ObjectInfo> objects, TBuffer *buffer);
           /**
           * @brief Инициализация буфера в зависимости от тписв высчитываемого хеша
           * 
           * @param buffer Указатель на класс буффера
           * @param typeHashCalculate Способ подсчёта контрольной суммы
           */
           static void changeTypeBuffer(TBuffer *&buffer, hashCountingMethod typeHashCalculate);
   };
};

#endif // HASHGENERATOR_H
