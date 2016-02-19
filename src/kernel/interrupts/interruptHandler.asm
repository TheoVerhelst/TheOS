extern isrDispatcher
global interruptHandler

%define DATA_SEGMENT 0x08

section .text
interruptHandler:
	push ds
	push es
	push fs
	push gs
	; Set up segment registers for the interrupt handler
	mov ax, DATA_SEGMENT
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, isrDispatcher
	call eax  ; A special call, preserves the 'eip' register
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	add esp, 8  ; Cleans up the pushed error code and pushed ISR number
	sti ; Reenable interrupts
	iret
