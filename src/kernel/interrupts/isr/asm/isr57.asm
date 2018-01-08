extern interruptHandler
global isr57

section .text
isr57:
    cli
    push byte 0 ; The error code
    push byte 57 ; The ISR number
    jmp interruptHandler
