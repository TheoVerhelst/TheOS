extern interruptHandler
global isr19

section .text
isr19:
    cli
    push byte 0 ; The error code
    push byte 19 ; The ISR number
    jmp interruptHandler
