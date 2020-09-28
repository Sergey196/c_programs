#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <thread>

#define SHARED_MEMORY_OBJECT_NAME "my_shared_memory"
#define SHARED_MEMORY_OBJECT_SIZE 100



int main () {
    int shm;
    char *addr;
    std::string str = "TEST0";
    
    if ( (shm = shm_open(SHARED_MEMORY_OBJECT_NAME, O_CREAT|O_RDWR, 0777)) == -1 ) {
        perror("shm_open");
        return 1;
    }
    
    if (ftruncate(shm, SHARED_MEMORY_OBJECT_SIZE+1) == -1) 
    {
       perror("ftruncate");
       return 1;
    }
    
    addr = (char *)mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    if ( addr == (char*)-1 ) {
        perror("mmap");
        return 1;
    }

    std::thread readMy([&](){
       while(true)
       {
          std::cout << "TEST = " << str << std::endl;
          
          memcpy(addr, str.c_str(), str.length());
          sleep(1);
       }
    });
    
    
    while(true)
    {
        
        
    }
    
    munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
    
    close(shm);
    
    return 0;
}
