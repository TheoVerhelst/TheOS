extern interruptHandler
global isr63

section .text
isr63:
    cli
    push byte 0 ; The error code
    push byte 63 ; The ISR number
    jmp interruptHandler
