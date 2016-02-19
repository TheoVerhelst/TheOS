extern interruptHandler
global isr39

section .text
isr39:
    cli
    push byte 0 ; The error code
    push byte 39 ; The ISR number
    jmp interruptHandler
