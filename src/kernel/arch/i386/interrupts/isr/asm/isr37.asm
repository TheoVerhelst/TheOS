extern interruptHandler
global isr37

section .text
isr37:
    cli
    push byte 0 ; The error code
    push byte 37 ; The ISR number
    jmp interruptHandler
