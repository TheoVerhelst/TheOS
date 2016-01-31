#include <io/out.hpp>

void outb(uint16_t port, uint8_t value)
{
	__asm__ __volatile__ ("outb %1, %0"
	                      :
						  : "dN" (port), "a" (value));
}
