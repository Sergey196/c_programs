###############################################
set (PROJECT_INTEGRITY_CONTROL integrity_control)
project(${PROJECT_INTEGRITY_CONTROL})
cmake_minimum_required(VERSION 3.7)

###############################################
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
###############################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(RUNTIME_PROGRAMMS
  ic_unit
)

message(${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION})
###############################################
foreach(PROGRAMM ${RUNTIME_PROGRAMMS})
   add_subdirectory(${CMAKE_SOURCE_DIR}/src/${PROGRAMM} ${CMAKE_SOURCE_DIR}/build/${PROGRAMM})
   include_directories(${CMAKE_SOURCE_DIR}/src/${PROGRAMM}/include/)   
endforeach(PROGRAMM)
###############################################

