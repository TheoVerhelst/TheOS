; NASM kernel boot multiboot compatible compilation file

; CONSTANTS
; MB_ALIGN: the modules loaded with the executable are aligned on 4k boundaries
; MEM_INFO: some informations about memory are passed to the executable by GRUB
; MAGIC: a value defined by the standard, informations can be found in README

MB_ALIGN equ 1 << 0
MEM_INFO equ 1 << 1
FLAGS    equ MB_ALIGN | MEM_INFO
MAGIC    equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

; _start is the entry point of the OS kernel where the bootloader jumps when it's done.
global _start

; this is the function that maps memory in page tables and directories at init stage
extern initKernelPaging

; this is the address of the kernel page directory
extern kernelPageDirectory

; kernelMain is the entry point of the C++ code kernel
extern kernelMain

; _init and _fini are entry points of routine used for initializing global objects
extern _init
extern _fini


; make a new section so data are ordered in a true header
section .multiboot
	align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .init
	align 4
	initStackBottom:
	resb 0x1000  ; make a 4KB stack
	initStackTop:

	_start:
		cli ; Block interrupts

		; set up a little stack for paging init functions
		mov esp, initStackTop

		; call paging init
		call initKernelPaging

		; activate paging by setting registers
		mov eax, kernelPageDirectory
		mov cr3, eax
		mov eax, cr0
		; turn on paging bit
		or eax, 0x80000000
		mov cr0, eax


		; set up a stack by putting TOS in ESP
		mov esp, kernelStackTop

		; set the address of the multiboot info structure
		mov [multibootInfoAddress], ebx

		; call objects constructors routines
		call _init
		call _fini

		; let's go for some fun
		call kernelMain

		; reset the interrupt flag (IF) to not handle maskable interrupts
		cli

	.hang:
		; infinite loop if kernelMain returns
		hlt
		jmp .hang

section .bss
	; this is the multiboot info structure address that is available to
	; the C++ environnement, it must be defined in assembly.
	; the keyword common is similar to global, but for variables.
	common multibootInfoAddress 4

; precise 'nobits' so that NASM knows that no explicit data is given
section .kernelStack, nobits
	align 4
	kernelStackBottom:
	resb 0x4000 ; make a 16KB stack
	kernelStackTop:
