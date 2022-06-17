###############################################
set (PROJECT_SERVER server)
project(${PROJECT_SERVER})

###############################################
cmake_minimum_required(VERSION 3.16.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################
set(RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)

###############################################
set(LIBRARIES_PROJECT_CLIENT
   lib_ftp_server
)

set(LIBRARIES_PROJECT_CLIENT_NAME
   _ftp_server
)


###############################################
foreach(LIBRARY ${LIBRARIES_PROJECT_CLIENT_NAME})
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

add_executable(${PROJECT_SERVER} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_SERVER} ${LIBRARIES_PROJECT_CLIENT_NAME} )
set_target_properties(${PROJECT_SERVER} PROPERTIES LINK_FLAGS "-g -pg") #для профилировщика gprof

install(TARGETS ${PROJECT_SERVER} RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})

 
