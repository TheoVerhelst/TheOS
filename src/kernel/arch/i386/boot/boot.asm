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

; _init is entry point of routine used for initializing global objects
extern _init
; _fini is the exit function that calls global object destructors
extern _fini

; make a new section so data are ordered in a true header
section .multiboot
	align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bootInit
	; this is the multiboot info structure address
	multibootInfoAddress db 0
	align 4
	times 0x1000 db 0x0 ; make a 4Ko stack
	initStackTop:

	_start:
		; set up a little stack for paging init functions
		mov esp, initStackTop

		; set the address of the multiboot info structure
		mov [multibootInfoAddress], ebx

		; call paging init
		call initKernelPaging

		; activate paging by setting registers
		mov eax, kernelPageDirectory
		mov cr3, eax
		; turn on paging bit
		mov eax, cr0
		or eax, 0x80000000

		mov cr0, eax

		; set up a stack by putting TOS in ESP
		mov esp, kernelStackTop

		; call global objects constructors routines
		call _init

		; let's go for some fun
		push DWORD [multibootInfoAddress]
		call kernelMain
		add esp, byte 4

		; call objects destructor routines. It doesn't hurt, and it may be useful
		call _fini

	.hang:
		; infinite loop if kernelMain returns
		hlt
		jmp .hang

section .bss
	align 4
	resb 0x200000 ; make a 2Mb stack
	kernelStackTop:
