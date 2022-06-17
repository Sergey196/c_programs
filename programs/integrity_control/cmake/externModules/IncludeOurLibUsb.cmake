#Подключение библиотеки libusb из проекта
#проверьте, что есть переменная CMAKE_MINOR_VERSION
MACRO(include_our_lib_usb)
   message("Check libusb")
   find_path( LIB_USB_INCLUDE_DIR libusb.h HINTS ${CMAKE_SOURCE_DIR}/src_lib/libusb/libusb/ )
   find_library(LIB_USB_LIBRARIES NAMES usb-1.0 PATHS ${LIBRARY_OUTPUT_PATH})
   message(LIB_USB_INCLUDE_DIR=${LIB_USB_INCLUDE_DIR})
   message(LIB_USB_LIBRARIES  =${LIB_USB_LIBRARIES})
   if(${LIB_USB_INCLUDE_DIR} STREQUAL "LIB_USB_INCLUDE_DIR-NOTFOUND")
      message("Check libusb ... NOT FOUND")
   else(${LIB_USB_INCLUDE_DIR} STREQUAL "LIB_USB_INCLUDE_DIR-NOTFOUND")
      message("Check libusb ... OK")
   endif(${LIB_USB_INCLUDE_DIR} STREQUAL "LIB_USB_INCLUDE_DIR-NOTFOUND")
   include_directories(${LIB_USB_INCLUDE_DIR})
ENDMACRO(include_our_lib_usb)   

