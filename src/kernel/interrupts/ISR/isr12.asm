extern interruptHandler
global isr12

section .text
isr12:
    cli
    ; The cpu already pushes an error code
    push byte 12 ; The ISR number
    jmp interruptHandler
