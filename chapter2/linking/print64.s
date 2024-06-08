.arch armv8-a
.text
.global main
main:
    ldr x0, =MYSTRING
    bl printf
    mov x0, #0
    bl exit

.section .rodata
.balign 8
MYSTRING:
.asciz "Hello world\n"

