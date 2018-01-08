extern interruptHandler
global isr47

section .text
isr47:
    cli
    push byte 0 ; The error code
    push byte 47 ; The ISR number
    jmp interruptHandler
