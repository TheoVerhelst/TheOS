extern interruptHandler
global isr42

section .text
isr42:
    cli
    push byte 0 ; The error code
    push byte 42 ; The ISR number
    jmp interruptHandler
