extern interruptHandler
global isr58

section .text
isr58:
    cli
    push byte 0 ; The error code
    push byte 58 ; The ISR number
    jmp interruptHandler
