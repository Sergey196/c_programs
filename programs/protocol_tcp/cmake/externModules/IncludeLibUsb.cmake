#Подключение библиотеки libusb-1.0 с проверкой версии cmake
#проверьте, что есть переменная CMAKE_MINOR_VERSION
MACRO(include_lib_usb)
   if (${CMAKE_MINOR_VERSION} LESS 8)
      message("Check libusb")
      find_path( LIB_USB_INCLUDE_DIR libusb.h HINTS /usr/include/libusb-1.0 /usr/local/include/libusb-1.0)
      find_library(LIB_USB_LIBRARIES NAMES usb PATHS /usr/lib/ /usr/local/lib)
      if(${LIB_USB_INCLUDE_DIR} STREQUAL "LIB_USB_INCLUDE_DIR-NOTFOUND")
         message("Check libusb ... NOT FOUND")
      else(${LIB_USB_INCLUDE_DIR} STREQUAL "LIB_USB_INCLUDE_DIR-NOTFOUND")
         message("Check libusb ... OK")
      endif(${LIB_USB_INCLUDE_DIR} STREQUAL "LIB_USB_INCLUDE_DIR-NOTFOUND")
      include_directories(${LIB_USB_INCLUDE_DIR})
   else(${CMAKE_MINOR_VERSION} LESS 8)
      message("Check libusb")
      find_package(LibUsb REQUIRED)
      if(${LIB_USB_INCLUDE_DIR} STREQUAL "LIB_USB_INCLUDE_DIR-NOTFOUND")
         message("Check libusb ... NOT FOUND")
      else(${LIB_USB_INCLUDE_DIR} STREQUAL "LIB_USB_INCLUDE_DIR-NOTFOUND")
         message("Check libusb ... OK")                           
      endif(${LIB_USB_INCLUDE_DIR} STREQUAL "LIB_USB_INCLUDE_DIR-NOTFOUND")
      include_directories(${LIB_USB_INCLUDE_DIR})
   endif(${CMAKE_MINOR_VERSION} LESS 8)
ENDMACRO(include_lib_usb)   
