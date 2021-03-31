include(FindPackageHandleStandardArgs)
if(QXT_INCLUDE_GUI_DIR AND QXT_GUI_LIBRARIES)
   set(Qxt_GUI_FIND_QUIETLY TRUE)
endif(QXT_INCLUDE_GUI_DIR AND QXT_GUI_LIBRARIES)
find_path(QXT_INCLUDE_GUI_DIR qxtgui.h HINTS  /usr/local/Qxt/include/QxtGui/)
find_library(QXT_GUI_LIBRARIES libQxtGui.so.0.6.0 HINTS /usr/local/Qxt/lib/)
message(QXT_INCLUDE_GUI_DIR=${QXT_INCLUDE_GUI_DIR} QXT_GUI_LIBRARIES=${QXT_GUI_LIBRARIES} )
find_package_handle_standard_args(Qxt_gui DEFAULT_MSG QXT_GUI_LIBRARIES QXT_INCLUDE_GUI_DIR)
mark_as_advanced(QXT_GUI_LIBRARIES)

