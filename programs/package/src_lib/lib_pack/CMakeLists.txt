set (PROJECT_LIB_NAME _pack)
project(${PROJECT_LIB_NAME})
cmake_minimum_required(VERSION 3.7)
###############################################
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
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
set(TESTS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
###############################################
include_directories(${HEADERS_DIRECTORY} ${SOURCES_DIRECTORY} ${TESTS_DIRECTORY})
###############################################
set(HEADERS
   ${HEADERS_DIRECTORY}/lib_protocol_constants.h
)

##############################################

set(SOURCES
   ${SOURCES_DIRECTORY}/main.cpp
)

##########################################################################################

add_library (${PROJECT_LIB_NAME} SHARED ${HEADERS} ${SOURCES})

set_target_properties(${PROJECT_LIB_NAME} PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib)
###############################################
target_link_libraries(${PROJECT_LIB_NAME} ${LIBRARIES_LIB_ISHTAR_FIFO_NAME} ${LIB_GOST_LIBRARIES})
install(TARGETS ${PROJECT_LIB_NAME} LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib)
