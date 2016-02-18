extern interruptHandler
global isr28

section .text
isr28:
    cli
    push byte 0 ; The error code
    push byte 28 ; The ISR number
    jmp interruptHandler
