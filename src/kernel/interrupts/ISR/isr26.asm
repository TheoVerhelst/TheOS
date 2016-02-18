extern interruptHandler
global isr26

section .text
isr26:
    cli
    push byte 0 ; The error code
    push byte 26 ; The ISR number
    jmp interruptHandler
