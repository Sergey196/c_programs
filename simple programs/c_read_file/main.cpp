#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h> 

int main()
{
   FILE *file = fopen("file", "r"); 
   if(file == NULL)
   {
      std::cout << "TEST error open" << std::endl; 
   }
   
   unsigned long fullSize { 0 };
   while(!feof(file))
   {
      char buffer[512]; 
      memset(buffer, 0, sizeof(buffer));
      int size = fread(buffer, sizeof(char), 512, file);
      fullSize += size;
      std::cout << "TEST size " << size << std::endl; 
      std::cout << "TEST size " << fullSize << std::endl; 
   }
   
   fclose(file);
   return 0; 
}
