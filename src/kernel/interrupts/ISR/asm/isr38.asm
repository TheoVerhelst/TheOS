extern interruptHandler
global isr38

section .text
isr38:
    cli
    push byte 0 ; The error code
    push byte 38 ; The ISR number
    jmp interruptHandler
