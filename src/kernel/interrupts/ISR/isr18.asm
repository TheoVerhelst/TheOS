extern interruptHandler
global isr18

section .text
isr18:
    cli
    push byte 0 ; The error code
    push byte 18 ; The ISR number
    jmp interruptHandler
