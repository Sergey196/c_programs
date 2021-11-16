cmake_minimum_required(VERSION 3.16)
set (SEA_BATTLE sea_battle)
project(${SEA_BATTLE} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(HEADERS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/include)
set(SOURCES_DIRECTORY ${CMAKE_SOURCE_DIR}/src/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${SOURCES_DIRECTORY} ${HEADERS_DIRECTORY})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(HEADERS
   ${HEADERS_DIRECTORY}/maingui.h
   ${HEADERS_DIRECTORY}/constants.h
   ${HEADERS_DIRECTORY}/cell.h
   ${HEADERS_DIRECTORY}/controller.h
   ${HEADERS_DIRECTORY}/logic.h
   ${HEADERS_DIRECTORY}/ship.h
   ${HEADERS_DIRECTORY}/pipconnectplayers.h
)

set(SOURCES
   ${SOURCES_DIRECTORY}/main.cpp
   ${SOURCES_DIRECTORY}/cell.cpp
   ${SOURCES_DIRECTORY}/controller.cpp
   ${SOURCES_DIRECTORY}/logic.cpp
   ${SOURCES_DIRECTORY}/maingui.cpp
   ${SOURCES_DIRECTORY}/ship.cpp
   ${SOURCES_DIRECTORY}/pipconnectplayers.cpp
)
add_executable(${SEA_BATTLE} ${HEADERS} ${SOURCES})
target_link_libraries(${SEA_BATTLE} PRIVATE Qt5::Widgets)

