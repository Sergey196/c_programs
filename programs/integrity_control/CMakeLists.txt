###############################################
set (PROJECT_INTEGRITY_CONTROL integrity_control)
project(${PROJECT_INTEGRITY_CONTROL})
cmake_minimum_required(VERSION 3.7)

###############################################
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/externModules)
###############################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)


set(LIBRARIES
  lib_integrity
)

set(RUNTIME_PROGRAMMS
  ic_unit
)

message(${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION})
###############################################
foreach(LIBRARY ${LIBRARIES})
   add_subdirectory(${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY} ${CMAKE_SOURCE_DIR}/build/${LIBRARY})
   include_directories(${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/include/ ${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY})
endforeach(LIBRARY)
###############################################
foreach(PROGRAMM ${RUNTIME_PROGRAMMS})
   add_subdirectory(${CMAKE_SOURCE_DIR}/src/${PROGRAMM} ${CMAKE_SOURCE_DIR}/build/${PROGRAMM})
   include_directories(${CMAKE_SOURCE_DIR}/src/${PROGRAMM}/include/)   
endforeach(PROGRAMM)
###############################################

