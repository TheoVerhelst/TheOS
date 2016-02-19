extern interruptHandler
global isr31

section .text
isr31:
    cli
    push byte 0 ; The error code
    push byte 31 ; The ISR number
    jmp interruptHandler
