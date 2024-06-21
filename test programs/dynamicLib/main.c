#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

int main()
{
    void *handle;
    void (*func_print_name)(const char*);

    handle = dlopen("./lib.so", RTLD_LAZY);
    if (!handle) {
        /* fail to load the library */
        fprintf(stderr, "Error: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    *(void**)(&func_print_name) = dlsym(handle, "print_name");
    if (!func_print_name) {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return EXIT_FAILURE;
    }

    func_print_name("TEST");
    dlclose(handle);

    return EXIT_SUCCESS;
} 
