cmake_minimum_required(VERSION 2.8)
set (PROJECT_NAME user_no_gui)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(HEADERS_DIRECTORY ${CMAKE_SOURCE_DIR}/include)
set(SOURCES_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${HEADERS_DIRECTORY} ${SOURCES_DIRECTORY})

set(QTHEADERS
   ${HEADERS_DIRECTORY}/tmainwindow.h
)  

set(SOURCES
   ${SOURCES_DIRECTORY}/main.cpp
   ${SOURCES_DIRECTORY}/tmainwindow.cpp
)

qt5_wrap_cpp (MOC_SOURCES ${QTHEADERS})
add_definitions(-DSTRESSTEST  -pipe -O2 -Wall -W -Werror=sign-compare -ggdb -std=c++11 -fPIC -D_REENTRANT)

add_executable(${PROJECT_NAME} ${MOC_SOURCES} ${QTHEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5PrintSupport_LIBRARIES})
###############################################
include(${CMAKE_SOURCE_DIR}/debGenerate.cmake)
###############################################
