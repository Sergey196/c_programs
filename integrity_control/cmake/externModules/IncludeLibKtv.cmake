#Подключение библиотеки libktv от Теркома с проверкой версии cmake
#проверьте, что есть переменная CMAKE_MINOR_VERSION
MACRO(include_lib_ktv)
   if (${CMAKE_MINOR_VERSION} LESS 8)
      message("Check libktv")
      find_path( LIB_KTV_INCLUDE_DIR ktv.h HINTS /usr/include/libktv/ /usr/local/include/libktv/ )
      find_library(LIB_KTV_LIBRARIES NAMES ktv PATHS /usr/lib/ /usr/local/lib)

      if(${LIB_KTV_INCLUDE_DIR} STREQUAL "LIB_KTV_INCLUDE_DIR-NOTFOUND")
         message("Check libktv ... NOT FOUND")
      else(${LIB_KTV_INCLUDE_DIR} STREQUAL "LIB_KTV_INCLUDE_DIR-NOTFOUND")
         message("Check libktv ... OK")
      endif(${LIB_KTV_INCLUDE_DIR} STREQUAL "LIB_KTV_INCLUDE_DIR-NOTFOUND")
      include_directories(${LIB_KTV_INCLUDE_DIR})
   else(${CMAKE_MINOR_VERSION} LESS 8)
      message("Check libktv")
      find_package(LibKtv REQUIRED)

      if(${LIB_KTV_INCLUDE_DIR} STREQUAL "LIB_KTV_INCLUDE_DIR-NOTFOUND")
         message("Check libktv ... NOT FOUND")
      else(${LIB_KTV_INCLUDE_DIR} STREQUAL "LIB_KTV_INCLUDE_DIR-NOTFOUND")
         message("Check libktv ... OK")                           
      endif(${LIB_KTV_INCLUDE_DIR} STREQUAL "LIB_KTV_INCLUDE_DIR-NOTFOUND")
      include_directories(${LIB_KTV_INCLUDE_DIR})
   endif(${CMAKE_MINOR_VERSION} LESS 8)
ENDMACRO(include_lib_ktv)   

