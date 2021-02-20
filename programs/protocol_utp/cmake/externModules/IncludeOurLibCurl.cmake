#Подключение библиотеки libcurl из проекта
#проверьте, что есть переменная CMAKE_MINOR_VERSION
MACRO(include_our_lib_curl)
   message("Check libcurl")
   find_path( LIB_CURL_INCLUDE_DIR curl HINTS ${CMAKE_SOURCE_DIR}/src_lib/libcurl/include )
   find_library(LIB_CURL_LIBRARIES NAMES curl PATHS ${LIBRARY_OUTPUT_PATH})
   message(LIB_CURL_INCLUDE_DIR=${LIB_CURL_INCLUDE_DIR})
   message(LIB_CURL_LIBRARIES  =${LIB_CURL_LIBRARIES})
   if(${LIB_CURL_INCLUDE_DIR} STREQUAL "LIB_CURL_INCLUDE_DIR-NOTFOUND")
      message("Check libcurl ... NOT FOUND")
   else(${LIB_CURL_INCLUDE_DIR} STREQUAL "LIB_CURL_INCLUDE_DIR-NOTFOUND")
      message("Check libcurl ... OK")
   endif(${LIB_CURL_INCLUDE_DIR} STREQUAL "LIB_CURL_INCLUDE_DIR-NOTFOUND")
   include_directories(${LIB_CURL_INCLUDE_DIR})
ENDMACRO(include_our_lib_curl)