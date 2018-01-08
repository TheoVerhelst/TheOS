extern interruptHandler
global isr51

section .text
isr51:
    cli
    push byte 0 ; The error code
    push byte 51 ; The ISR number
    jmp interruptHandler
