#include <stdio.h>

int __attribute__((constructor)) init(int argc, char **argv, char **ev)
{
    int i;
    char *p;
    printf("------constructor------\n");
    //show command line arguments
    for (i = 0; i < argc; ++i)
        printf("arg[%d]=%s\n", i, argv[i]);
    
    //show environment variables
    for (i = 0, p = ev[0]; p; ++i, p = ev[i])
    {
        printf("env[%d]:%s\n", i, p);
    }

    return 0;
}

void __attribute__((destructor)) fini() 
{
    printf("------destructor------\n");
}

int main(int argc, char **argv)
{
    int i;
    printf("------main------\n");
     for (i = 0; i < argc; ++i)
        printf("arg[%d]=%s\n", i, argv[i]);
    return 0;
}