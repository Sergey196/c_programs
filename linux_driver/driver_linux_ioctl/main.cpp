#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>

#define MCB_IOC_MAGIC  'm'

#define ADD_1 0
#define ADD_2 1

#define MCB_IOCswicwrite    _IOW(MCB_IOC_MAGIC, ADD_1, uint64_t)

int main()
{
   int hdl = open("/dev/scull", O_RDONLY); 
   if (hdl < 0)
   {
      std::cout << "TEST" << std::endl; 
      return -1;
   }
   
   int val = 5;
   return ioctl(hdl, ADD_2, val);
}
