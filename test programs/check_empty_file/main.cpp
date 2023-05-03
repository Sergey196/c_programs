
#include <sys/stat.h>
#include <errno.h>
#include <iostream>

int main()
{
   struct stat stat_record;
   if(stat("file", &stat_record)) {
       std::cout << "TEST error" << std::endl;
   } else if(!stat_record.st_size) {
       std::cout << "TEST file empty" << std::endl;
   } else {
       // File is present and has data so do stuff...
   }
   return 0; 
}

