extern interruptHandler
global isr0

section .text
isr0:
    cli
    push byte 0 ; The error code
    push byte 0 ; The ISR number
    jmp interruptHandler
