extern interruptHandler
global isr16

section .text
isr16:
    cli
    push byte 0 ; The error code
    push byte 16 ; The ISR number
    jmp interruptHandler
