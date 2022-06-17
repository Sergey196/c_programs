cmake_minimum_required(VERSION 2.8)
set (PROJECT_NAME mkio)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(HEADERS_DIRECTORY ${CMAKE_SOURCE_DIR}/include)
set(SOURCES_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5PrintSupport_INCLUDE_DIRS} ${HEADERS_DIRECTORY} ${SOURCES_DIRECTORY})

set(QTHEADERS
   ${HEADERS_DIRECTORY}/tmainwindow.h
   ${HEADERS_DIRECTORY}/tcontroller.h
   ${HEADERS_DIRECTORY}/qcustomplot.h
   ${HEADERS_DIRECTORY}/thexspinbox.h
   ${HEADERS_DIRECTORY}/tbinaryspinbox.h
   ${HEADERS_DIRECTORY}/toctalspinbox.h
)  

set(HEADERS
   ${HEADERS_DIRECTORY}/baseitem.h
   ${HEADERS_DIRECTORY}/tlogic.h
)

set(SOURCES
   ${SOURCES_DIRECTORY}/main.cpp
   ${SOURCES_DIRECTORY}/tmainwindow.cpp
   ${SOURCES_DIRECTORY}/tcontroller.cpp
   ${SOURCES_DIRECTORY}/tlogic.cpp
   ${SOURCES_DIRECTORY}/qcustomplot.cpp
   ${SOURCES_DIRECTORY}/thexspinbox.cpp
   ${SOURCES_DIRECTORY}/tbinaryspinbox.cpp
   ${SOURCES_DIRECTORY}/toctalspinbox.cpp
   ${SOURCES_DIRECTORY}/tbitepanel.cpp
)

qt5_wrap_cpp (MOC_SOURCES ${QTHEADERS})
add_definitions(-DSTRESSTEST  -pipe -O2 -Wall -W -Werror=sign-compare -ggdb -std=c++11 -fPIC -D_REENTRANT)

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${MOC_SOURCES} ${QTHEADERS} ${HEADERS} ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${MOC_SOURCES} ${QTHEADERS} ${HEADERS} ${SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5PrintSupport_LIBRARIES})
