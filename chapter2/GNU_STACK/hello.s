
.arch armv8-a
.text
.global _start
_start:
	mov X0, #1   		//1 = stdout
	adr X1, helloworld  	//string to print
	mov X2, #12		//string length
	mov X8, #64		//sys_write
	svc 0
	ret
helloworld:
.ascii "Hello World\n"

