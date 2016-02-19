extern interruptHandler
global isr9

section .text
isr9:
    cli
    push byte 0 ; The error code
    push byte 9 ; The ISR number
    jmp interruptHandler
