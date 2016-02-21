; NASM kernel boot multiboot compatible compilation file

; CONSTANTS
; MB_ALIGN: the modules loaded with the executable are aligned on 4k boundaries
; MEM_INFO: some informations about memory are passed to the executable by GRUB
; MAGIC   : a value defined by the standard, informations can be found in README

MB_ALIGN equ 1 << 0
MEM_INFO equ 1 << 1
FLAGS    equ MB_ALIGN | MEM_INFO
MAGIC    equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

; make a new section so data are ordered in a true header
section .multiboot
	align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
	; this is the multiboot info structure address that is available to
	; the C++ environnement, it must be defined in assembly.
	; the keyword common is similar to global, but for variables.
	common multibootInfoAddress 4

; precise 'nobits' so that NASM knows that no explicit data is given
section .bootstrap_stack, nobits
	align 4
	stack_bottom:
	resb 0x4000  ; make a 16 KiB stack
	stack_top:

section .text
	; _start is the entry point of the OS kernel where the bootloader jumps when it's done.
	global _start

	extern setMultibootInfoAddress

	; kernelMain is the entry point of the C++ code kernel
	extern kernelMain

	; _init and _fini are entry points of routine used for initializing global objects
	extern _init
	extern _fini

	_start:
		; set up a stack by putting TOS in ESP
		mov esp, stack_top

		; set the address of the multiboot info structure
		mov [multibootInfoAddress], ebx

		; call objects constructors routines
		call _init
		call _fini

		; Let's go for some fun
		call kernelMain

		; reset the interrupt flag (IF) to not handle maskable interrupts
		cli

	.hang:
		; infinite loop if kernelMain returns
		hlt
		jmp .hang
