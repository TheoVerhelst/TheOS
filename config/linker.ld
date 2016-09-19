/* Entry point is the assembly label _start */
ENTRY(_start)

SECTIONS
{
	. = 1M;

	/* A symbol to retrieve the beginning of the kernel in memory */
	beginKernel = ALIGN(4K);

	/* Place the header first for the bootloader to recognize the kernel */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* RO data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* RW data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* RW data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

	/* A symbol to retrieve the end of the kernel in memory */
	endKernel = ALIGN(4K);
}
