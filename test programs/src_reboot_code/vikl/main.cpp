#include <unistd.h>
#include <stdlib.h>

int main()
{
    seteuid(0);
    setuid(0);
    setegid(0);
    setgid(0);
    system("/sbin/poweroff");
    return 0;
}
