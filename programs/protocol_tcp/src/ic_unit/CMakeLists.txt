###############################################
set (PROJECT_IC ic)
project(${PROJECT_IC})

###############################################
cmake_minimum_required(VERSION 3.7) 

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
###############################################
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake
${CMAKE_SOURCE_DIR}/cmake/externModules)
set(RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)

###############################################
set(LIBRARIES_PROJECT_IC
lib_protocol
)

set(LIBRARIES_PROJECT_IC_NAME
_protocol
)


###############################################
foreach(LIBRARY ${LIBRARIES_PROJECT_IC})
   include_directories(${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/include/ ${CMAKE_SOURCE_DIR}/build/${LIBRARY})
endforeach(LIBRARY)

###############################################
#Подключение сторонних библиотек
set(LIBRARIES_INCLUDE
)

###############################################
foreach(LIB_INC ${LIBRARIES_INCLUDE})
   include_directories(${LIB_INC})
endforeach(LIB_INC)

###############################################
set(HEADERS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${HEADERS_DIRECTORY} ${SOURCES_DIRECTORY})
###############################################
set(HEADERS
${HEADERS_DIRECTORY}/defines_ic.hpp
)

set(SOURCES
${SOURCES_DIRECTORY}/main.cpp
)

###############################################
#Включение в зависимости только h-ов, чтобы при
#изменении cpp'ов в библиотеках не пересобиралось все подряд
set(ALLHEADERS ${HEADERS})
INCLUDE(IncludeOnlyHeaders)
include_only_headers(${ALLHEADERS})

###############################################
add_definitions(-pipe -O2 -Wall -W -Werror=sign-compare -ggdb -std=c++11 -fPIC -D_REENTRANT)
add_executable(${PROJECT_IC} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_IC} ${LIBRARIES_PROJECT_IC_NAME} )
set_target_properties(${PROJECT_IC} PROPERTIES LINK_FLAGS "-g -pg") #для профилировщика gprof

install(TARGETS ${PROJECT_IC} RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})

 
