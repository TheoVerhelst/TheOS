extern interruptHandler
global isr52

section .text
isr52:
    cli
    push byte 0 ; The error code
    push byte 52 ; The ISR number
    jmp interruptHandler
