extern interruptHandler
global isr17

section .text
isr17:
    cli
    push byte 0 ; The error code
    push byte 17 ; The ISR number
    jmp interruptHandler
