cmake_minimum_required(VERSION 2.8)
set (PROJECT_NAME terminal)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(HEADERS_DIRECTORY ${CMAKE_SOURCE_DIR}/include)
set(SOURCES_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
include_directories(${HEADERS_DIRECTORY} ${SOURCES_DIRECTORY})


set(HEADERS
   ${HEADERS_DIRECTORY}/baseitem.h
)

set(SOURCES
   ${SOURCES_DIRECTORY}/main.cpp
)

add_definitions(-DSTRESSTEST  -pipe -O2 -Wall -W -Werror=sign-compare -ggdb -std=c++11 -fPIC -D_REENTRANT)

add_executable(${PROJECT_NAME} ${MOC_SOURCES} ${HEADERS} ${SOURCES})

