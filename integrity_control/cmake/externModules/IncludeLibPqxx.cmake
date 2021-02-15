#Подключение библиотеки libpxx-1.0 с проверкой версии cmake
#проверьте, что есть переменная CMAKE_MINOR_VERSION
MACRO(include_lib_pqxx)
   if (${CMAKE_MINOR_VERSION} LESS 8)
      message("Check libpqxx")
      find_path( LIB_PQXX_INCLUDE_DIR pqxx HINTS /usr/include/pqxx/ /usr/local/include/pqxx/)
      find_library(LIB_PQXX_LIBRARIES NAMES pqxx PATHS /usr/lib/ /usr/local/lib)

      if(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
         message("Check libpqxx ... NOT FOUND")
      else(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
         message("Check libpqxx ... OK")
      endif(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
      include_directories(${LIB_PQXX_INCLUDE_DIR})
      message(${LIB_PQXX_INCLUDE_DIR} " || " ${LIB_PQXX_LIBRARIES})
   else(${CMAKE_MINOR_VERSION} LESS 9)
      message("Check libpqxx")
      find_package(LibPqxx REQUIRED)

      if(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
         message("Check libpqxx ... NOT FOUND")
      else(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
         message("Check libpqxx ... OK")                           
      endif(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
      include_directories(${LIB_PQXX_INCLUDE_DIR})
      message(${LIB_PQXX_INCLUDE_DIR})
   endif(${CMAKE_MINOR_VERSION} LESS 9)
ENDMACRO(include_lib_pqxx)   

