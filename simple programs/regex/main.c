#include <regex.h>  
#include <stdlib.h>
#include <stdio.h>

int main()
{
   regex_t regex;
   int reti;
   char msgbuf[100];
   
   /* Compile regular expression */
   //reti = regcomp(&regex, "a\\[F\\]", 0); - a[F]
   //reti = regcomp(&regex, "a\\\\b" 	, 0); - - +-*/
   reti = regcomp(&regex, "^([0-9]{1,2}|[1-2][0-9]{2}).([0-9]{1,2}|[1-2][0-9]{2}).([0-9]{1,2}|[1-2][0-9]{2}).([0-9]{1,2}|[1-2][0-9]{2})$", REG_EXTENDED); 
   if(reti) {
      printf("Could not compile regex\n");
      exit(1);
   }
   
   /* Execute regular expression */
   reti = regexec(&regex, "192.168.0.200", 0, NULL, 0);
   if(!reti) {
      printf("Match\n");
   } else if(reti == REG_NOMATCH) {
      printf("No match\n");
   } else {
      printf("Regex match failed: %s\n", msgbuf);
      exit(1);
   }
   
   /* Free memory allocated to the pattern buffer by regcomp() */
   regfree(&regex); 
   return 0;
}
