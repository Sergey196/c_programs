include(FindPackageHandleStandardArgs)
if(LIB_USB_INCLUDE_DIR AND LIB_USB_LIBRARIES)
   set(LibUsb_FIND_QUIETLY TRUE)
endif(LIB_USB_INCLUDE_DIR AND LIB_USB_LIBRARIES)
   
find_path(LIB_USB_INCLUDE_DIR libusb.h HINTS  /include/libusb-1.0/ /usr/local/include/libusb-1.0 /usr/include/libusb-1.0)
find_library(LIB_USB_LIBRARIES libusb-1.0.so HINTS /usr/lib/ /usb/lib64 /usr/local/lib)
find_package_handle_standard_args(LibUsb DEFAULT_MSG LIB_USB_LIBRARIES LIB_USB_INCLUDE_DIR)
mark_as_advanced(LIB_USB_LIBRARIES)
