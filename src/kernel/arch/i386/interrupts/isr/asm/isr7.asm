extern interruptHandler
global isr7

section .text
isr7:
    cli
    push byte 0 ; The error code
    push byte 7 ; The ISR number
    jmp interruptHandler
