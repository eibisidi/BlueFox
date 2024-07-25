#include <stdio.h>

extern void foo();  //foo is a weak symbol in libfoo.so
extern void bar();  //bar is a weak aliase in libfoo.so

void foo()
{//overrides foo() defined in libfoo.so
    printf("%s:%s is called\n", __FILE__, __FUNCTION__);
}

int main()
{
    foo();
    bar();
    return 0;
}