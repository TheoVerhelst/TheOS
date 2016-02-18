extern interruptHandler
global isr5

section .text
isr5:
    cli
    push byte 0 ; The error code
    push byte 5 ; The ISR number
    jmp interruptHandler
