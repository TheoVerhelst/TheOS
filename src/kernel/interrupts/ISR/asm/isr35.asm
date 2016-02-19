extern interruptHandler
global isr35

section .text
isr35:
    cli
    push byte 0 ; The error code
    push byte 35 ; The ISR number
    jmp interruptHandler
