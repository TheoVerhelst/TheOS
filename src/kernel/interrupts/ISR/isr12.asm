extern interruptHandler
global isr12

section .text
isr12:
    cli
    push byte 0 ; The error code
    push byte 12 ; The ISR number
    jmp interruptHandler
