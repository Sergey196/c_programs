
#include <cstdio>
#include <sys/statvfs.h>
#include <iostream>

int main(int argc, char* argv[])
{
   if (argc < 2) 
   {
      return -1;
   }
  
   struct statvfs stat;
   statvfs(argv[1], &stat);
   printf("Disk %s: \n", argv[1]);
   printf("\tblock size: %u\n", stat.f_bsize);
   printf("\ttotal no blocks: %i\n", stat.f_blocks);
   printf("\tfree blocks: %i\n", stat.f_bfree);
   long result = stat.f_bsize * stat.f_bavail;
   printf("\tresult: %lu mb\n", result);
   //std::cout << "space " << result << std::endl;
}
