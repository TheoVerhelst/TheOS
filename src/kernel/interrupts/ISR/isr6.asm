extern interruptHandler
global isr6

section .text
isr6:
    cli
    push byte 0 ; The error code
    push byte 6 ; The ISR number
    jmp interruptHandler
