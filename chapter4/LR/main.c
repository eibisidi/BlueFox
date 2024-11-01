#include <stdio.h>

void callee()
{
	void *ret_ip;
	ret_ip = __builtin_return_address(2); //level > 0 returns XZR
	printf("ret_ip=0x%p\n", ret_ip);
}

void caller()
{
	void *ret_ip;
	ret_ip = __builtin_return_address(1); //level > 0 returns XZR
	printf("ret_ip=0x%p\n", ret_ip);
	callee();
}

int main()
{
	void *ret_ip;
	ret_ip = __builtin_return_address(0); //level == 0 returns LR(X30)
	printf("ret_ip=0x%p\n", ret_ip);
	caller();
	return 0;
}
