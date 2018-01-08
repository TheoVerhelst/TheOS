extern interruptHandler
global isr3

section .text
isr3:
    cli
    push byte 0 ; The error code
    push byte 3 ; The ISR number
    jmp interruptHandler
