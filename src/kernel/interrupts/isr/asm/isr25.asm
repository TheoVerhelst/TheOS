extern interruptHandler
global isr25

section .text
isr25:
    cli
    push byte 0 ; The error code
    push byte 25 ; The ISR number
    jmp interruptHandler
