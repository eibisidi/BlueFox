#include <stdio.h>

/* Define ALIASNAME as a weak alias for NAME.
   If weak aliases are not available, this defines a strong alias.  */
# define weak_alias(name, aliasname) _weak_alias (name, aliasname)
# define _weak_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((weak, alias (#name))) \
    __attribute_copy__ (name);

void _bar();
weak_alias(_bar, bar);  //create weak aliase bar for _bar

void __attribute__((weak)) foo()
{
    printf("%s:%s is called\n", __FILE__, __FUNCTION__);
}

void _bar()
{
    printf("%s:%s is called\n", __FILE__, __FUNCTION__);
}