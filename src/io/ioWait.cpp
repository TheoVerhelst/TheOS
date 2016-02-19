#include <io/ioWait.hpp>

void ioWait()
{
	asm volatile("jmp 1f\n\t"
		"1:jmp 2f\n\t"
		"2:");
}
