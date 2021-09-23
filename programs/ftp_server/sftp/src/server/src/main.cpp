
#include <iostream>


// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <fcntl.h>
#include "lib_ftp_constants.h"
#include "tserveriface.h"

int main() 
{ 
    _ftp_server::TServerIface *iface = new _ftp_server::TServerIface(); 
    _ftp_server::TConfig info;
    iface->init(info);
    iface->start();

    return 0; 
}  
