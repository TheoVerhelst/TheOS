extern interruptHandler
global isr32

section .text
isr32:
    cli
    push byte 0 ; The error code
    push byte 32 ; The ISR number
    jmp interruptHandler
