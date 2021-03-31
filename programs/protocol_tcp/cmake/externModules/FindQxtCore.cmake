include(FindPackageHandleStandardArgs)
if(QXT_INCLUDE_CORE_DIR AND QXT_CORE_LIBRARIES)
   set(Qxt_CORE_FIND_QUIETLY TRUE)
endif(QXT_INCLUDE_CORE_DIR AND QXT_CORE_LIBRARIES)
find_path(QXT_INCLUDE_CORE_DIR qxtcore.h HINTS  /usr/local/Qxt/include/QxtCore/)
find_library(QXT_CORE_LIBRARIES libQxtCore.so.0.6.0 HINTS /usr/local/Qxt/lib/)
message(QXT_INCLUDE_CORE_DIR=${QXT_INCLUDE_CORE_DIR} QXT_CORE_LIBRARIES=${QXT_CORE_LIBRARIES} )
find_package_handle_standard_args(Qxt_core DEFAULT_MSG QXT_CORE_LIBRARIES QXT_INCLUDE_CORE_DIR)
mark_as_advanced(QXT_CORE_LIBRARIES)