#Проверка версии ядра, если меньше 2.6 возвращаем false
#Должен существовать файл ${CONFIG_FILE}.h.in с переменной KERNEL_LESS_2_6
#В результате выполнения скрипта устанавливается переменная IS_KERNEL_LESS_2_6 в true или false
MACRO(check_kernel_less_2_6 PROJ_HEADERS_DIRECTORY CONFIG_FILE)
   message(${CMAKE_SYSTEM_VERSION} )
   string(REGEX MATCH "^.\\.." SYSTEM_VERSION ${CMAKE_SYSTEM_VERSION})
   message(${SYSTEM_VERSION} )
   string(COMPARE LESS ${SYSTEM_VERSION} "2.6" IS_KERNEL_LESS_2_6)
   message(IS_KERNEL_LESS_2_6=${IS_KERNEL_LESS_2_6} )
   if(IS_KERNEL_LESS_2_6)
      set(KERNEL_LESS_2_6 1)
   endif(IS_KERNEL_LESS_2_6)
   configure_file(${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE}.in ${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE})
ENDMACRO(check_kernel_less_2_6)