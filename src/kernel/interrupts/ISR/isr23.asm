extern interruptHandler
global isr23

section .text
isr23:
    cli
    push byte 0 ; The error code
    push byte 23 ; The ISR number
    jmp interruptHandler
