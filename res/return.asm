    .global _start
    .section .text

_start:
    mov $0x3c, %rax
    mov $0x27, %rdi
    syscall
