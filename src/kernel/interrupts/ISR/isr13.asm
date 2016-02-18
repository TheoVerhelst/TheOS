extern interruptHandler
global isr13

section .text
isr13:
    cli
    ; The cpu already pushes an error code
    push byte 13 ; The ISR number
    jmp interruptHandler
