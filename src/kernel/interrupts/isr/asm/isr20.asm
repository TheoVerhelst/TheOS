extern interruptHandler
global isr20

section .text
isr20:
    cli
    push byte 0 ; The error code
    push byte 20 ; The ISR number
    jmp interruptHandler
