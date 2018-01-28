extern isrDispatcher
global interruptHandler

; TODO I didn't manage to use the -I flag of nasm, this should be solved
%include "../../../include/kernel/arch/i386/memory/segmentation/segmentSelectors.asm"

section .text
interruptHandler:
	pushad ; Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI
	; Push the address of the stack, to give it as a pointer to the arg struct
	mov eax, esp
	push eax
	call isrDispatcher
	add esp, 4
	popad
	add esp, 8 ; Cleans up the pushed error code and pushed ISR number
	iret
