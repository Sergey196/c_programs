#include <stdio.h>


int main()
{ 
   char buffer[100]; 
   FILE *ptr = fopen("/opt/test_package/config/conf.txt", "r");  
   if(!ptr) {
      printf("%s", "error\n"); 
      return -1;
   }
   fgets(buffer, sizeof(buffer), ptr);
   fclose(ptr);
   printf("%s", buffer);
   return 0; 
}
