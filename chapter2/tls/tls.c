#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <stdlib.h>

//omit checking code for clarity
#define CHECK (0)

__thread int tls_main_a = 3;

extern  __thread int tls_initial_a;
extern int get_value();

int main() 
{ 
    int *ptr;
    void *handle;
    char *error;

    ptr = &tls_main_a;              //local-exec
    ptr = &tls_initial_a;           //initial-exec

    handle = dlopen("libbar.so", RTLD_LAZY);
#if CHECK
    if (!handle) 
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror();    /* Clear any existing error */   
#endif
    ptr = (int *)dlsym(handle, "tls_dyn_a");    
#if CHECK
    error = dlerror();
    if (error != NULL) 
    {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
#endif
    printf("tls_dyn_a = 0x%x\n", *ptr);

    dlclose(handle);

    return 0; 
}