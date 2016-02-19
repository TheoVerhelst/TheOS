extern interruptHandler
global isr43

section .text
isr43:
    cli
    push byte 0 ; The error code
    push byte 43 ; The ISR number
    jmp interruptHandler
