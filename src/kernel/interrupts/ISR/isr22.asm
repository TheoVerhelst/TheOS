extern interruptHandler
global isr22

section .text
isr22:
    cli
    push byte 0 ; The error code
    push byte 22 ; The ISR number
    jmp interruptHandler
