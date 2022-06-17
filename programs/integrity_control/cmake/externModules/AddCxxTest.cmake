#Подключение unit тестов cxxtest
#Первый параметр TESTED_BIN - тестируемый бинарник, например cuu
#Второй параметр - список заголовочных файлов с тестами
MACRO(add_lib_cxxtest TESTED_BIN)
#    find_package(CxxTest)
   include(FindCxxTest)
   set(CXXTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/cxxtest/cxxtest)
   set(CXXTEST_PYTHON_TESTGEN_EXECUTABLE ${CMAKE_SOURCE_DIR}/cxxtest/bin/cxxtestgen)
   set(CXXTEST_USE_PYTHON TRUE)
#    if(CXXTEST_FOUND)
      include_directories(${CXXTEST_INCLUDE_DIR})
      enable_testing()
      CXXTEST_ADD_TEST(test_${TESTED_BIN} test_${TESTED_BIN}.cpp ${ARGN})
      target_link_libraries(test_${TESTED_BIN} _${TESTED_BIN}) # as needed

#    endif(CXXTEST_FOUND)
ENDMACRO(add_lib_cxxtest)  

MACRO(add_bin_cxxtest TESTED_BIN)
#    find_package(CxxTest)
   include(FindCxxTest)
   set(CXXTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/cxxtest/cxxtest)
   set(CXXTEST_PYTHON_TESTGEN_EXECUTABLE ${CMAKE_SOURCE_DIR}/cxxtest/bin/cxxtestgen)
   set(CXXTEST_USE_PYTHON TRUE)
#    if(CXXTEST_FOUND)
      include_directories(${CXXTEST_INCLUDE_DIR})
      enable_testing()
      CXXTEST_ADD_TEST(test_${TESTED_BIN} test_${TESTED_BIN}.cpp ${ARGN})

#    endif(CXXTEST_FOUND)
ENDMACRO(add_bin_cxxtest)  
