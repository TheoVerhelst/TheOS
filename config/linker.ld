/* Entry point is the assembly label _start */
ENTRY(_start)

kernelVirtualOffset = 0xC0000000;

SECTIONS
{
	. = 1M;

	lowKernelStart = ALIGN(4K);

	/**** BOOTSTRAP INIT PART ****/

	/* Place the header first for the bootloader to recognize the kernel */
	.bootInit ALIGN(4K) :
	{
		*(.multiboot)
		*(.bootInit)
		*(.pagingTables)
	}

	lowKernelEnd = .;

	/**** HIGHER HALF KERNEL PART ****/

	. += kernelVirtualOffset;

	/* Symbols to retrieve the beginning of the kernel in memory */
	kernelVirtualStart = ALIGN(4K);
	kernelPhysicalStart = kernelVirtualStart - kernelVirtualOffset;

	/* Text. */
	.text ALIGN(4K) : AT(ADDR(.text) - kernelVirtualOffset)
	{
		*(.text)
	}

	/* RO data. */
	.rodata ALIGN(4K) : AT(ADDR(.rodata) - kernelVirtualOffset)
	{
		*(.rodata)
	}

	/* RW data (initialized) */
	.data ALIGN(4K) : AT(ADDR(.data) - kernelVirtualOffset)
	{
		*(.data)
	}

	/* RW data (uninitialized) and stack */
	.bss ALIGN(4K) : AT(ADDR(.bss) - kernelVirtualOffset)
	{
		*(.bss)
		*(COMMON)
		*(.kernelStack)
	}

	/* Symbols to retrieve the end of the kernel in memory */
	kernelVirtualEnd = .;
	kernelPhysicalEnd = kernelVirtualEnd - kernelVirtualOffset;
}
