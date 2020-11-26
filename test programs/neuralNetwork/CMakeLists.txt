cmake_minimum_required(VERSION 2.8)
project(neuralnetwork)

set(HEADERS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/inclide)
set(SOURCES_DIRECTORY ${CMAKE_SOURCE_DIR}/src/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories(${HEADERS_DIRECTORY} ${SOURCES_DIRECTORY})

set(HEADERS
   ${HEADERS_DIRECTORY}/perceptron.h
)

set(SOURCES
   ${SOURCES_DIRECTORY}/main.cpp
   ${SOURCES_DIRECTORY}/perceptron.cpp
)

add_executable(neuralnetwork ${HEADERS} ${SOURCES} )


