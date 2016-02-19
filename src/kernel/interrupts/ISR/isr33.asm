extern interruptHandler
global isr33

section .text
isr33:
    cli
    push byte 0 ; The error code
    push byte 33 ; The ISR number
    jmp interruptHandler
