/* Entry point is the assembly label _start */
ENTRY(_start)

kernelVirtualOffset = 0xC0000000;

SECTIONS
{
	. = 1M;

	/**** BOOTSTRAP INIT PART ****/

	.init ALIGN(4K) :
	{
		*(.multiboot);
		*(.init);
		*(.pagingTables);
	}

	/**** HIGHER HALF KERNEL PART ****/

	. += kernelVirtualOffset;

	/* A symbol to retrieve the beginning of the kernel in memory */
	kernelHighHalfStart = ALIGN(4K);

	/* Place the header first for the bootloader to recognize the kernel */
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

	/* A symbol to retrieve the end of the kernel in memory */
	kernelHighHalfEnd = .;
}
