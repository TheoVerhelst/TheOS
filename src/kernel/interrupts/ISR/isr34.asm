extern interruptHandler
global isr34

section .text
isr34:
    cli
    push byte 0 ; The error code
    push byte 34 ; The ISR number
    jmp interruptHandler
