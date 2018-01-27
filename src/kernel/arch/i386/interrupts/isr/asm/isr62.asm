extern interruptHandler
global isr62

section .text
isr62:
    cli
    push byte 0 ; The error code
    push byte 62 ; The ISR number
    jmp interruptHandler
