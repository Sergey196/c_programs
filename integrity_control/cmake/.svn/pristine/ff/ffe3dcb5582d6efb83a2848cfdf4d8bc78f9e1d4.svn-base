#Проверка архитектуры процессоря на 64 бита, если процессор 64 битный (uname -p выдает x86_64) возвращаем true, если нет - false
#Должен существовать файл config.h.in с переменной __64BIT_ARCH__
#В результате выполнения скрипта устанавливается переменная IS_X64_86 в true или false
MACRO(check_64bit_arch PROJ_HEADERS_DIRECTORY CONFIG_FILE)
#    message(CMAKE_SYSTEM_PROCESSOR = ${CMAKE_SYSTEM_PROCESSOR})
   string(REGEX MATCH "^x86_64" PROCESSOR_TYPE ${CMAKE_SYSTEM_PROCESSOR})
   if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "^x86_64")
      message("You are using x86_64 architecthure!!!!!!")
      set(__64BIT_ARCH__ 1)      
   endif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "^x86_64")
   configure_file(${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE}.in ${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE})
ENDMACRO(check_64bit_arch)