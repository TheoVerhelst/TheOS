extern interruptHandler
global isr10

section .text
isr10:
    cli
    ; The cpu already pushes an error code
    push byte 10 ; The ISR number
    jmp interruptHandler
