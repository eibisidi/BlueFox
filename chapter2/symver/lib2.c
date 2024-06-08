#include <stdio.h>
__asm__(".symver foo_unversion, foo@");
__asm__(".symver foo_v2,foo@@LIB_V2");

void foo_unversion()
{
     printf("foo is called\n");
}

void foo_v2(int a)
{
    printf("func_v2 is called, arg = %d\n", a);
}

