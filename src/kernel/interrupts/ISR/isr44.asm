extern interruptHandler
global isr44

section .text
isr44:
    cli
    push byte 0 ; The error code
    push byte 44 ; The ISR number
    jmp interruptHandler
