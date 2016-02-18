extern interruptHandler
global isr1

section .text
isr1:
    cli
    push byte 0 ; The error code
    push byte 1 ; The ISR number
    jmp interruptHandler
