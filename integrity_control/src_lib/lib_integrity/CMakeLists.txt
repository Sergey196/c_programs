set (PROJECT_LIB_INTEGRITY _integrity)
set (PROJECT_TEST_LIB_INTEGRITY integrity)
project(${PROJECT_LIB_INTEGRITY})
cmake_minimum_required(VERSION 3.7)
###############################################

set(CMAKE_MODULE_PATH 
${CMAKE_SOURCE_DIR}/cmake/externModules
)

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
###############################################

set(LIBRARIES_LIB_ISHTAR_FIFO
)

###############################################
set(LIBRARIES_LIB_ISHTAR_FIFO_NAME
)

###############################################
foreach(LIBRARY ${LIBRARIES_TEMP_LIB})   
   include_directories(${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/ ${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/include)
   message(${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/)
endforeach(LIBRARY)
###############################################
foreach(LIB_INC ${LIBRARIES_INCLUDE})
   include_directories(${LIB_INC})
endforeach(LIB_INC)
###############################################

set(HEADERS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TESTS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
###############################################
include_directories(${HEADERS_DIRECTORY} ${SOURCES_DIRECTORY} ${TESTS_DIRECTORY})
###############################################
set(HEADERS
   ${HEADERS_DIRECTORY}/lib_integrity_constants.h
   ${HEADERS_DIRECTORY}/tmainclass.h
   ${HEADERS_DIRECTORY}/hashgenerator.h
   ${HEADERS_DIRECTORY}/tbuffer.h
)

##############################################

set(SOURCES
   ${SOURCES_DIRECTORY}/tmainclass.cpp
   ${SOURCES_DIRECTORY}/hashgenerator.cpp
   ${SOURCES_DIRECTORY}/tbuffer.cpp
)

##########################################################################################
include_directories(${LIB_GOST_INCLUDE_DIR})
##########################################################################################

###############################################
#Включение в зависимости только h-ов, чтобы при 
#изменении cpp'ов в библиотеках не пересобиралось все подряд
set(ALLHEADERS ${HEADERS} ${QTHEADERS})
INCLUDE(IncludeOnlyHeaders)
include_only_headers(${ALLHEADERS})


add_library (${PROJECT_LIB_INTEGRITY} SHARED ${HEADERS} ${SOURCES})

set_target_properties(${PROJECT_LIB_ISHTAR_FIFO} PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib)
###############################################
target_link_libraries(${PROJECT_LIB_INTEGRITY} ${LIBRARIES_LIB_ISHTAR_FIFO_NAME} ${LIB_GOST_LIBRARIES})
install(TARGETS ${PROJECT_LIB_INTEGRITY} LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib)
