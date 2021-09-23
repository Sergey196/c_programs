set (PROJECT_LIB_FTP _ftp_server)
project(${PROJECT_LIB_FTP})
cmake_minimum_required(VERSION 3.16.0)
###############################################


set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
###############################################

set(LIBRARIES_LIB_ISHTAR_FIFO
)

###############################################
set(LIBRARIES_LIB_ISHTAR_FIFO_NAME
)

###############################################
foreach(LIBRARY ${LIBRARIES_TEMP_LIB})   
   include_directories(${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/ ${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/include)
   message(${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/)
endforeach(LIBRARY)
###############################################
foreach(LIB_INC ${LIBRARIES_INCLUDE})
   include_directories(${LIB_INC})
endforeach(LIB_INC)
###############################################

set(HEADERS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
###############################################
include_directories(${HEADERS_DIRECTORY} ${SOURCES_DIRECTORY} )
###############################################
set(HEADERS
   ${HEADERS_DIRECTORY}/lib_ftp_constants.h
   ${HEADERS_DIRECTORY}/tserveriface.h
   ${HEADERS_DIRECTORY}/tsocket.h
   ${HEADERS_DIRECTORY}/tlogic.h
)

##############################################

set(SOURCES
   ${SOURCES_DIRECTORY}/tserveriface.cpp
   ${SOURCES_DIRECTORY}/tsocket.cpp
   ${SOURCES_DIRECTORY}/tlogic.cpp
)

##########################################################################################
include_directories(${LIB_GOST_INCLUDE_DIR})
##########################################################################################

SET(CMAKE_CXX_FLAGS -lssl)

add_library (${PROJECT_LIB_FTP} SHARED ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT_LIB_ISHTAR_FIFO} PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib)
###############################################
target_link_libraries(${PROJECT_LIB_FTP} ${LIBRARIES_LIB_ISHTAR_FIFO_NAME} ${LIB_GOST_LIBRARIES})
install(TARGETS ${PROJECT_LIB_FTP} LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib)
