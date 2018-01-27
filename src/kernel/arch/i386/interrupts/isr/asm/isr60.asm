extern interruptHandler
global isr60

section .text
isr60:
    cli
    push byte 0 ; The error code
    push byte 60 ; The ISR number
    jmp interruptHandler
