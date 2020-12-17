cmake_minimum_required(VERSION 2.6)

set (SEA_BATTLE sea_battle)
set(HEADERS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/include)
set(SOURCES_DIRECTORY ${CMAKE_SOURCE_DIR}/src/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

project(${SEA_BATTLE})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${SOURCES_DIRECTORY} ${HEADERS_DIRECTORY})

set(QTHEADERS
   ${HEADERS_DIRECTORY}/maingui.h
)

set(HEADERS
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

set (CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

qt5_wrap_cpp (MOC_SOURCES ${QTHEADERS})

add_executable(${SEA_BATTLE} ${MOC_SOURCES} ${HEADERS} ${SOURCES})
target_link_libraries(${SEA_BATTLE} ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES})
