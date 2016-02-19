extern interruptHandler
global isr11

section .text
isr11:
    cli
    ; The cpu already pushes an error code
    push byte 11 ; The ISR number
    jmp interruptHandler
