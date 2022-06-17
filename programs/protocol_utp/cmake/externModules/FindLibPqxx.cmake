include(FindPackageHandleStandardArgs)
if(LIB_PQXX_INCLUDE_DIR AND LIB_PQXX_LIBRARIES)
   set(LibPqxx_FIND_QUIETLY TRUE)
endif(LIB_PQXX_INCLUDE_DIR AND LIB_PQXX_LIBRARIES)

find_path(LIB_PQXX_INCLUDE_DIR pqxx HINTS /usr/include/pqxx/ /usr/local/include/pqxx/ )
find_library(LIB_PQXX_LIBRARIES NAMES libpqxx.so libpqxx.a HINTS /usr/lib/ /usr/local/lib/)
find_package_handle_standard_args(LibPqxx LIB_PQXX_LIBRARIES LIB_PQXX_INCLUDE_DIR)
mark_as_advanced(LIB_PQXX_LIBRARIES)

