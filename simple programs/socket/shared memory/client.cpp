#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <algorithm>
#include <thread>
#include <string.h>

#define SHARED_MEMORY_OBJECT_NAME "my_shared_memory"
#define SHARED_MEMORY_OBJECT_SIZE 100

int main () {
    int shm;
    char *addr;

    if ( (shm = shm_open(SHARED_MEMORY_OBJECT_NAME, O_RDWR, 0777)) == -1 ) {
        perror("shm_open");
        return 1;
    }

    addr = (char *)mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    if ( addr == (char*)-1 ) {
        perror("mmap");
        return 1;
    }

    printf("Got from shared memory: %s\n", addr);

    
    std::thread readMy([&](){
       while(true)
       {
          printf("Got from shared memory: %s\n", addr);
          sleep(1);
       }
    });
    
    while(true)
    {
        
    }
    
    munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
    
    close(shm);

    shm_unlink(SHARED_MEMORY_OBJECT_NAME);
    
    
    return 0;
}
