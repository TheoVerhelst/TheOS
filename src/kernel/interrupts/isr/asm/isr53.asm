extern interruptHandler
global isr53

section .text
isr53:
    cli
    push byte 0 ; The error code
    push byte 53 ; The ISR number
    jmp interruptHandler
