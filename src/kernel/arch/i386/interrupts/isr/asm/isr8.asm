extern interruptHandler
global isr8

section .text
isr8:
    cli
    ; The cpu already pushes an error code
    push byte 8 ; The ISR number
    jmp interruptHandler
