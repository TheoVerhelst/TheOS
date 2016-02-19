extern interruptHandler
global isr50

section .text
isr50:
    cli
    push byte 0 ; The error code
    push byte 50 ; The ISR number
    jmp interruptHandler
