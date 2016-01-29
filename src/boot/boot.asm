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

; precise 'nobits' so that NASM knows that no explicit data is given
section .bootstrap_stack, nobits
	align 4
	stack_bottom:
	resb 0x4000  ; make a 16 KiB stack
	stack_top:

section .text
	; _start is the entry point of the OS kernel where the bootloader jumps when it's done.
	global _start
	; kernel_main is the entry point of the C++ code kernel
	extern kernel_main
	; _init and _fini are entry points of routine used for initializing global objects
	extern _init
	extern _fini

	_start:
		; set up a stack by putting TOS in ESP
		mov esp, stack_top

		; call objects constructors calling routine
		call _init
		call _fini

		call kernel_main

		cli  ; set Interrupt Flag (IF) to 0 to not handle maskable interrupts
	.hang:
		hlt  ; infinite loop if kernel_main returns
		jmp .hang
