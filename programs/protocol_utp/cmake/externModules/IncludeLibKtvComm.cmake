#Подключение библиотеки libktvcomm от Теркома с проверкой версии cmake
#проверьте, что есть переменная CMAKE_MINOR_VERSION
MACRO(include_lib_ktvcomm)
   if (${CMAKE_MINOR_VERSION} LESS 8)
      message("Check libktvcomm")
      find_path( LIB_KTVCOMM_INCLUDE_DIR ktvcomm.h HINTS /usr/include/libktvcomm/ /usr/local/include/libktvcomm/ )
      find_library(LIB_KTVCOMM_LIBRARIES NAMES ktvcomm PATHS /usr/lib/ /usr/local/lib)

      if(${LIB_KTVCOMM_INCLUDE_DIR} STREQUAL "LIB_KTVCOMM_INCLUDE_DIR-NOTFOUND")
         message("Check libktvcomm ... NOT FOUND")
      else(${LIB_KTVCOMM_INCLUDE_DIR} STREQUAL "LIB_KTVCOMM_INCLUDE_DIR-NOTFOUND")
         message("Check libktvcomm ... OK")
      endif(${LIB_KTVCOMM_INCLUDE_DIR} STREQUAL "LIB_KTVCOMM_INCLUDE_DIR-NOTFOUND")
      include_directories(${LIB_KTVCOMM_INCLUDE_DIR})
   else(${CMAKE_MINOR_VERSION} LESS 8)
      message("Check libktvcomm")
      find_package(LibKtvComm REQUIRED)

      if(${LIB_KTVCOMM_INCLUDE_DIR} STREQUAL "LIB_KTVCOMM_INCLUDE_DIR-NOTFOUND")
         message("Check libktvcomm ... NOT FOUND")
      else(${LIB_KTVCOMM_INCLUDE_DIR} STREQUAL "LIB_KTVCOMM_INCLUDE_DIR-NOTFOUND")
         message("Check libktvcomm ... OK")                           
      endif(${LIB_KTVCOMM_INCLUDE_DIR} STREQUAL "LIB_KTVCOMM_INCLUDE_DIR-NOTFOUND")
      include_directories(${LIB_KTVCOMM_INCLUDE_DIR})
   endif(${CMAKE_MINOR_VERSION} LESS 8)
ENDMACRO(include_lib_ktvcomm)   

