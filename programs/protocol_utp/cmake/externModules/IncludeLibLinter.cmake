#Подключение библиотеки liblinter с проверкой версии cmake
#проверьте, что есть переменная CMAKE_MINOR_VERSION
MACRO(include_lib_linter)
   if (${CMAKE_MINOR_VERSION} LESS 8)
      message("Check linter")
      execute_process(COMMAND rm -fr /usr/linter/intlib/libintlib.so)
      execute_process(COMMAND ar cr /usr/linter/intlib/libintlib.a /usr/linter/intlib/intlib.o)
      execute_process(COMMAND ranlib /usr/linter/intlib/libintlib.a)

      set(LIB_LINTER_LIBRARIES /usr/linter/intlib/libintlib.a)
      set(LIB_LINTER_INCLUDE_DIR /usr/linter/intlib)

      execute_process(COMMAND cp /usr/linter/samples/call/exlib/exlib.a /usr/linter/samples/call/exlib/libexlib.a)
      set(LIB_LINTER_LIBRARIES_EXLIB /usr/linter/samples/call/exlib/libexlib.a)

      if(${LIB_LINTER_INCLUDE_DIR} STREQUAL "LIB_LINTER_INCLUDE_DIR-NOTFOUND")
         message("Check linter intlib ... NOT FOUND")
      else(${LIB_LINTER_INCLUDE_DIR} STREQUAL "LIB_LINTER_INCLUDE_DIR-NOTFOUND")
         message("Check linter intlib ... OK")                           
      endif(${LIB_LINTER_INCLUDE_DIR} STREQUAL "LIB_LINTER_INCLUDE_DIR-NOTFOUND")

      include_directories(${LIB_LINTER_INCLUDE_DIR})

      set(LIB_LINTER_INCLUDE_DIR_EXLIB /usr/linter/samples/call/exlib/)

      if(${LIB_LINTER_INCLUDE_DIR_EXLIB} STREQUAL "LIB_LINTER_INCLUDE_DIR_EXLIB-NOTFOUND")
         message("Check linter exlib ... NOT FOUND")
      else(${LIB_LINTER_INCLUDE_DIR_EXLIB} STREQUAL "LIB_LINTER_INCLUDE_DIR_EXLIB-NOTFOUND")
         message("Check linter exlib ... OK")                           
      endif(${LIB_LINTER_INCLUDE_DIR_EXLIB} STREQUAL "LIB_LINTER_INCLUDE_DIR_EXLIB-NOTFOUND")

      include_directories(${LIB_LINTER_INCLUDE_DIR_EXLIB})
   else(${CMAKE_MINOR_VERSION} LESS 8)
      message("Check linter")
      find_package(LibLinter REQUIRED)
      execute_process(COMMAND rm -fr /usr/linter/intlib/libintlib.so)
      execute_process(COMMAND ar cr /usr/linter/intlib/libintlib.a /usr/linter/intlib/intlib.o)
      execute_process(COMMAND ranlib /usr/linter/intlib/libintlib.a)
      
      set(LIB_LINTER_LIBRARIES /usr/linter/intlib/libintlib.a)
#       set(LIB_LINTER_LIBRARIES /usr/linter/intlib/libintlib.a)

      if(${LIB_LINTER_INCLUDE_DIR} STREQUAL "LIB_LINTER_INCLUDE_DIR-NOTFOUND")
         message("Check linter intlib ... NOT FOUND")
      else(${LIB_LINTER_INCLUDE_DIR} STREQUAL "LIB_LINTER_INCLUDE_DIR-NOTFOUND")
         message("Check linter intlib ... OK")                           
      endif(${LIB_LINTER_INCLUDE_DIR} STREQUAL "LIB_LINTER_INCLUDE_DIR-NOTFOUND")

      include_directories(${LIB_LINTER_INCLUDE_DIR})     

      set(LIB_LINTER_INCLUDE_DIR_EXLIB /usr/linter/samples/call/exlib/)

      if(${LIB_LINTER_INCLUDE_DIR_EXLIB} STREQUAL "LIB_LINTER_INCLUDE_DIR_EXLIB-NOTFOUND")
         message("Check linter exlib ... NOT FOUND")
      else(${LIB_LINTER_INCLUDE_DIR_EXLIB} STREQUAL "LIB_LINTER_INCLUDE_DIR_EXLIB-NOTFOUND")
         message("Check linter exlib ... OK")                           
      endif(${LIB_LINTER_INCLUDE_DIR_EXLIB} STREQUAL "LIB_LINTER_INCLUDE_DIR_EXLIB-NOTFOUND")

      include_directories(${LIB_LINTER_INCLUDE_DIR_EXLIB})                      
   endif(${CMAKE_MINOR_VERSION} LESS 8)
ENDMACRO(include_lib_linter)   

