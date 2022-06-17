#Проверка что sh есть символическая ссылка на dash
#Должен существовать файл ${CONFIG_FILE}.h.in с переменной IS_SH_DASH
#В результате выполнения скрипта устанавливается переменная IS_SH_DASH в true или false
#Пока нужно только для определения сигнатуры функции iconv
MACRO(check_sh_is_dash PROJ_HEADERS_DIRECTORY CONFIG_FILE)
   set(LS_SH_CMD ls -l /bin/sh)
   execute_process(COMMAND ${LS_SH_CMD} OUTPUT_VARIABLE DASH_STR )
#    message(DASH_STR=${DASH_STR})
   string(REGEX MATCH "dash" IS_SH_DASH ${DASH_STR})
#    message(IS_SH_DASH=${IS_SH_DASH})
   string(COMPARE EQUAL "empty-${IS_SH_DASH}" "empty-dash"  IS_SH_DASH)
#    message(IS_SH_DASH=${IS_SH_DASH})
   configure_file(${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE}.in ${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE})
ENDMACRO(check_sh_is_dash)