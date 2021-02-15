#ifndef TMAINCLASS_H
#define TMAINCLASS_H

#include "lib_integrity_constants.h"
#include <vector>
#include <map>
#include <memory>

namespace _integrity_control
{
    /**
    * @brief Интерфейс вывода данных класса в виде строки
    * 
    */
    class ObjectCalcHashIface
   { 
      public: 
          /**
          * @brief Вывод данных класса в виде строки
          * 
          * @return Полученный результат
          */
          virtual std::string convertDataToString() = 0; 
   };
   
   /**
   * @brief Интерфейс реакции на несовпадение контрольных сумм
   * 
   */
   class TEventsInface
   {
      public: 
          /**
          * @brief Нарушение контрольной суммы оперативных данных
          * 
          * @param indexType Индификотор группы контрольной суммы
          */
          virtual void dataIntegrityViolation(int indexType, bool state) = 0; 
          /**
          * @brief Нарушение контрольной суммы ПО
          * 
          * @param indexType Индификотор группы контрольной суммы
          */
          virtual void poIntegrityViolation(int indexType, bool state) = 0; 
   };
    
   /**
   * @brief Класс группы данных для подсчёта и сравления их контрольной суммы с эталонной
   * 
   */
   class GroupIface
   {
      public: 
          /**
          * @brief Конструктор
          * 
          * @param _indexGroup Индификатор контрольной суммы
          * @param _hashEtalon Эталонная контрольная сумма
          */
          GroupIface(int _indexGroup, std::string _hashEtalon) { indexGroup = _indexGroup; hashEtalon = _hashEtalon; }
          /**
          * @brief Сравнивание подсчитанной контрольной суммы с эталонной
          * 
          * @return Результат проверки
          */
          bool checkHash();
          /**
          * @brief Получение индификатора группы данных
          * 
          * @return Индификатор данных
          */
          int getIndexGroup() { return indexGroup; }
      protected:
          /**
          * @brief Подсчёт контрольной суммы
          * 
          * @return Результат полсчёта
          */
          virtual std::string calcData() = 0; 
          int indexGroup { -1 };  ///< Индификатор данных
          std::string hashEtalon; ///< Эталонная контольная сумма
   };
   
   /**
   * @brief Группа объектов
   * 
   */
   class GroupDbArrayObjectsIface: public GroupIface
   {
      public:
          /**
          * @brief Конструктор
          * 
          * @param indexGroup Индификатор данных
          * @param _objects Список объектов
          * @param hashEtalon Эталонный хеш
          */
          GroupDbArrayObjectsIface(int indexGroup, std::vector<ObjectCalcHashIface *> _objects, std::string hashEtalon):GroupIface(indexGroup, hashEtalon) { objects = _objects; } 
      private: 
          /**
          * @brief Подсчёт контрольной суммы
          * 
          * @return Результат полсчёта
          */
         std::string calcData() override;  
         std::vector<ObjectCalcHashIface *>  objects; ///< Список указателей объектов
   };
   
   /**
   * @brief Группа файлов
   * 
   */
   class GroupDbFileIface: public GroupIface
   {
      public: 
          /**
          * @brief Конструктор
          * 
          * @param indexGroup Индификатор данных
          * @param _fileDir Список директорий файлов
          * @param hashEtalon Эталонный хеш
          */
          GroupDbFileIface(int indexGroup, std::vector<std::string> _fileDir, std::string hashEtalon):GroupIface(indexGroup, hashEtalon) { fileDir = _fileDir; } 
      protected:
          /**
          * @brief Подсчёт контрольной суммы
          * 
          * @return Результат полсчёта
          */
          std::string calcData() override;  
          std::vector<std::string> fileDir; ///< Список директорий файлов
   };
   
   /**
   * @brief Интерфейс хранилища данных
   * 
   */
   class TDbIface
   {
      public: 
          /**
          * @brief Заполнение списка объектами
          * 
          * @param listGrops Список для заполнения
          */
          virtual void getListObjectsGroup(std::vector<GroupIface*> &listGrops) = 0; 
          /**
          * @brief Заполнение списка файлов
          * 
          * @param listGrops Список файлов
          */
          virtual void getListPoGroup(std::vector<GroupIface*> &listGrops) = 0;
   };
   
    /**
    * @brief Настройка проверки целостности оперативных данных и ПО
    * 
    */
   struct LibIntegritySettings
   {
      int periodIntegrityPo;      ///< интервал времени проверки ПО
      int periodIntegrityData;    ///< интервал времени проверки оперативных данных    
      TEventsInface *ifaceClass;  ///< указатель на интерфейс отправки нарушения целостеости 
      TDbIface *dbIface;          ///< указатель на класс хранилища данных 
      
   }; 
   
   
    
   /**
   * @brief Класс мотиторинга контролных сумм файлов
   * 
   */
   class DataChecksumMonitoring
   {
      public:
          /**
          * @brief Инициализация настройками
          * 
          * @param _settings Настройки алгоритма
          */
          void init(LibIntegritySettings _settings);
          /**
          * @brief Старт мониторинга контроля целостености
          * 
          */
          void startIntegrity();   
          /**
          * @brief Установка флага прерывания мониторинга контроля целостности
          * 
          * @param state Значение флага
          */
          void setIntegrityState(bool state);
          
      private:
          /**
          * @brief Проверка контрольных сумм оперативных данных
          * 
          */
          void checkHashData();
          /**
          * @brief Проверка контрольных сумм ПО
          * 
          */
          void checkHashPo();
          
         LibIntegritySettings settings;                    ///< Настройки мониторинга целостности ПО и оперативных данных
         std::vector<GroupIface*> listObjectGrops;         ///< Список групп объектов
         std::vector<GroupIface*> listPoGrops;             ///< Список групп файлов
         bool stopIntegrityDataFlag { false };             ///< Флаг паузы контроля целосности объектов                    
   };
};
#endif // TMAINCLASS_H
