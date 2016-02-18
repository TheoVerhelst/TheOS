extern interruptHandler
global isr24

section .text
isr24:
    cli
    push byte 0 ; The error code
    push byte 24 ; The ISR number
    jmp interruptHandler
