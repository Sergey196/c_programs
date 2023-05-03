

#include <sys/statvfs.h>
#include <iostream>

int main()
{
   struct statvfs stat;
   if(statvfs("/home/utkinsv/", &stat) != 0)
   {
      return -1;
   }
   std::cout << "TEST1 = " << stat.f_bsize << std::endl;
   std::cout << "TEST2 = " << stat.f_bavail << std::endl;
   std::cout << "TEST3 = " << (stat.f_bsize * stat.f_bavail) << std::endl;
   return 0; 
}
