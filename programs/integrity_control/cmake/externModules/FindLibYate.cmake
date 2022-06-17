include(FindPackageHandleStandardArgs)
if(LIB_YATE_INCLUDE_DIR AND LIB_YATE_LIBRARIES)
   set(LibYate_FIND_QUIETLY TRUE)
endif(LIB_YATE_INCLUDE_DIR AND LIB_YATE_LIBRARIES)

find_path(LIB_YATE_INCLUDE_DIR yatecbase.h HINTS  /usr/include/yate/ /usr/local/include/yate/ )
find_library(LIB_YATE_LIBRARIES NAMES libyate.so libyateqt4.so HINTS /usr/lib/ /usr/local/lib/)
find_package_handle_standard_args(LibYate LIB_YATE_LIBRARIES LIB_YATE_INCLUDE_DIR)
mark_as_advanced(LIB_YATE_LIBRARIES)