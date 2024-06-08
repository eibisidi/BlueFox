#include <stdio.h>
__asm__(".symver foo_unversion, foo@");
__asm__(".symver foo_v2,foo@LIB_V2");
__asm__(".symver foo_v3,foo@@LIB_V3");

void foo_unversion()
{
     printf("foo is called\n");
}

void foo_v2(int a)
{
    printf("foo_v2 is called, arg = %d\n", a);
}

void foo_v3(int a, float b)
{
    printf("foo_v3 is called, arg = %d, arg b = %f\n", a, b);
}
