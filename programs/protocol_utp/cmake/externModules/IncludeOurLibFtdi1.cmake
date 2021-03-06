#Подключение библиотеки libftdi1 из проекта
#проверьте, что есть переменная CMAKE_MINOR_VERSION
MACRO(include_our_lib_ftdi)
   message("Check libftdi")
   find_path( LIB_FTDI_INCLUDE_DIR NAMES ftdi.h ftdi_i.h HINTS ${CMAKE_SOURCE_DIR}/src_lib/libftdi/src/ )
   find_library(LIB_FTDI_LIBRARIES NAMES libftdi1.a libftdi1.so PATHS ${LIBRARY_OUTPUT_PATH})
   message(LIB_FTDI_INCLUDE_DIR=${LIB_FTDI_INCLUDE_DIR})
   message(LIB_FTDI_LIBRARIES  =${LIB_FTDI_LIBRARIES})
   if(${LIB_FTDI_INCLUDE_DIR} STREQUAL "LIB_FTDI_INCLUDE_DIR-NOTFOUND")
      message("Check libftdi ... NOT FOUND")
   else(${LIB_FTDI_INCLUDE_DIR} STREQUAL "LIB_FTDI_INCLUDE_DIR-NOTFOUND")
      message("Check libftdi ... OK")
   endif(${LIB_FTDI_INCLUDE_DIR} STREQUAL "LIB_FTDI_INCLUDE_DIR-NOTFOUND")
   include_directories(${LIB_FTDI_INCLUDE_DIR})
ENDMACRO(include_our_lib_ftdi)
