###############################################
set (PROJECT_PROTOCOL_UTP protocol_utp)
project(${PROJECT_PROTOCOL_UTP})
###############################################
cmake_minimum_required(VERSION 3.16.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
###############################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)


set(LIBRARIES
  lib_ftp_server
)

set(RUNTIME_PROGRAMMS
  client
  server
)

SET(CMAKE_CXX_FLAGS -pthread)

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

