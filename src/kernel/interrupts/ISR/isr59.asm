extern interruptHandler
global isr59

section .text
isr59:
    cli
    push byte 0 ; The error code
    push byte 59 ; The ISR number
    jmp interruptHandler
