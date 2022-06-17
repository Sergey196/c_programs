#Подключение библиотек pjsua-api с проверкой версии cmake из нашего проекта
#проверьте, что есть переменная CMAKE_MINOR_VERSION
# 2.6.34-3-generic
MACRO(include_our_lib_pjsip)
   message (${CMAKE_SYSTEM} ">>>>>>>>>>>>>>>>>>>>>>>>")
   message("Check libpjsip")
   find_path( LIB_PJSIP_INCLUDE_DIR NAMES pjsip.h pjsip_ua.h pjsip_simple.h pjsua-lib/pjsua.h HINTS ${CMAKE_SOURCE_DIR}/src_lib/libpjsua/pjsip/include/ )
   find_library(LIB_PJSIPSIMPLE_LIBRARIES libpjsip-simple.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_PJSIPUA_LIBRARIES libpjsip-ua.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_PJSIP_LIBRARIES libpjsip.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_PJSUA_LIBRARIES libpjsua.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_PJSUA2_LIBRARIES libpjsua2.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   if(${LIB_PJSIP_INCLUDE_DIR} STREQUAL "LIB_PJSIP_INCLUDE_DIR-NOTFOUND")
      message("Check libpjsip ... NOT FOUND")
   else(${LIB_PJSIP_INCLUDE_DIR} STREQUAL "LIB_PJSIP_INCLUDE_DIR-NOTFOUND")
      message("Check libpjsip ... OK")
   endif(${LIB_PJSIP_INCLUDE_DIR} STREQUAL "LIB_PJSIP_INCLUDE_DIR-NOTFOUND")
   message(${LIB_PJSIP_INCLUDE_DIR})
   include_directories(${LIB_PJSIP_INCLUDE_DIR})
ENDMACRO(include_our_lib_pjsip)  


MACRO(include_our_lib_pj)
   message (${CMAKE_SYSTEM} ">>>>>>>>>>>>>>>>>>>>>>>>")
   message("Check libpj")
   find_path( LIB_PJ_INCLUDE_DIR NAMES pjlib.h HINTS ${CMAKE_SOURCE_DIR}/src_lib/libpjsua/pjlib/include/ )
   find_library(LIB_PJ_LIBRARIES NAMES libpj.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   if(${LIB_PJ_INCLUDE_DIR} STREQUAL "LIB_PJ_INCLUDE_DIR-NOTFOUND")
      message("Check libpj ... NOT FOUND")
   else(${LIB_PJ_INCLUDE_DIR} STREQUAL "LIB_PJ_INCLUDE_DIR-NOTFOUND")
      message("Check libpj ... OK")
   endif(${LIB_PJ_INCLUDE_DIR} STREQUAL "LIB_PJ_INCLUDE_DIR-NOTFOUND")
   message(${LIB_PJ_INCLUDE_DIR})
   include_directories(${LIB_PJ_INCLUDE_DIR})
ENDMACRO(include_our_lib_pj)  



MACRO(include_our_lib_pjutil)
   message (${CMAKE_SYSTEM} ">>>>>>>>>>>>>>>>>>>>>>>>")
   message("Check libpjutil")
   find_path( LIB_PJUTIL_INCLUDE_DIR NAMES pjlib-util.h HINTS ${CMAKE_SOURCE_DIR}/src_lib/libpjsua/pjlib-util/include/ )
   find_library(LIB_PJUTIL_LIBRARIES NAMES libpjlib-util.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   if(${LIB_PJUTIL_INCLUDE_DIR} STREQUAL "LIB_PJUTIL_INCLUDE_DIR-NOTFOUND")
      message("Check libpjutil ... NOT FOUND")
   else(${LIB_PJUTIL_INCLUDE_DIR} STREQUAL "LIB_PJUTIL_INCLUDE_DIR-NOTFOUND")
      message("Check libpjutil ... OK")
   endif(${LIB_PJUTIL_INCLUDE_DIR} STREQUAL "LIB_PJUTIL_INCLUDE_DIR-NOTFOUND")
   message(${LIB_PJUTIL_INCLUDE_DIR})
   include_directories(${LIB_PJUTIL_INCLUDE_DIR})
ENDMACRO(include_our_lib_pjutil)  


MACRO(include_our_lib_pjmedia)
   message (${CMAKE_SYSTEM} ">>>>>>>>>>>>>>>>>>>>>>>>")
   message("Check pjmedia for astra")
   find_path( LIB_PJMEDIA_INCLUDE_DIR NAMES pjmedia.h pjmedia-codec.h HINTS ${CMAKE_SOURCE_DIR}/src_lib/libpjsua/pjmedia/include/ )
   find_library(LIB_PJMEDIA_LIBRARIES NAMES libpjmedia.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_PJMEDIAA_LIBRARIES NAMES libpjmedia-audiodev.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_PJMEDIAV_LIBRARIES NAMES libpjmedia-videodev.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_PJMEDIAC_LIBRARIES NAMES libpjmedia-codec.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_PJMSDP_LIBRARIES NAMES libpjsdp.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   if(${LIB_PJMEDIA_INCLUDE_DIR} STREQUAL "LIB_PJMEDIA_INCLUDE_DIR-NOTFOUND")
      message("Check pjmedia ... NOT FOUND")
   else(${LIB_PJMEDIA_INCLUDE_DIR} STREQUAL "LIB_PJMEDIA_INCLUDE_DIR-NOTFOUND")
      message("Check pjmedia ... OK")
   endif(${LIB_PJMEDIA_INCLUDE_DIR} STREQUAL "LIB_PJMEDIA_INCLUDE_DIR-NOTFOUND")
   message(${LIB_PJMEDIA_INCLUDE_DIR})
   include_directories(${LIB_PJMEDIA_INCLUDE_DIR})
ENDMACRO(include_our_lib_pjmedia)  



MACRO(include_our_lib_pjnath)
   message (${CMAKE_SYSTEM} ">>>>>>>>>>>>>>>>>>>>>>>>")
   message("Check pjnath for astra")
   find_path( LIB_PJNATH_INCLUDE_DIR NAMES pjnath.h HINTS ${CMAKE_SOURCE_DIR}/src_lib/libpjsua/pjnath/include/ )
   find_library(LIB_PJNATH_LIBRARIES NAMES libpjnath.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   if(${LIB_PJNATH_INCLUDE_DIR} STREQUAL "LIB_PJNATH_INCLUDE_DIR-NOTFOUND")
      message("Check pjnath ... NOT FOUND")
   else(${LIB_PJNATH_INCLUDE_DIR} STREQUAL "LIB_PJNATH_INCLUDE_DIR-NOTFOUND")
      message("Check pjnath ... OK")
   endif(${LIB_PJNATH_INCLUDE_DIR} STREQUAL "LIB_PJNATH_INCLUDE_DIR-NOTFOUND")
   message(${LIB_PJNATH_INCLUDE_DIR})
   include_directories(${LIB_PJNATH_INCLUDE_DIR})
ENDMACRO(include_our_lib_pjnath)  


MACRO(include_our_lib_thirdparty)
   message (${CMAKE_SYSTEM} ">>>>>>>>>>>>>>>>>>>>>>>>")
   message("Check libpjsip for astra")
   #find_path( LIB_THIRD_INCLUDE_DIR pjsua.h HINTS ${CMAKE_SOURCE_DIR}/src_lib/libpjsua/pjsip/include/pjsua-lib/  )
   find_library(LIB_G722_LIBRARIES NAMES libg7221codec.so.2 PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_GSM_LIBRARIES NAMES libgsmcodec.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_ILBC_LIBRARIES NAMES libilbccodec.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_PORTAUDIO_LIBRARIES NAMES libportaudio.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_RESAMPLE_LIBRARIES NAMES libresample.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_SPEEX_LIBRARIES NAMES libspeex.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   find_library(LIB_SRTP_LIBRARIES NAMES libsrtp.so.2  PATHS  ${LIBRARY_OUTPUT_PATH} )
   #if(${LIB_THIRD_INCLUDE_DIR} STREQUAL "LIB_THIRD_INCLUDE_DIR-NOTFOUND")
   #   message("Check libpjsip ... NOT FOUND")
   #else(${LIB_THIRD_INCLUDE_DIR} STREQUAL "LIB_THIRD_INCLUDE_DIR-NOTFOUND")
      message("Check third ... OK")
   #endif(${LIB_THIRD_INCLUDE_DIR} STREQUAL "LIB_THIRD_INCLUDE_DIR-NOTFOUND")
   #message(${LIB_THIRD_INCLUDE_DIR})
   #include_directories(${LIB_THIRD_INCLUDE_DIR})
ENDMACRO(include_our_lib_thirdparty)  







