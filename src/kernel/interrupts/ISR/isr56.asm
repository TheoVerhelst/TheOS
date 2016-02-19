extern interruptHandler
global isr56

section .text
isr56:
    cli
    push byte 0 ; The error code
    push byte 56 ; The ISR number
    jmp interruptHandler
