#Проверка версии библиотеки libc, если меньше 2.1.4 возвращаем true
#Должен существовать файл ${CONFIG_FILE}.h.in с переменной LIBC_LESS_2_1_4
#В результате выполнения скрипта устанавливается переменная LIBC_LESS_2_1_4 в true или false
#Пока нужно только для определения сигнатуры функции iconv
MACRO(check_libc_less_2_1_4 PROJ_HEADERS_DIRECTORY CONFIG_FILE)
   set(LS_CMD ls /lib /lib/i386-linux-gnu/ /lib/x86_64-linux-gnu/)
   set(GREP_CMD grep ^libc-)
   execute_process(COMMAND ${LS_CMD} COMMAND ${GREP_CMD} OUTPUT_VARIABLE LIBC )
#    message(LIBC=${LIBC})
   string(REGEX MATCH "[0-9].*[0-9]" LIBC_VERSION ${LIBC})
   message(LIBC_VERSION=${LIBC_VERSION})
   string(COMPARE LESS ${LIBC_VERSION} "2.1.4"  LIBC_LESS_2_1_4)
   message(LIBC_LESS_2_1_4=${LIBC_LESS_2_1_4})
   # string(COMPARE LESS "2.3.6" "2.1.4"  LIBC_LESS_2_1_4)
   # message(LIBC_LESS_2_1_4=${LIBC_LESS_2_1_4})
   # string(COMPARE LESS "2.1.3" "2.1.4"  LIBC_LESS_2_1_4)
   # message(LIBC_LESS_2_1_4=${LIBC_LESS_2_1_4})
   configure_file(${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE}.in ${PROJ_HEADERS_DIRECTORY}/${CONFIG_FILE})
ENDMACRO(check_libc_less_2_1_4)
