
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>

int main()
{

   int status;
   char resSize[50];
   for(int i = 0;i < 1000000; i++)
   {
      std::string command = "./check_journal_size.sh hardware"; 
      FILE *fp = popen(command.c_str(), "r");
      std::cout << "TEST = " << fp << std::endl; 
      
      
      if (fp == NULL)
      {
         std::cout << "NORMAL NULL" << std::endl; 
      }


      while (fgets(resSize, 50, fp) != NULL)
      {
         break;
      }
   
      status = pclose(fp);
      
      if (status == -1) 
      {
         /* Error reported by pclose() */
         std::cout << "Error reported by pclose() "  << std::endl;
      } 
      
      int intSize = atoi(resSize);
      
      if (intSize >= 200)
      {
         std::cout << "CRITICAL" << std::endl; 
      }
      else if (intSize >= 150)
      {
         std::cout << "JS SIZE" << std::endl; 
      }
      else
      {
         std::cout << "NORMAL" << std::endl; 
      }
      sleep(1);
   }
   return 0; 
}
