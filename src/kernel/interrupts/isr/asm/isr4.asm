extern interruptHandler
global isr4

section .text
isr4:
    cli
    push byte 0 ; The error code
    push byte 4 ; The ISR number
    jmp interruptHandler
