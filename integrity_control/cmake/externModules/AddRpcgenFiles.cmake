#Макрос создания заголовочного h файла из исходного x-файла с использованием
#команды rpcgen -h
MACRO(add_rpcgen_h_file RPC_DIRECTORY HEADERS_DIRECTORY filename)
   set(RPCGEN_H rpcgen -h)
   execute_process(COMMAND ${RPCGEN_H} ${RPC_DIRECTORY}/${filename}.x OUTPUT_FILE ${HEADERS_DIRECTORY}/${filename}.h )

   set(MAKE_CLEAN_RPCGEN_H ${MAKE_CLEAN_RPCGEN_H};${HEADERS_DIRECTORY}/${filename}.h)
   set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${MAKE_CLEAN_RPCGEN_H}")
ENDMACRO(add_rpcgen_h_file)  


MACRO(add_rpcgen_l_file RPC_DIRECTORY SOURCES_DIRECTORY filename)
   set(RPCGEN_L rpcgen -l)
   set(SED_LOCAL_PATH sed s,${RPC_DIRECTORY}/${filename},${filename},)
   execute_process(COMMAND ${RPCGEN_L} ${RPC_DIRECTORY}/${filename}.x COMMAND ${SED_LOCAL_PATH} OUTPUT_FILE ${SOURCES_DIRECTORY}/${filename}_clnt.cpp )

   set(MAKE_CLEAN_RPCGEN_L ${MAKE_CLEAN_RPCGEN_L};${SOURCES_DIRECTORY}/${filename}_clnt.cpp)
   set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${MAKE_CLEAN_RPCGEN_L}")
ENDMACRO(add_rpcgen_l_file)  

MACRO(add_rpcgen_c_file RPC_DIRECTORY SOURCES_DIRECTORY filename)
   set(RPCGEN_C rpcgen -c)
   set(SED_LOCAL_PATH sed s,${RPC_DIRECTORY}/${filename},${filename},)
   set(GREP_BUF grep -v "register int32_t \\*buf;")
   execute_process(COMMAND ${RPCGEN_C} ${RPC_DIRECTORY}/${filename}.x COMMAND ${SED_LOCAL_PATH} COMMAND ${GREP_BUF} OUTPUT_FILE ${SOURCES_DIRECTORY}/${filename}_xdr.cpp )

   set(MAKE_CLEAN_RPCGEN_C ${MAKE_CLEAN_RPCGEN_C};${SOURCES_DIRECTORY}/${filename}_xdr.cpp)
   set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${MAKE_CLEAN_RPCGEN_C}")
ENDMACRO(add_rpcgen_c_file) 

MACRO(add_rpcgen_m_file RPC_DIRECTORY SOURCES_DIRECTORY filename)
   set(RPCGEN_M rpcgen -m)
   set(SED_LOCAL_PATH sed s,${RPC_DIRECTORY}/${filename},${filename},)
   execute_process(COMMAND ${RPCGEN_M} ${RPC_DIRECTORY}/${filename}.x COMMAND ${SED_LOCAL_PATH} OUTPUT_FILE ${SOURCES_DIRECTORY}/${filename}_svc.cpp )

   set(MAKE_CLEAN_RPCGEN_M ${MAKE_CLEAN_RPCGEN_M};${SOURCES_DIRECTORY}/${filename}_svc.cpp)
   set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${MAKE_CLEAN_RPCGEN_M}")
ENDMACRO(add_rpcgen_m_file) 

MACRO(add_rpcgen_Ss_file RPC_DIRECTORY SOURCES_DIRECTORY filename)
   set(RPCGEN_SS rpcgen -Ss)
   set(SED_LOCAL_PATH sed s,${RPC_DIRECTORY}/${filename},${filename},)
   execute_process(COMMAND ${RPCGEN_SS} ${RPC_DIRECTORY}/${filename}.x COMMAND ${SED_LOCAL_PATH} OUTPUT_FILE ${SOURCES_DIRECTORY}/${filename}_skel.cpp )

   set(MAKE_CLEAN_RPCGEN_M ${MAKE_CLEAN_RPCGEN_SS};${SOURCES_DIRECTORY}/${filename}_skel.cpp)
   set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${MAKE_CLEAN_RPCGEN_SS}")
ENDMACRO(add_rpcgen_Ss_file) 
