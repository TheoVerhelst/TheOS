extern interruptHandler
global isr41

section .text
isr41:
    cli
    push byte 0 ; The error code
    push byte 41 ; The ISR number
    jmp interruptHandler
