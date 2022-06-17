#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>
#include <sys/syslog.h>

int main()
{
   openlog("test", LOG_PID, LOG_USER);
   syslog(LOG_DEBUG, "TEST gfsaegsdgsdgsdg");
   closelog();
   return 0; 
}
