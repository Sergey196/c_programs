#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>
#include <sys/syslog.h>

int main()
{
   openlog("TEST", LOG_PID, LOG_USER);
   syslog(LOG_DEBUG, "TEST gfsaegsdgsdgsdg %d", 25);
   closelog();
   return 0; 
}
