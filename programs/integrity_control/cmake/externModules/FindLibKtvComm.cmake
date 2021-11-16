include(FindPackageHandleStandardArgs)

if(LIB_KTVCOMM_INCLUDE_DIR AND LIB_KTVCOMM_LIBRARIES)
   set(LibKtvComm_FIND_QUIETLY TRUE)
endif(LIB_KTVCOMM_INCLUDE_DIR AND LIB_KTVCOMM_LIBRARIES)

find_path(LIB_KTVCOMM_INCLUDE_DIR ktvcomm.h HINTS /opt/spo/oks/include/libktvcomm/  /usr/include/libktvcomm/ /usr/local/include/libktvcomm/ )
find_library(LIB_KTVCOMM_LIBRARIES NAMES libktvcomm.so HINTS /opt/spo/oks/lib/ /usr/lib/ /usr/local/lib/)
find_package_handle_standard_args(LibKtvComm LIB_KTVCOMM_LIBRARIES LIB_KTVCOMM_INCLUDE_DIR)
mark_as_advanced(LIB_KTVCOMM_LIBRARIES)
