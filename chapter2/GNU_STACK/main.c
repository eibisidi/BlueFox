#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_CODE (0x40)

//read text instructions from hello.bin
int read_code_from_file(char *buffer, ssize_t len)
{
	int fd, n;

	fd = open("hello.bin", O_RDONLY);
	if (fd < 0) {
		return -1;
	}
	n = read(fd, buffer, len);

	if (n < 0) {
		return n;
	}

	close(fd);

	return n;
}

int main()
{
	int i, ret;
	char code[MAX_CODE];

	ret = read_code_from_file(code, MAX_CODE);
	if (ret < 0) {
		printf("read code error=%d\n", ret);
		return -1;
	}

	printf("read %dB codes:\n", ret);
	for (i = 0; i < ret; ++i) {
		printf("%02x ", code[i]);
	}

	printf("\nExecute code in stack.\n");

	asm volatile(
		     "blr %0 \n"
		     :
		     :"r"(code)
		     :"cc", "memory"
		    );

	pause();
	return 0;
}

