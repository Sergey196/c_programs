###############################################
set (PROJECT_NAME pack)
project(${PROJECT_NAME})

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
set(LIBRARIES_PROJECT
   lib_pack
)

set(LIBRARIES_PROJECT_NAME
   _pack
)


###############################################
foreach(LIBRARY ${LIBRARIES_PROJECT})
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
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES_PROJECT_NAME} )
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-g -pg") #для профилировщика gprof

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})

 
