extern interruptHandler
global isr54

section .text
isr54:
    cli
    push byte 0 ; The error code
    push byte 54 ; The ISR number
    jmp interruptHandler
