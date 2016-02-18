extern interruptHandler
global isr15

section .text
isr15:
    cli
    push byte 0 ; The error code
    push byte 15 ; The ISR number
    jmp interruptHandler
