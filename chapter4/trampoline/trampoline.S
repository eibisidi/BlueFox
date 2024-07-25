#include <asm/unistd.h>

.section .textfar
.global target
_target:            //_target is at 0x10000000, see linker.ld
    ret

.section .text
.global _start
_start:
    bl  _target     //_target is too far away

    mov x0, #0
    mov x8, __NR_exit
    svc 0
