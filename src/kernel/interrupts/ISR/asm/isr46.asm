extern interruptHandler
global isr46

section .text
isr46:
    cli
    push byte 0 ; The error code
    push byte 46 ; The ISR number
    jmp interruptHandler
