#Подключение библиотеки libpxx-3.1 с проверкой версии cmake из нашего проекта
#проверьте, что есть переменная CMAKE_MINOR_VERSION
MACRO(include_our_lib_pqxx)
message (${CMAKE_SYSTEM} ">>>>>>>>>>>>>>>>>>>>>>>>")
   if (${CMAKE_SYSTEM_VERSION} EQUAL "2.6.34-3-generic")
      message("Check libpqxx for astra")
      find_path( LIB_PQXX_INCLUDE_DIR pqxx HINTS ${CMAKE_SOURCE_DIR}/src_lib/libpqxxm/include/ )
      find_library(LIB_PQXX_LIBRARIES NAMES pqxx PATHS  ${LIBRARY_OUTPUT_PATH} )
      if(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
         message("Check libpqxx ... NOT FOUND")
      else(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
         message("Check libpqxx ... OK")
      endif(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
      message(${LIB_PQXX_INCLUDE_DIR})
      include_directories(${LIB_PQXX_INCLUDE_DIR})
   else(${CMAKE_SYSTEM_VERSION} EQUAL "2.6.34-3-generic")
      if (${CMAKE_SYSTEM_VERSION} EQUAL "2.4.32-vniins42bigmem")
         message("Check libpqxx for mcbc")
         #find_path( LIB_PQXX_INCLUDE_DIR pqxx HINTS ${CMAKE_SOURCE_DIR}/src_lib/libpqxxm/include/ )
         set ( LIB_PQXX_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src_lib/libpqxxm/include/ )
         find_library(LIB_PQXX_LIBRARIES NAMES pqxx PATHS  ${LIBRARY_OUTPUT_PATH} )
         if(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
            message("Check libpqxx ... NOT FOUND")
         else(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
            message("Check libpqxx ... OK")
         endif(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
         message(${LIB_PQXX_INCLUDE_DIR})
         include_directories(${LIB_PQXX_INCLUDE_DIR})      
      else(${CMAKE_SYSTEM_VERSION} EQUAL "2.4.32-vniins42bigmem")  
         message("Check libpqxx for other")
         find_path( LIB_PQXX_INCLUDE_DIR pqxx HINTS ${CMAKE_SOURCE_DIR}/src_lib/libpqxx/include/ )
         find_library(LIB_PQXX_LIBRARIES NAMES pqxx PATHS  ${LIBRARY_OUTPUT_PATH} )
         if(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
            message("Check libpqxx ... NOT FOUND")
         else(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
            message("Check libpqxx ... OK")                           
         endif(${LIB_PQXX_INCLUDE_DIR} STREQUAL "LIB_PQXX_INCLUDE_DIR-NOTFOUND")
         message(${LIB_PQXX_INCLUDE_DIR})
         include_directories(${LIB_PQXX_INCLUDE_DIR})
      endif(${CMAKE_SYSTEM_VERSION} EQUAL "2.4.32-vniins42bigmem")
   endif(${CMAKE_SYSTEM_VERSION} EQUAL "2.6.34-3-generic")
ENDMACRO(include_our_lib_pqxx)   

