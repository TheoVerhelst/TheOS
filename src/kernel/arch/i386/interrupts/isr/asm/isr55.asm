extern interruptHandler
global isr55

section .text
isr55:
    cli
    push byte 0 ; The error code
    push byte 55 ; The ISR number
    jmp interruptHandler
