include(FindPackageHandleStandardArgs)
if(LIB_NET_SNMP_INCLUDE_DIR AND LIB_NET_SNMP_LIBRARIES)
   set(Lib_Net_FIND_QUIETLY TRUE)
endif(LIB_NET_SNMP_INCLUDE_DIR AND LIB_NET_SNMP_LIBRARIES)
   
   find_path(LIB_NET_SNMP_INCLUDE_DIR net-snmp-config.h HINTS /usr/include/net-snmp/)
   find_library(LIB_NET_SNMP_LIBRARIES libnetsnmp.so HINTS /usr/lib/)
   find_package_handle_standard_args(LibNetSnmp DEFAULT_MSG LIB_NET_SNMP_LIBRARIES LIB_NET_SNMP_INCLUDE_DIR)
   mark_as_advanced(LIB_NET_LIBRARIES)