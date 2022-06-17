#Проверка версии ОС - если МСВС 14, то ставим версию QT 3.3.8
#Если любая другая ОС - выставляем ту версию 3его Qt, которую нашли
#Если не нашли никакую - ставим 3.3
MACRO(set_qt3_mcbc_14 QT_DESIRED_VERSION)
   set(UNAME_A_CMD uname -a)
   set(VNIINS_GREP_CMD grep "vniins42")
   set(GREP_2008_CMD grep "2008")
   set(GREP_2010_CMD grep "2010")
   set(GREP_2011_CMD grep "2011")
   execute_process(COMMAND ${UNAME_A_CMD} COMMAND ${VNIINS_GREP_CMD} OUTPUT_VARIABLE UNAME_A_VNIINS_STR)

   string(COMPARE NOTEQUAL "${UNAME_A_VNIINS_STR}" "" IS_MCBC)

# message(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!IS_MCBC=${IS_MCBC})

   if(IS_MCBC)
      execute_process(COMMAND ${UNAME_A_CMD} COMMAND ${GREP_2008_CMD} OUTPUT_VARIABLE UNAME_A_2008_STR)
# message(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!UNAME_A_2008_STR=${UNAME_A_2008_STR})
      string(COMPARE NOTEQUAL "${UNAME_A_2008_STR}" "" IS_MCBC_14)

      if(NOT IS_MCBC_14)
         execute_process(COMMAND ${UNAME_A_CMD} COMMAND ${GREP_2010_CMD} OUTPUT_VARIABLE UNAME_A_2010_STR)
# message(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!UNAME_A_2010_STR=${UNAME_A_2010_STR})
         string(COMPARE NOTEQUAL "${UNAME_A_2010_STR}" "" IS_MCBC_14)
      endif(NOT IS_MCBC_14)

      execute_process(COMMAND ${UNAME_A_CMD} COMMAND ${GREP_2011_CMD} OUTPUT_VARIABLE UNAME_A_2011_STR)
# message(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!UNAME_A_2011_STR=${UNAME_A_2010_STR})
      string(COMPARE NOTEQUAL "${UNAME_A_2011_STR}" "" IS_MCBC_16)
   endif(IS_MCBC)

   if(IS_MCBC_14 OR IS_MCBC_16)
      set_qt3_version(${QT_DESIRED_VERSION})
   else(IS_MCBC_14 OR IS_MCBC_16)
      find_package(Qt3 REQUIRED)
      string(COMPARE EQUAL ${QT_INCLUDE_DIR} "QT_INCLUDE_DIR-NOTFOUND" QT_3_NOTFOUND)
      if(QT_3_NOTFOUND)
         set_qt3_version(3.3)
         set(QT_LIBRARIES 
         /usr/lib/qt-3.3/lib/libqassistantclient.a
         /usr/lib/qt-3.3/lib/libqt-mt.so)
      endif(QT_3_NOTFOUND)
   endif(IS_MCBC_14 OR IS_MCBC_16)
#    message(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!IS_MCBC_14=${QT_INCLUDE_DIR})
ENDMACRO(set_qt3_mcbc_14)

MACRO(set_qt3_version QT_VERSION)
   set(QT_INCLUDE_DIR /usr/lib/qt-${QT_VERSION}/include)
   set(QT_UIC_EXECUTABLE /usr/lib/qt-${QT_VERSION}/bin/uic)
   set(QT_MOC_EXECUTABLE /usr/lib/qt-${QT_VERSION}/bin/moc)
   set(QT_MT_REQUIRED TRUE)
   set(QT_DEFINITIONS "-DQT_THREAD_SUPPORT")
   set(QT_LIBRARIES 
   /usr/lib/qt-${QT_VERSION}/lib/libqassistantclient.so
   /usr/lib/qt-${QT_VERSION}/lib/libqt-mt.so)
ENDMACRO(set_qt3_version)
