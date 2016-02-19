extern interruptHandler
global isr14

section .text
isr14:
    cli
    ; The cpu already pushes an error code
    push byte 14 ; The ISR number
    jmp interruptHandler
