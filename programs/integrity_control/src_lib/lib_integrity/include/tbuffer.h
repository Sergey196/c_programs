#ifndef TBUFFER_H
#define TBUFFER_H

#include <openssl/md5.h>
#include <string>

const int CRC_TABLE_SIZE = 256; ///< Размер CRC32 таблицы

namespace _integrity_control
{
   /**
   * @brief Абстрактный класс буфера
   * 
   */
   class TBuffer
   {
      public:
          /**
          * @brief Заполнение буфера
          * 
          * @param value Новые данные
          * @param length Длина новых данных
          */
          virtual void addNewData(unsigned char *value, int length) = 0;
          /**
          * @brief Результат выполнения подсчёта
          * 
          * @return Контрольная сумма
          */
          virtual std::string calculateResult() = 0;
          /**
          * @brief Конвертирование обекта в массив char
          * 
          * @param array Массив вполучатель информации
          * @param object Укразатель на объект
          * @param sizeObject Размер объекта
          */
          static void convertObjectToChar(unsigned char *array, void *object, int sizeObject);
   };
   
   /**
   * @brief Подсчёт контрольной суммы CRC32
   * 
   */
   class TBufferCrc32: public TBuffer
   {
      public:
          TBufferCrc32();
          /**
          * @brief Заполнение буфера
          * 
          * @param value Новые данные
          * @param length Длина новых данных
          */
          void addNewData(unsigned char *value, int length) override;
          /**
          * @brief Результат выполнения подсчёта
          * 
          * @return Контрольная сумма
          */
          std::string calculateResult() override;
      private:
         unsigned long crc_table[CRC_TABLE_SIZE];  ///< CRC32 таблица
         unsigned long crc;                        ///< Результат подсчёта контрольной суммы
   };
   
   /**
   * @brief Подсчёт контрольной суммы CRC8
   * 
   */
   class TBufferCrc8: public TBuffer
   {
      public:
          /**
          * @brief Заполнение буфера
          * 
          * @param value Новые данные
          * @param length Длина новых данных
          */
          void addNewData(unsigned char *value, int length) override;
          /**
          * @brief Результат выполнения подсчёта
          * 
          * @return Контрольная сумма
          */
          std::string calculateResult()  override { return std::to_string(crc); }
      private:
         unsigned long crc { 0xFF };  ///< Результат подсчёта контрольной суммы
   };
   
   /**
   * @brief Подсчёт контрольной суммы MD5
   * 
   */
   class TBufferMd5: public TBuffer
   {
      public:
          /**
          * @brief Инициализация md5handler
          * 
          */
          TBufferMd5();
          /**
          * @brief Заполнение буфера
          * 
          * @param value Новые данные
          * @param length Длина новых данных
          */
          void addNewData(unsigned char *value, int length) override;
          /**
          * @brief Результат выполнения подсчёта
          * 
          * @return Контрольная сумма
          */
          std::string calculateResult() override;
      private:
         MD5_CTX md5handler;  ///< Хранилище состояния подсчёта контрольной суммы
   };
};

#endif // TBUFFER_H
