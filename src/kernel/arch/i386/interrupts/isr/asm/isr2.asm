extern interruptHandler
global isr2

section .text
isr2:
    cli
    push byte 0 ; The error code
    push byte 2 ; The ISR number
    jmp interruptHandler
