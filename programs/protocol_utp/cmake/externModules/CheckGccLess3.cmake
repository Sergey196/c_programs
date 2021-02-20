#Проверка что версия компилятора младше 3.0 - в 2.95 и младше есть ряд не реализованных функций и багов
#Должен существовать файл ${CONFIG_FILE}.h.in с переменной IS_GCC_LESS_3
#В результате выполнения скрипта устанавливается переменная IS_GCC_LESS_3 в true или false
MACRO(check_gcc_less_3)
   set(GCC_V_CMD gcc --version)
   set(GCC_V_GREP_CMD grep "[0-9]\\.[0-9]")
   set(GCC_V_SED_SQR_BRACES_CMD sed "s,\\[[-a-zA-Z.0-9_ ]\\+\\],,g")
   set(GCC_V_SED_BRACES_CMD sed "s,([-a-zA-Z.0-9/ ]\\+),,g")
   set(GCC_V_SED_ALPHA_CMD sed "s/[a-zA-Z]\\+//g")
   set(GCC_V_SED_TABS_CMD sed "s/\\s\\+//g")
   execute_process(COMMAND ${GCC_V_CMD} COMMAND ${GCC_V_GREP_CMD} COMMAND ${GCC_V_SED_BRACES_CMD} COMMAND ${GCC_V_SED_SQR_BRACES_CMD} COMMAND ${GCC_V_SED_ALPHA_CMD}  COMMAND ${GCC_V_SED_TABS_CMD} OUTPUT_VARIABLE GCC_V_STR )
#    message(GCC_V_STR__=${GCC_V_STR})
   string(REGEX MATCH "[0-9]\\.[0-9]+\\.[0-9]+.$" GCC_VERSION ${GCC_V_STR})
   string(REGEX MATCH "^[0-9]+" GCC_MAJOR ${GCC_VERSION})
#    message(GCC_MAJOR=${GCC_MAJOR})
   string(COMPARE LESS ${GCC_MAJOR} "3" IS_GCC_LESS_3)
#    message(IS_GCC_LESS_3=${IS_GCC_LESS_3})
#    configure_file(${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE}.in ${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE})
ENDMACRO(check_gcc_less_3)

MACRO(check_gcc_less_3_conf PROJ_HEADERS_DIRECTORY CONFIG_FILE)
   check_gcc_less_3()
   configure_file(${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE}.in ${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE})
ENDMACRO(check_gcc_less_3_conf)