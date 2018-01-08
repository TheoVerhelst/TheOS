extern interruptHandler
global isr29

section .text
isr29:
    cli
    push byte 0 ; The error code
    push byte 29 ; The ISR number
    jmp interruptHandler
