extern interruptHandler
global isr17

section .text
isr17:
    cli
    ; The cpu already pushes an error code
    push byte 17 ; The ISR number
    jmp interruptHandler
