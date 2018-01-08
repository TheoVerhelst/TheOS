#include <kernel/io.hpp>

uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

void outb(uint16_t port, uint8_t value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void ioWait()
{
	asm volatile("jmp 1f\n\t"
		"1:jmp 2f\n\t"
		"2:");
}
