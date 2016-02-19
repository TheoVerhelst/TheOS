extern interruptHandler
global isr49

section .text
isr49:
    cli
    push byte 0 ; The error code
    push byte 49 ; The ISR number
    jmp interruptHandler
