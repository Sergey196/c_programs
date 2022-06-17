#Вспомогательный макрос для создания заголовочного файла
MACRO(set_project_revision_hdr PROJECTNAME projectname MAJOR_VERSION MINOR_VERSION PATH_VERSION)
   file(WRITE ${HEADERS_DIRECTORY}/${projectname}_revision.h "#ifndef ${PROJECTNAME}_REVISION_H "\n)
   file(APPEND ${HEADERS_DIRECTORY}/${projectname}_revision.h "#define ${PROJECTNAME}_REVISION_H "\n)
   file(APPEND ${HEADERS_DIRECTORY}/${projectname}_revision.h "   #define ${PROJECTNAME}_MAJOR_VERSION "${MAJOR_VERSION}\n)
   file(APPEND ${HEADERS_DIRECTORY}/${projectname}_revision.h "   #define ${PROJECTNAME}_MINOR_VERSION "${MINOR_VERSION}\n)
   file(APPEND ${HEADERS_DIRECTORY}/${projectname}_revision.h "   #define ${PROJECTNAME}_PATH_VERSION "${PATH_VERSION}\n)
   file(APPEND ${HEADERS_DIRECTORY}/${projectname}_revision.h "#endif"\n)
   file(APPEND ${HEADERS_DIRECTORY}/${projectname}_revision.h "\n")
ENDMACRO(set_project_revision_hdr)

#Создание файла с текущим номером версии подпроекта
MACRO(set_project_version_svn PROJECTNAME projectname MAJOR_VERSION MINOR_VERSION PATH_VERSION)
   set(CAT_CMD cat ${RPM_DIRECTORY}/${projectname}.spec.in)
   set(REPLACE_MAJOR sed s/MAJOR_VERSION/${MAJOR_VERSION}/g)
   set(REPLACE_MINOR sed s/MINOR_VERSION/${MINOR_VERSION}/g)
   set(ACCEPT_CMD ${RPM_DIRECTORY}/${projectname}.spec)


   find_file(IS_SVN_WORKING_COPY entries ${CMAKE_SOURCE_DIR}/.svn)
#   message(IS_SVN_WORKING_COPY=${IS_SVN_WORKING_COPY})
#   message(DIR=${CMAKE_SOURCE_DIR})
   if (${IS_SVN_WORKING_COPY} STREQUAL "IS_SVN_WORKING_COPY-NOTFOUND")
      message("It isn't a svn working copy!")
   else (${IS_SVN_WORKING_COPY} STREQUAL "IS_SVN_WORKING_COPY-NOTFOUND")
   
      find_package(Subversion)
   #    message(${Subversion_FOUND})
message(Subversion_DIR=${Subversion_DIR})
      if(Subversion_FOUND)
         EXECUTE_PROCESS(COMMAND ${Subversion_SVN_EXECUTABLE} --version --quiet    #Проверяем версию клиента
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}                                     #сам cmake проверяет ее
         OUTPUT_VARIABLE Subversion_VERSION_SVN                                    #в Subversion_WC_INFO
         OUTPUT_STRIP_TRAILING_WHITESPACE)                                         #и если что-то не так 
   #       message(${Subversion_VERSION_SVN})
         string(REGEX REPLACE "\\...$" "" SVN_NUM_VERSION ${Subversion_VERSION_SVN})   #вываливается с ошибкой
   #       message(${SVN_NUM_VERSION})                                                  #здесь обходим этот момент
         string(COMPARE EQUAL ${SVN_NUM_VERSION} "1.6" IS_SVN_1_6)
         message(IS_SVN_1_6 ${IS_SVN_1_6})
         if (IS_SVN_1_6)
            Subversion_WC_INFO(${CMAKE_SOURCE_DIR} svnVersion)
            message(tempSvnVersion_WC_REVISION = ${svnVersion_WC_REVISION})
            set(PATH_VERSION ${svnVersion_WC_REVISION})
            
            set(REPLACE_PATH sed s/PATH_VERSION/${svnVersion_WC_REVISION}/g)
            message(PATH_VERSION ${svnVersion_WC_REVISION})
            set_project_revision_hdr(${PROJECTNAME} ${projectname} ${MAJOR_VERSION} ${MINOR_VERSION} ${svnVersion_WC_REVISION})
#             file(WRITE ${HEADERS_DIRECTORY}/revision.h "#define ${PROJECTNAME}_MAJOR_VERSION "${MAJOR_VERSION}\n)
#             file(APPEND ${HEADERS_DIRECTORY}/revision.h "#define ${PROJECTNAME}_MINOR_VERSION "${MINOR_VERSION}\n)
#             file(APPEND ${HEADERS_DIRECTORY}/revision.h "#define ${PROJECTNAME}_PATH_VERSION "${svnVersion_WC_REVISION}\n)
#             file(APPEND ${HEADERS_DIRECTORY}/revision.h "\n")

            #Обновляем содержимое файла с версией
            execute_process(COMMAND ${CAT_CMD} COMMAND ${REPLACE_MAJOR} COMMAND ${REPLACE_MINOR} COMMAND ${REPLACE_PATH} OUTPUT_FILE ${ACCEPT_CMD} )
         endif (IS_SVN_1_6)
      endif(Subversion_FOUND)
   endif (${IS_SVN_WORKING_COPY} STREQUAL "IS_SVN_WORKING_COPY-NOTFOUND")

   ###############################################
   #Если не смогли создать файл ${projectname}_revision.h в силу отсутствия SVN - создаем его сами со значениями версии, прописанными в файле Version.blocked
   if(NOT EXISTS ${HEADERS_DIRECTORY}/${projectname}_revision.h)
      set_project_revision_hdr(${PROJECTNAME} ${projectname} ${MAJOR_VERSION} ${MINOR_VERSION} ${PATH_VERSION})
#       file(WRITE ${HEADERS_DIRECTORY}/revision.h "#define ${PROJECTNAME}_MAJOR_VERSION "${MAJOR_VERSION}\n)
#       file(APPEND ${HEADERS_DIRECTORY}/revision.h "#define ${PROJECTNAME}_MINOR_VERSION "${MINOR_VERSION}\n)
#       file(APPEND ${HEADERS_DIRECTORY}/revision.h "#define ${PROJECTNAME}_PATH_VERSION "${PATH_VERSION}\n)
#       file(APPEND ${HEADERS_DIRECTORY}/revision.h "\n")
   endif(NOT EXISTS ${HEADERS_DIRECTORY}/${projectname}_revision.h)  
   ############################################### 
   #Если не смогли создать spec файл в силу отсутствия SVN - создаем его сами
   if(NOT EXISTS ${RPM_DIRECTORY}/${projectname}.spec)
      set(REPLACE_PATH sed s/PATH_VERSION/${PATH_VERSION}/g)
      execute_process(COMMAND ${CAT_CMD} COMMAND ${REPLACE_MAJOR} COMMAND ${REPLACE_MINOR} COMMAND ${REPLACE_PATH} OUTPUT_FILE ${ACCEPT_CMD} )
   endif(NOT EXISTS ${RPM_DIRECTORY}/${projectname}.spec)   

set(MAKE_CLEAN_SPECS ${MAKE_CLEAN_SPECS};${RPM_DIRECTORY}/${projectname}.spec)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${MAKE_CLEAN_SPECS}")
ENDMACRO(set_project_version_svn)

