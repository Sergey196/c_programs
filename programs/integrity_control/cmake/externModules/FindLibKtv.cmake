include(FindPackageHandleStandardArgs)

if(LIB_KTV_INCLUDE_DIR AND LIB_KTV_LIBRARIES)
   set(LibKtv_FIND_QUIETLY TRUE)
endif(LIB_KTV_INCLUDE_DIR AND LIB_KTV_LIBRARIES)

find_path(LIB_KTV_INCLUDE_DIR ktv.h HINTS  /opt/spo/oks/include/libktv/ /usr/include/libktv/ /usr/local/include/libktv/ )
find_library(LIB_KTV_LIBRARIES NAMES libktv.so HINTS /opt/spo/oks/lib /usr/lib/ /usr/local/lib/)
find_package_handle_standard_args(LibKtv LIB_KTV_LIBRARIES LIB_KTV_INCLUDE_DIR)
mark_as_advanced(LIB_KTV_LIBRARIES)
