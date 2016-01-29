#include <stdio.hpp>
#include <kernel/terminal/terminal.hpp>

int puts(const char * str)
{
	terminal_putstring(str);
	putchar('\n');
	return 1;
}
