extern interruptHandler
global isr30

section .text
isr30:
    cli
    push byte 0 ; The error code
    push byte 30 ; The ISR number
    jmp interruptHandler
