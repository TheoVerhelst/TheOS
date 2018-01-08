extern interruptHandler
global isr61

section .text
isr61:
    cli
    push byte 0 ; The error code
    push byte 61 ; The ISR number
    jmp interruptHandler
