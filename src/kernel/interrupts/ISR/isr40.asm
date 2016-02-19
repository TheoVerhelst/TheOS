extern interruptHandler
global isr40

section .text
isr40:
    cli
    push byte 0 ; The error code
    push byte 40 ; The ISR number
    jmp interruptHandler
