extern interruptHandler
global isr36

section .text
isr36:
    cli
    push byte 0 ; The error code
    push byte 36 ; The ISR number
    jmp interruptHandler
