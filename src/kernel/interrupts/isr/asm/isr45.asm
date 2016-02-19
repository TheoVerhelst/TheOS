extern interruptHandler
global isr45

section .text
isr45:
    cli
    push byte 0 ; The error code
    push byte 45 ; The ISR number
    jmp interruptHandler
