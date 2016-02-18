extern interruptHandler
global isr27

section .text
isr27:
    cli
    push byte 0 ; The error code
    push byte 27 ; The ISR number
    jmp interruptHandler
