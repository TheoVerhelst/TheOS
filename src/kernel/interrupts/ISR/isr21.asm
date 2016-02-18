extern interruptHandler
global isr21

section .text
isr21:
    cli
    push byte 0 ; The error code
    push byte 21 ; The ISR number
    jmp interruptHandler
