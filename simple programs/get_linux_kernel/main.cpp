#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/utsname.h>

int main(void) {

    struct utsname buffer;
    char *p;
    long ver[16];
    int i=0;

    errno = 0;
    if (uname(&buffer) != 0) {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    printf("system name = %s\n", buffer.sysname);
    printf("node name   = %s\n", buffer.nodename);
    printf("release     = %s\n", buffer.release);
    printf("version     = %s\n", buffer.version);
    printf("machine     = %s\n", buffer.machine);
    printf("domain name = %s\n", buffer.domainname);

    p = buffer.release;
    printf("Full name %s\n", p);
    
    while (*p) {
        if (isdigit(*p)) {
            ver[i] = strtol(p, &p, 10);
            i++;
        } else {
            p++;
        }
    }

    printf("Kernel %d Major %d Minor %d Patch %d\n", ver[0], ver[1], ver[2], ver[3]);

    return EXIT_SUCCESS;
} 
