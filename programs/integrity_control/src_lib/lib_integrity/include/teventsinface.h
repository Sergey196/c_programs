#ifndef TEVENTSINFACE_H
#define TEVENTSINFACE_H

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
       virtual void dataIntegrityViolation(int indexType) = 0; 
       /**
       * @brief Нарушение контрольной суммы ПО
       * 
       * @param indexType Индификотор группы контрольной суммы
       */
       virtual void poIntegrityViolation(int indexType) = 0; 
};

#endif // TEVENTSINFACE_H
