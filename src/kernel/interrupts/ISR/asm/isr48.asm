extern interruptHandler
global isr48

section .text
isr48:
    cli
    push byte 0 ; The error code
    push byte 48 ; The ISR number
    jmp interruptHandler
